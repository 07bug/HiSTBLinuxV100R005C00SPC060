/* Copyright 2008 The Android Open Source Project
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include "binder.h"

#define LOG_TAG "servicemanager"
#include <cutils/log.h>

#define CHK_SVCMNG_RETURN(val, ret, ...) /*lint -save -e64*/ \
    do \
    { \
        if ((val)) \
        { \
            ALOGE(__VA_ARGS__); \
            return (ret); \
        } \
    } while (0) /*lint -restore */

/* TODO:
 * These should come from a config file or perhaps be
 * based on some namespace rules of some sort (media
 * uid can register media.*, etc)
 */

uint32_t svcmgr_handle;

const char *str8(const uint16_t *x, size_t x_len)
{
    static char buf[128];
    size_t max = 127;
    char *p = buf;

    if (x_len < max) {
        max = x_len;
    }

    if (x) {
        while ((max > 0) && (*x != '\0')) {
            *p++ = *x++;
            max--;
        }
    }
    *p++ = 0;
    return buf;
}

int str16eq(const uint16_t *a, const char *b)
{
    while (*a && *b)
        if (*a++ != *b++) return 0;
    if (*a || *b)
        return 0;
    return 1;
}

struct svcinfo
{
    struct svcinfo *next;
    uint32_t handle;
    struct binder_death death;
    int allow_isolated;
    size_t len;
    uint16_t name[0];
};

struct svcinfo *svclist = NULL;

struct svcinfo *find_svc(const uint16_t *s16, size_t len)
{
    struct svcinfo *si;

    for (si = svclist; si; si = si->next) {
        if ((len == si->len) &&
            !memcmp(s16, si->name, len * sizeof(uint16_t))) {
            return si;
        }
    }
    return NULL;
}

void svcinfo_death(struct binder_state *bs, void *ptr)
{
    struct svcinfo *si = (struct svcinfo* ) ptr;

    ALOGI("service '%s' died\n", str8(si->name, si->len));
    if (si->handle) {
        binder_release(bs, si->handle);
        si->handle = 0;
    }
}

uint16_t svcmgr_id[] = {
    'a','n','d','r','o','i','d','.','o','s','.',
    'I','S','e','r','v','i','c','e','M','a','n','a','g','e','r'
};

uint32_t do_find_service(struct binder_state *bs, const uint16_t *s, size_t len, uid_t uid, pid_t spid)
{
    struct svcinfo *si;
    si = find_svc(s, len);
    //ALOGI("check_service('%s') handle = %x\n", str8(s, len), si ? si->handle : 0);
    if (si && si->handle) {
        return si->handle;
    } else {
        return 0;
    }
}

int do_add_service(struct binder_state *bs,
                   const uint16_t *s, size_t len,
                   uint32_t handle, uid_t uid, int allow_isolated,
                   pid_t spid)
{
    struct svcinfo* si;

    //ALOGI("add_service('%s',%x,%s) uid=%d\n", str8(s, len), handle,
    //        allow_isolated ? "allow_isolated" : "!allow_isolated", uid);

    if (!handle || (len == 0) || (len > 127))
        return -1;

    si = find_svc(s, len);
    if (si) {
        if (si->handle) {
            ALOGE("add_service('%s',%x) uid=%d - ALREADY REGISTERED, OVERRIDE\n",
                 str8(s, len), handle, uid);
            svcinfo_death(bs, si);
        }
        si->handle = handle;
    } else {
        si = (struct svcinfo*)malloc(sizeof(*si) + (len + 1) * sizeof(uint16_t));
        if (!si) {
            ALOGE("add_service('%s',%x) uid=%d - OUT OF MEMORY\n",
                 str8(s, len), handle, uid);
            return -1;
        }
        si->handle = handle;
        si->len = len;
        memcpy(si->name, s, (len + 1) * sizeof(uint16_t));
        si->name[len] = '\0';
        si->death.func = svcinfo_death;
        si->death.ptr = si;
        si->allow_isolated = allow_isolated;
        si->next = svclist;
        svclist = si;
    }

    binder_acquire(bs, handle);
    binder_link_to_death(bs, handle, &si->death);
    return 0;
}

int svcmgr_handler(struct binder_state *bs,
                   struct binder_transaction_data *txn,
                   struct binder_io *msg,
                   struct binder_io *reply)
{
    struct svcinfo *si;
    uint16_t *s;
    size_t len;
    uint32_t handle;
    uint32_t strict_policy;
    int allow_isolated;

    //ALOGI("target=%x code=%d pid=%d uid=%d\n",
    //  txn->target.handle, txn->code, txn->sender_pid, txn->sender_euid);

    CHK_SVCMNG_RETURN((txn->target.handle != svcmgr_handle), -1, "svcmgr handle invalid");
    CHK_SVCMNG_RETURN((txn->code == PING_TRANSACTION), 0, "return 0");

    // Equivalent to Parcel::enforceInterface(), reading the RPC
    // header with the strict mode policy mask and the interface name.
    // Note that we ignore the strict_policy and don't propagate it
    // further (since we do no outbound RPCs anyway).
    strict_policy = bio_get_uint32(msg);
    printf("get policy value is %d \n", strict_policy);
    s = bio_get_string16(msg, &len);
    CHK_SVCMNG_RETURN((s == NULL), -1, "return -1");

    if ((len != (sizeof(svcmgr_id) / 2)) ||
        memcmp(svcmgr_id, s, sizeof(svcmgr_id))) {
        fprintf(stderr,"invalid id %s\n", str8(s, len));
        return -1;
    }

    switch(txn->code) {
    case SVC_MGR_GET_SERVICE:
    case SVC_MGR_CHECK_SERVICE:
        s = bio_get_string16(msg, &len);
        CHK_SVCMNG_RETURN((s == NULL), -1, "return -1");

        handle = do_find_service(bs, s, len, txn->sender_euid, txn->sender_pid);
        if (!handle)
            break;
        bio_put_ref(reply, handle);
        return 0;

    case SVC_MGR_ADD_SERVICE:
        s = bio_get_string16(msg, &len);
        CHK_SVCMNG_RETURN((s == NULL), -1, "return -1");

        handle = bio_get_ref(msg);
        allow_isolated = bio_get_uint32(msg) ? 1 : 0;
        if (do_add_service(bs, s, len, handle, txn->sender_euid,
            allow_isolated, txn->sender_pid))
            return -1;
        break;

    case SVC_MGR_LIST_SERVICES:
    {
        uint32_t n = bio_get_uint32(msg);

        si = svclist;
        while ((n-- > 0) && si)
            si = si->next;
        if (si) {
            bio_put_string16(reply, si->name);
            return 0;
        }
        return -1;
    }
    default:
        ALOGE("unknown code %d\n", txn->code);
        printf("ERROR===%d===\n", __LINE__);
        return -1;
    }

    bio_put_uint32(reply, 0);
    return 0;
}

int main(int argc, char** argv)
{
    struct binder_state* bs;
    void* svcmgr = BINDER_SERVICE_MANAGER;

    bs = binder_open(128 * 1024);

    if (binder_become_context_manager(bs))
    {
        ALOGE("cannot become context manager (%s)\n", strerror(errno));
        return -1;
    }

    svcmgr_handle = (uint32_t)svcmgr;
    binder_loop(bs, svcmgr_handler);
    return 0;
}
