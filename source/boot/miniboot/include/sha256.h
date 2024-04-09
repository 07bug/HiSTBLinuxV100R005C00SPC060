/*
 * SHA256 hash implementation and interface functions
 * Copyright (c) 2003-2006, Jouni Malinen <j@w1.fi>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Alternatively, this software may be distributed under the terms of BSD
 * license.
 *
 * See README and COPYING for more details.
 */

#ifndef SHA256_H
#define SHA256_H

#include <sys/types.h>

#define SHA256_MAC_LEN 32
#define INTERNAL_SHA256

/* Macros for handling unaligned memory accesses */

#define WPA_GET_BE16(a) ((u16) (((a)[0] << 8) | (a)[1]))
#define WPA_PUT_BE16(a, val)                    \
        do {                                    \
                (a)[0] = ((u16) (val)) >> 8;    \
                (a)[1] = ((u16) (val)) & 0xff;  \
        } while (0)

#define WPA_GET_LE16(a) ((u16) (((a)[1] << 8) | (a)[0]))
#define WPA_PUT_LE16(a, val)                    \
        do {                                    \
                (a)[1] = ((u16) (val)) >> 8;    \
                (a)[0] = ((u16) (val)) & 0xff;  \
        } while (0)

#define WPA_GET_BE24(a) ((((u32) (a)[0]) << 16) | (((u32) (a)[1]) << 8) | \
                         ((u32) (a)[2]))
#define WPA_PUT_BE24(a, val)                                    \
        do {                                                    \
                (a)[0] = (u8) ((((u32) (val)) >> 16) & 0xff);   \
                (a)[1] = (u8) ((((u32) (val)) >> 8) & 0xff);    \
                (a)[2] = (u8) (((u32) (val)) & 0xff);           \
        } while (0)

#define WPA_GET_BE32(a) ((((u32) (a)[0]) << 24) | (((u32) (a)[1]) << 16) | \
                         (((u32) (a)[2]) << 8) | ((u32) (a)[3]))
#define WPA_PUT_BE32(a, val)                                    \
        do {                                                    \
                (a)[0] = (u8) ((((u32) (val)) >> 24) & 0xff);   \
                (a)[1] = (u8) ((((u32) (val)) >> 16) & 0xff);   \
                (a)[2] = (u8) ((((u32) (val)) >> 8) & 0xff);    \
                (a)[3] = (u8) (((u32) (val)) & 0xff);           \
        } while (0)

#define WPA_GET_LE32(a) ((((u32) (a)[3]) << 24) | (((u32) (a)[2]) << 16) | \
                         (((u32) (a)[1]) << 8) | ((u32) (a)[0]))
#define WPA_PUT_LE32(a, val)                                    \
        do {                                                    \
                (a)[3] = (u8) ((((u32) (val)) >> 24) & 0xff);   \
                (a)[2] = (u8) ((((u32) (val)) >> 16) & 0xff);   \
                (a)[1] = (u8) ((((u32) (val)) >> 8) & 0xff);    \
                (a)[0] = (u8) (((u32) (val)) & 0xff);           \
        } while (0)

#define WPA_GET_BE64(a) ((((u64) (a)[0]) << 56) | (((u64) (a)[1]) << 48) | \
                         (((u64) (a)[2]) << 40) | (((u64) (a)[3]) << 32) | \
                         (((u64) (a)[4]) << 24) | (((u64) (a)[5]) << 16) | \
                         (((u64) (a)[6]) << 8) | ((u64) (a)[7]))
#define WPA_PUT_BE64(a, val)                            \
        do {                                            \
                (a)[0] = (u8) (((u64) (val)) >> 56);    \
                (a)[1] = (u8) (((u64) (val)) >> 48);    \
                (a)[2] = (u8) (((u64) (val)) >> 40);    \
                (a)[3] = (u8) (((u64) (val)) >> 32);    \
                (a)[4] = (u8) (((u64) (val)) >> 24);    \
                (a)[5] = (u8) (((u64) (val)) >> 16);    \
                (a)[6] = (u8) (((u64) (val)) >> 8);     \
                (a)[7] = (u8) (((u64) (val)) & 0xff);   \
        } while (0)

#define WPA_GET_LE64(a) ((((u64) (a)[7]) << 56) | (((u64) (a)[6]) << 48) | \
                         (((u64) (a)[5]) << 40) | (((u64) (a)[4]) << 32) | \
                         (((u64) (a)[3]) << 24) | (((u64) (a)[2]) << 16) | \
                         (((u64) (a)[1]) << 8) | ((u64) (a)[0]))
                         
void hmac_sha256_vector(const u8 *key, size_t key_len, size_t num_elem,
                      const u8 *addr[], const size_t *len, u8 *mac);
void hmac_sha256(const u8 *key, size_t key_len, const u8 *data,
                 size_t data_len, u8 *mac);
void sha256_prf(const u8 *key, size_t key_len, const char *label,
              const u8 *data, size_t data_len, u8 *buf, size_t buf_len);
#endif /* SHA256_H */