#ifndef __UTILS_H__
#define __UTILS_H__

#include "types.h"

// atrocious, but i love it
#define p *(uint32_t*)
#define vp *(volatile uint32_t*)
#define v8p *(volatile uint8_t*)
#define v16p *(volatile uint16_t*)
#define v32p *(volatile uint32_t*)
#define v64p *(volatile uint64_t*)

#define BITF(n) (~(-1 << (n)))
#define BITFL(n) (BITF((n) + 1))
#define BITN(n) (1 << (n))
#define BITNVAL(n, val) ((val) << (n))
#define BITNVALM(n, val, mask) (((val) & (mask)) << (n))
#define XBITN(v, n) (((v) >> (n)) & 1)
#define XBITNVALM(v, n, mask) (((v) >> (n)) & (mask))

#define _AGX_SYNC_ __asm("sync");

// wait for ~n * 200 cycles
void delay(int n);

// get compile timestamp
__attribute__((noinline)) uint32_t get_build_timestamp(void);

// stub func for disabled features
int stub();

#endif