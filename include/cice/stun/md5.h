/*
 * MD5 hash implementation and interface functions
 * Copyright (c) 2003-2005, Jouni Malinen <j@w1.fi>
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

#ifndef MD5_H
#define MD5_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
#include "win32_common.h"
#else
#include <stdint.h>
#endif
#include <stddef.h>

#define MD5_MAC_LEN 16

struct MD5Context {
  uint32_t buf[4];
  uint32_t bits[2];
  union {
    uint8_t u8[64];
    uint32_t u32[16];
  } in;
};

typedef struct MD5Context MD5_CTX;

void MD5Init(MD5_CTX *context);
void MD5Update(MD5_CTX *context, unsigned char const *buf, unsigned len);
void MD5Final(unsigned char digest[16], MD5_CTX *context);


#ifdef __cplusplus
}
#endif

#endif /* MD5_H */
