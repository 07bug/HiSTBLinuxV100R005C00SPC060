
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <errno.h>
#include <stdlib.h>

#include "hi_flash.h"
#include "nand.h"
#include "hi_debug.h"

#define BDEVNAME_SIZE   32  /* Largest string for a blockdev identifier */
#define min(a,b) (a)<=(b)?(a):(b)

struct cmdline_subpart {
    HI_CHAR name[BDEVNAME_SIZE]; /* partition name, such as 'rootfs' */
    HI_U64 from;
    HI_U64 size;
    struct cmdline_subpart *next_subpart;
};

struct cmdline_parts_info
{
    HI_CHAR PartName[BDEVNAME_SIZE];
    HI_U64 StartAddr;
    HI_U64 PartSize;
};

struct cmdline_parts {
    HI_CHAR name[BDEVNAME_SIZE]; /* block device, such as 'mmcblk0' */
    HI_U64 end_addr;
    struct cmdline_subpart *subpart;
    struct cmdline_parts *next_parts;
};

static  struct cmdline_parts_info cmdline_partition[MAX_PARTS];
static  struct cmdline_parts *cmdline_parts_head = NULL;

static HI_U64 memparse(const HI_CHAR *ptr, HI_CHAR **retptr)
{
    HI_CHAR *endptr;   /* local pointer to end of parsed string */

    HI_U64  ret = strtoull(ptr, &endptr, 0);

    switch (*endptr)
    {
        case 'G':
        case 'g':
            ret <<= 10;
        //lint -fallthrough
        case 'M':
        case 'm':
            ret <<= 10;
        //lint -fallthrough
        case 'K':
        case 'k':
            ret <<= 10;
            endptr++;
        //lint -fallthrough
        default:
            break;
    }

    if (retptr)
    {
        *retptr = endptr;
    }

    return ret;
}

static HI_S32 parse_subpart(struct cmdline_parts *parts, struct cmdline_subpart **subpart, HI_CHAR *cmdline)
{
    HI_S32 ret = 0;
    struct cmdline_subpart *new_subpart;

    *subpart = NULL;

    new_subpart = malloc(sizeof(struct cmdline_subpart));
    if (!new_subpart)
        return -ENOMEM;
    memset(new_subpart, 0, sizeof(struct cmdline_subpart));

    if (*cmdline == '-') {
        new_subpart->size = (HI_U64)(~0ULL);
        cmdline++;
    } else {
        new_subpart->size = memparse(cmdline, &cmdline);
        if (new_subpart->size == 0) {
            HI_PRINT("cmdline partition size is invalid.\n");
            ret = -EINVAL;
            goto fail;
        }
    }

    if (*cmdline == '@') {
        cmdline++;
        new_subpart->from = memparse(cmdline, &cmdline);
        parts->end_addr = new_subpart->from + new_subpart->size;
    } else {
        new_subpart->from = parts->end_addr;
        parts->end_addr += new_subpart->size;
    }

    if (*cmdline == '(') {
        HI_S32 length;
        HI_CHAR *next = strchr(++cmdline, ')');

        if (!next) {
            HI_PRINT("cmdline partition format is invalid.");
            ret = -EINVAL;
            goto fail;
        }

        length = min((HI_U32)(next - cmdline),
                   sizeof(new_subpart->name) - 1);
        strncpy(new_subpart->name, cmdline, length);
        new_subpart->name[length] = '\0';

        cmdline = ++next;
    } else
        new_subpart->name[0] = '\0';

    *subpart = new_subpart;
    return 0;
fail:
    free(new_subpart);
    return ret;
}

static HI_VOID free_subpart(struct cmdline_parts *parts)
{
    struct cmdline_subpart *subpart;

    while (parts->subpart) {
        subpart = parts->subpart;
        parts->subpart = subpart->next_subpart;
        free(subpart);
    }
}

static HI_VOID free_parts(struct cmdline_parts **parts)
{
    struct cmdline_parts *next_parts;

    while (*parts) {
        next_parts = (*parts)->next_parts;
        free_subpart(*parts);
        free(*parts);
        *parts = next_parts;
    }
}

