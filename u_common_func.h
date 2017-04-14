#ifndef COMMON_FUNC_H
#define COMMON_FUNC_H

#include "u_include.h"

#define     MAX(x, y)                  (((x) > (y)) ? (x) : (y)) 
#define     MIN(x, y)                  (((x) < (y)) ? (x) : (y))

#define     ABS(x)                     ((x) >= 0 ? (x) : -(x))
#define     ABS_DIFF(x, y)             ((x) > (y) ? (x - y) : (y - x))


void Delay_Ms(uint32_t val);
void Delay_1Us(void);

#endif
