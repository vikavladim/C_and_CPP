#if !defined(VV_DECIMAL_H)
#define VV_DECIMAL_H

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 0
#define TOO_BIG 1  // число слишком велико или равно бесконечности
#define TOO_SMALL 2  // число слишком мало или равно отрицательной бесконечности
#define DIV_BY_ZERO 3  // деление на 0

typedef struct decimal_t {
  int bits[4];
} vv_decimal;

typedef struct decimal_t_long {
  int bits[7];
} lvv_decimal;

#include "decimal_utils.h"

int vv_mul(vv_decimal value_1, vv_decimal value_2, vv_decimal *result);
int vv_add(vv_decimal value_1, vv_decimal value_2, vv_decimal *result);
int vv_sub(vv_decimal value_1, vv_decimal value_2, vv_decimal *result);
int vv_div(vv_decimal value_1, vv_decimal value_2, vv_decimal *result);
int vv_mod(vv_decimal value_1, vv_decimal value_2, vv_decimal *result);

int vv_is_less(vv_decimal, vv_decimal);
int vv_is_less_or_equal(vv_decimal, vv_decimal);
int vv_is_greater(vv_decimal, vv_decimal);
int vv_is_greater_or_equal(vv_decimal, vv_decimal);
int vv_is_equal(vv_decimal, vv_decimal);
int vv_is_not_equal(vv_decimal, vv_decimal);
int vv_negate(vv_decimal value, vv_decimal *result);
int vv_from_int_to_decimal(int src, vv_decimal *dst);
int vv_from_float_to_decimal(float src, vv_decimal *dst);
int vv_from_decimal_to_int(vv_decimal src, int *dst);
int vv_from_decimal_to_float(vv_decimal src, float *dst);
int vv_truncate(vv_decimal value, vv_decimal *result);
int vv_round(vv_decimal value, vv_decimal *result);
int vv_floor(vv_decimal value, vv_decimal *result);

#endif  // VV_DECIMAL_H