static HI_S32 parse_parts(struct cmdline_parts **parts, HI_CHAR *cmdline)
{
    HI_S32 ret = -EINVAL;
    HI_CHAR *next;
    HI_U32 length;
    struct cmdline_subpart **next_subpart = NULL;
    struct cmdline_parts *newparts = NULL;
    HI_CHAR buf[BDEVNAME_SIZE + 32 + 4];

    *parts = NULL;

    newparts = malloc(sizeof(struct cmdline_parts));
    if (!newparts)
        return -ENOMEM;
    memset(newparts, 0, sizeof(struct cmdline_parts));

    if (!cmdline) {
        HI_PRINT("cmdline partition invalid.");
        goto fail;
    }

    next = strchr(cmdline, ':');
    if (!next) {
        HI_PRINT("cmdline partition has not block device.");
        goto fail;
    }

    length = min((HI_U32)(next - cmdline), sizeof(newparts->name) - 1);
    strncpy(newparts->name, cmdline, length);
    newparts->name[length] = '\0';
    newparts->end_addr = 0;

    next_subpart = &newparts->subpart;

    while (next && *(++next)) {
        cmdline = next;
        next = strchr(cmdline, ',');

        length = (!next) ? (sizeof(buf) - 1) :
            min((HI_U32)(next - cmdline), sizeof(buf) - 1);

        strncpy(buf, cmdline, length);
        buf[length] = '\0';

        ret = parse_subpart(newparts, next_subpart, buf);
        if (ret)
            goto fail;

        next_subpart = &(*next_subpart)->next_subpart;
    }

    if (!newparts->subpart) {
        HI_PRINT("cmdline partition has not valid partition.");
        goto fail;
    }

    *parts = newparts;

    return 0;
fail:
    free_subpart(newparts);
    free(newparts);
    return ret;
}

static HI_S32 parse_cmdline(struct cmdline_parts **parts, const HI_CHAR *cmdline)
{
    HI_S32 ret;
    HI_CHAR *buf;
    HI_CHAR *pbuf;
    HI_CHAR *next;
    struct cmdline_parts **next_parts;

    *parts = NULL;

    if (!cmdline)
        return -1;
    if (strlen(cmdline) == SIZE_MAX)
        next = pbuf = buf = strdup(cmdline);
    else
        next = pbuf = buf = strndup(cmdline, strlen(cmdline));
    if (!buf)
        return -ENOMEM;

    next_parts = parts;

    while (next && *pbuf) {
        next = strchr(pbuf, ';');
        if (next)
            *next = '\0';

        ret = parse_parts(next_parts, pbuf);
        if (ret)
            goto fail;

        if (next)
            pbuf = ++next;

        next_parts = &(*next_parts)->next_parts;
    }

    if (!*parts) {
        HI_PRINT("cmdline partition has not valid partition.");
        ret = -EINVAL;
        goto fail;
    }

    ret = 0;
done:
    free(buf);
    return ret;

fail:
    free_parts(parts);
    goto done;
}


static struct cmdline_parts *get_cmdline_parts(HI_CHAR *cmdline_string)
{
    HI_CHAR *parts_string = NULL;
    struct cmdline_parts *tmp_cmdline_parts = NULL;

    if (!cmdline_string) {
        goto fail;
    }

    parts_string = strstr(cmdline_string, "mmcblk0:");
    if (!parts_string) {
        goto fail;
    }

    if (parse_cmdline(&tmp_cmdline_parts, parts_string) || !tmp_cmdline_parts)
        goto fail;

    return tmp_cmdline_parts;
fail:
    if (tmp_cmdline_parts)
        free_parts(&tmp_cmdline_parts);

    return NULL;
}

HI_S32 cmdline_parts_init(HI_CHAR *bootargs)
{
    HI_CHAR *cmdline_string = NULL;
    HI_CHAR *pcmdline_buf = NULL;
    HI_CHAR *pend = NULL;
    HI_S32 ret = -1;

    if (!bootargs)
        goto fail;

    if (cmdline_parts_head) {
        ret = 0;
        goto done;
    }

    cmdline_string = strstr(bootargs, "blkdevparts=");
    if (!cmdline_string) {
        ret = -EINVAL;
        goto fail;
    }

    cmdline_string += sizeof("blkdevparts=") - 1;

    pcmdline_buf = strdup(cmdline_string);
    if (!pcmdline_buf) {
        ret = -ENOMEM;
        goto fail;
    }

    if ((pend = strchr(pcmdline_buf, ' '))
        && (HI_U32)(pend - pcmdline_buf) <= strlen(pcmdline_buf)) {
        *pend = '\0';
    }

    cmdline_parts_head = get_cmdline_parts(pcmdline_buf);
    if (!cmdline_parts_head) {
        HI_PRINT("Fail to get cmdline parts from: %s\n", pcmdline_buf);
        ret = -ENODEV;
        goto fail;
    }

    ret = 0;
done:
    if (pcmdline_buf)
        free(pcmdline_buf);
    return ret;
fail:
    goto done;
}

