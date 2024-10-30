#if !defined(BIT_OPERATIONS_H)
#define BIT_OPERATIONS_H

#include "decimal_utils.h"
#include "vv_decimal.h"
int vv_plus_bit(lvv_decimal value_1, lvv_decimal value_2, lvv_decimal *result);
int vv_minus_bit(lvv_decimal value_1, lvv_decimal value_2, lvv_decimal *result);
int vv_umn_bit(lvv_decimal value_1, lvv_decimal value_2, lvv_decimal *result);
int vv_del_bit(lvv_decimal a, lvv_decimal b, lvv_decimal *result,
               lvv_decimal *ostatok);

#endif  // BIT_OPERATIONS_H
