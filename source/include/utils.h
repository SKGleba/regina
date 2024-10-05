#ifndef __UTILS_H__
#define __UTILS_H__

#include "types.h"

// atrocious, but i love it
#define p *(uint32_t*)
#define vp *(volatile uint32_t*)

// wait for ~n * 200 cycles
void delay(int n);

// get compile timestamp
__attribute__((noinline)) uint32_t get_build_timestamp(void);

// stub func for disabled features
int stub();

#endif