/* 1 - find, 0 - no find */
HI_S32 find_flash_part(HI_CHAR *cmdline_string,
                              const HI_CHAR * media_name,  /* hi_sfc, hinand */
                              HI_CHAR * ptn_name,
                              HI_U64 *start,
                              HI_U64 *length)
{
    HI_S32 got = 0;
    size_t len;
    struct cmdline_parts *tmp_cmdline_parts = NULL;
    struct cmdline_subpart *tmp_subpart     = NULL;

    if (!media_name || !ptn_name \
        || !start || !length) {
        goto fail;
    }

    if (!cmdline_parts_head) {
        goto fail;
    }

    tmp_cmdline_parts = cmdline_parts_head;
    got = 0;
    while(tmp_cmdline_parts && !got) {
        len = sizeof(tmp_cmdline_parts->name) > strlen(media_name) ? (strlen(media_name) + 1) : sizeof(tmp_cmdline_parts->name);
        if (!strncmp(tmp_cmdline_parts->name, \
                     media_name, len)) {
            got = 1;
            break;
        }
        tmp_cmdline_parts = tmp_cmdline_parts->next_parts;
    }

    if (!got || !tmp_cmdline_parts) {
        HI_PRINT("%s not found from: %s\n", media_name, cmdline_string);
        goto fail;
    }

    tmp_subpart = tmp_cmdline_parts->subpart;
    got = 0;
    while (tmp_subpart && !got) {
        len = sizeof(tmp_subpart->name) > strlen(ptn_name) ? (strlen(ptn_name) + 1) : sizeof(tmp_subpart->name);
        if (!strncmp(tmp_subpart->name, ptn_name, len)) {
            got = 1;
            break;
        }
        tmp_subpart = tmp_subpart->next_subpart;
    }

    if (!got || !tmp_subpart) {
        HI_PRINT("%s not found from: %s\n", ptn_name, cmdline_string);
        goto fail;
    }

    *start  = (HI_U64)(tmp_subpart->from);
    *length = (HI_U64)(tmp_subpart->size);
    HI_DBG_PRINT(HI_ID_FLASH, "Got partition %s: start=0x%llX,size=%llu\n", ptn_name, *start, *length);

    return 1;
fail:
    return 0;
}
/* 0 - success, -1 - fail */
HI_S32 get_part_info(HI_U8 partnum, HI_U64 *start, HI_U64 *size)
{
    HI_S32 partindex = 0;
    struct cmdline_subpart *part;

    if (!cmdline_parts_head || !cmdline_parts_head->subpart) {
        HI_PRINT("cmdline parts not initialized.\n");
        goto fail;
    }

    part = cmdline_parts_head->subpart;

    while (part && (partindex < MAX_PARTS)) {
        strncpy(cmdline_partition[partindex].PartName,
            part->name, sizeof(cmdline_partition[partindex].PartName));
        cmdline_partition[partindex].PartName[sizeof(cmdline_partition[partindex].PartName) - 1] = '\0';
        cmdline_partition[partindex].StartAddr = (part->from);
        cmdline_partition[partindex].PartSize = (part->size);

        partindex ++;
        part = part->next_subpart;
    }

    if (partnum == 0) {
        HI_PRINT("partnum(%d) is invalid. \n", partnum);
        goto fail;
    }

    if (partnum > partindex) {
        HI_PRINT("partnum is to large, max partnum is %d.\n",
            partindex);
        goto fail;
    }

    *start = (HI_U64)cmdline_partition[partnum-1].StartAddr;
    *size = (HI_U64)cmdline_partition[partnum-1].PartSize;

    return 0;
fail:
    return -1;
}
