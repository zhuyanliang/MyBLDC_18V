#ifndef COMMON_FUNC_H
#define COMMON_FUNC_H

#include "u_include.h"

#define     MAX(x, y)                  (((x) > (y)) ? (x) : (y)) 
#define     MIN(x, y)                  (((x) < (y)) ? (x) : (y))

#define     ABS(x)                     ((x) >= 0 ? (x) : -(x))
#define     ABS_DIFF(x, y)             ((x) > (y) ? (x - y) : (y - x))


void Delay_Ms(uint32_t val);
void Delay_1Us(void);
uint16_t Calc_AverageCalculate(uint16_t *TableEntry,uint8_t len);
uint32_t Calc_AverageCalculate_32Bit(uint32_t *TableEntry,uint8_t len);


#endif
