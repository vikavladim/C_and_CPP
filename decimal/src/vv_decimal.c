
#include "vv_decimal.h"

int vv_mul(vv_decimal value_1, vv_decimal value_2, vv_decimal *result) {
  int res = OK, sign = (get_sign(value_1) + get_sign(value_2)) % 2;
  vv_decimal temp = {{0}};
  lvv_decimal a, b, c;
  to_long_dec(value_1, &a);
  to_long_dec(value_2, &b);
  to_long_dec(temp, &c);
  int scale = get_scale(value_1) + get_scale(value_2);
  res = vv_umn_bit(a, b, &c);
  to_norm(&c, &scale);
  if (scale < 0 || res != OK) res = TOO_BIG + sign;
  if (res == OK) {
    from_long_dec(c, result);
    set_sign(result, sign);
    set_scale(result, scale);
  }
  return res;
}

int vv_add(vv_decimal value_1, vv_decimal value_2, vv_decimal *result) {
  int res = OK;
  lvv_decimal a = {{0}}, b = {{0}}, c = {{0}}, d;
  lvv_decimal des = {{0, 0, 0, 0, 0, 10, 0}};
  to_long_dec(value_1, &a);
  to_long_dec(value_2, &b);
  norm_for_plus_minus(&a, &b);
  int scale = lget_scale(a), sign = 0;
  if (get_sign(value_1) == get_sign(value_2)) {
    vv_plus_bit(a, b, &c);
    sign = get_sign(value_1);
  } else {
    if (mem_dec(a, b) > 0) {
      if (get_sign(value_2) == 1)
        sign = 0;
      else
        sign = 1;
      vv_minus_bit(a, b, &c);
    } else {
      if (get_sign(value_1) == 1)
        sign = 0;
      else
        sign = 1;
      vv_minus_bit(b, a, &c);
    }
  }
  lset_sign(&c, sign);
  // to_norm(&c, &scale);
  while (((unsigned long int)lget_len(c) > 3 * 8 * sizeof(int) || scale > 28) &&
         scale >= 0) {
    scale--;
    vv_del_bit(c, des, &c, &d);
  }
  if (scale < 0) res = TOO_BIG + sign;
  if (res == OK) {
    min_scale(&c, &scale);
    from_long_dec(c, result);
    set_sign(result, sign);
    set_scale(result, scale);
  }
  return res;
}

int vv_sub(vv_decimal value_1, vv_decimal value_2, vv_decimal *result) {
  int res = OK;
  lvv_decimal a = {{0}}, b = {{0}}, c = {{0}}, d;
  lvv_decimal des = {{0, 0, 0, 0, 0, 10, 0}};
  to_long_dec(value_1, &a);
  to_long_dec(value_2, &b);
  norm_for_plus_minus(&a, &b);
  int scale = lget_scale(a), sign = 0;
  if (get_sign(value_1) != get_sign(value_2)) {
    vv_plus_bit(a, b, &c);
    sign = get_sign(value_1);
  } else {
    if (mem_dec(a, b) > 0) {
      if (get_sign(value_1) == 0)
        sign = 0;
      else
        sign = 1;
      vv_minus_bit(a, b, &c);
    } else {
      if (get_sign(value_2) == 1)
        sign = 0;
      else
        sign = 1;
      vv_minus_bit(b, a, &c);
    }
  }
  lset_sign(&c, sign);
  // to_norm(&c, &scale);
  while (((long unsigned int)lget_len(c) > 3 * 8 * sizeof(int) || scale > 28) &&
         scale >= 0) {
    scale--;
    vv_del_bit(c, des, &c, &d);
  }
  if (scale < 0) res = TOO_BIG + sign;
  if (res == OK) {
    min_scale(&c, &scale);
    from_long_dec(c, result);
    set_sign(result, sign);
    set_scale(result, scale);
  }
  return res;
}

int vv_div(vv_decimal value_1, vv_decimal value_2, vv_decimal *result) {
  int res = OK, sign = (get_sign(value_1) + get_sign(value_2)) % 2,
      to_long = OK;
  vv_decimal temp = {{0}};
  lvv_decimal a, b, c, d, temp2 = {{0}}, dva = {{0, 0, 0, 0, 0, 2, 0}},
                          nuli = {{0}};
  lvv_decimal des = {{0, 0, 0, 0, 0, 10, 0}};
  to_long_dec(value_1, &a);
  to_long_dec(value_2, &b);
  int nol1 = mem_dec(a, nuli), nol2 = mem_dec(b, nuli);
  if (nol2 == 0) return DIV_BY_ZERO;
  if (nol1 == 0) {
    memcpy(result, &temp, 4 * sizeof(int));
    return res;
  }
  to_long_dec(temp, &c);
  int scale = get_scale(value_1) - get_scale(value_2);
  memcpy(&temp2, &a, 6 * sizeof(int));
  while (to_long == OK) {
    memcpy(&a, &temp2, 6 * sizeof(int));
    to_long = vv_umn_bit(temp2, des, &temp2);
    scale++;
  }
  scale--;
  vv_del_bit(a, b, &c, &d);
  vv_umn_bit(d, dva, &d);
  lset_sign(&c, sign);
  to_norm(&c, &scale);
  if (scale < 0) res = TOO_BIG + sign;
  if (res == OK) {
    min_scale(&c, &scale);
    from_long_dec(c, result);
    set_sign(result, sign);
    set_scale(result, scale);
  }
  return res;
}

int vv_is_less(vv_decimal first, vv_decimal second) {
  int res = 0;
  if (is_eq(first, second) < 0) res = 1;
  return res;
}
int vv_is_less_or_equal(vv_decimal first, vv_decimal second) {
  int res = 0;
  if (is_eq(first, second) <= 0) res = 1;
  return res;
}
int vv_is_greater(vv_decimal first, vv_decimal second) {
  int res = 0;
  if (is_eq(first, second) > 0) res = 1;
  return res;
}
int vv_is_greater_or_equal(vv_decimal first, vv_decimal second) {
  int res = 0;
  if (is_eq(first, second) >= 0) res = 1;
  return res;
}
int vv_is_equal(vv_decimal first, vv_decimal second) {
  int res = 0;
  if (is_eq(first, second) == 0) res = 1;
  return res;
}
int vv_is_not_equal(vv_decimal first, vv_decimal second) {
  int res = 0;
  if (is_eq(first, second) != 0) res = 1;
  return res;
}

int vv_negate(vv_decimal value, vv_decimal *result) {
  int res = OK;
  memcpy(result, &value, 4 * sizeof(int));
  set_sign(result, !get_sign(value));
  return res;
}

int vv_from_int_to_decimal(int src, vv_decimal *dst) {
  int result = 0;
  int sign = (src >= 0) ? 0 : 1;  // VALUE MEANS: 1 -- negative, 0 -- positive
  src = abs(src);
  decimal_init(dst, src, 0, 0, 0);
  set_sign(dst, sign);
  return result;
}

int vv_from_float_to_decimal(float src, vv_decimal *dst) {
  vv_decimal ten = {{0}};
  vv_from_int_to_decimal(10, &ten);
  int result = 0;
  int scale = 0;
  int sign = (src >= 0) ? 0 : 1;  // VALUE MEANS: 1 -- negative, 0 -- positive
  src = fabsf(src);
  if ((src < 1e-28 && src != 0.0f) || src > 79228162514264337593543950335.0 ||
      isinf(src) || isnan(src)) {
    result = 1;
    decimal_init(dst, 0, 0, 0, 0);
  } else {
    int number = parse_float(src, &scale);
    decimal_init(dst, number, 0, 0, 0);
    set_sign(dst, sign);
    if (scale >= 0 && scale <= 28) {
      set_scale(dst, scale);
    } else if (scale < 0) {
      for (int i = 0; i < -scale; ++i) {
        vv_mul(*dst, ten, dst);
      }
    }
  }
  // printf("%d %d %d \n", dst->bits[0], dst->bits[1], dst->bits[2]);
  return result;
}

int vv_from_decimal_to_int(vv_decimal src, int *dst) {
  int result = 0;
  int sign = get_sign(src);
  vv_truncate(src, &src);
  if (src.bits[1] || src.bits[2]) {
    result = 1;
  } else {
    *dst = src.bits[0] * (1 + -2 * sign);
  }
  return result;
}

int vv_from_decimal_to_float(vv_decimal src, float *dst) {
  int result = 0;
  long double number = 0;
  long double power = 1;
  for (int i = 0; i < 96; ++i) {
    if (get_bit(src, i)) {
      number += power;
    }
    power *= 2;
  }
  for (int i = 0; i < get_scale(src); ++i) {
    number /= 10;
  }
  *dst = (get_sign(src)) ? -(float)number : (float)number;
  return result;
}

int vv_truncate(vv_decimal value, vv_decimal *result) {
  vv_decimal ten;
  vv_from_int_to_decimal(10, &ten);
  lvv_decimal lten;
  to_long_dec(ten, &lten);
  lvv_decimal lsrc;
  lvv_decimal trash;
  int result_code = 0;
  int scale = get_scale(value);
  for (int i = 0; i < scale; ++i) {
    to_long_dec(value, &lsrc);
    vv_del_bit(lsrc, lten, &lsrc, &trash);
    from_long_dec(lsrc, &value);
  }
  set_scale(&value, 0);
  decimal_init(result, value.bits[0], value.bits[1], value.bits[2],
               value.bits[3]);
  return result_code;
}

int vv_floor(vv_decimal value, vv_decimal *result) {
  vv_decimal one;
  decimal_init(&one, 1, 0, 0, 0);
  int result_code = 0;
  vv_decimal tr_value;
  int tr_result_code = vv_truncate(value, &tr_value);
  if (get_sign(value) && !vv_is_equal(value, tr_value)) {
    int minus_one_result_code = vv_sub(tr_value, one, result);
    result_code = minus_one_result_code;
  } else {
    result_code = tr_result_code;
    decimal_init(result, tr_value.bits[0], tr_value.bits[1], tr_value.bits[2],
                 tr_value.bits[3]);
  }
  return result_code;
}

int vv_round(vv_decimal value, vv_decimal *result) {
  int sign = get_sign(value);
  set_sign(&value, 0);
  vv_decimal one;
  decimal_init(&one, 1, 0, 0, 0);
  vv_decimal half;
  vv_from_float_to_decimal(0.5f, &half);
  int result_code = 0;
  vv_decimal tr_value;
  int tr_result_code = vv_truncate(value, &tr_value);
  vv_decimal value_min_tr;
  int min_tr_result_code = vv_sub(value, tr_value, &value_min_tr);
  if (vv_is_greater_or_equal(value_min_tr, half)) {
    result_code =
        tr_result_code || min_tr_result_code || vv_add(tr_value, one, result);
  } else {
    result_code = tr_result_code;
    decimal_init(result, tr_value.bits[0], tr_value.bits[1], tr_value.bits[2],
                 tr_value.bits[3]);
  }
  set_sign(result, sign);
  return result_code;
}

int vv_mod(vv_decimal value_1, vv_decimal value_2, vv_decimal *result) {
  int res = OK;
  vv_decimal temp = {{0}};
  lvv_decimal a, b, c, d, nuli = {{0}};
  to_long_dec(value_1, &a);
  to_long_dec(value_2, &b);
  int nol1 = mem_dec(a, nuli), nol2 = mem_dec(b, nuli);
  norm_for_plus_minus(&a, &b);
  int scale = lget_scale(a);
  if (nol2 == 0)
    res = DIV_BY_ZERO;
  else if (nol1 == 0 || mem_dec(a, b) < 0) {
    memcpy(result, &value_1, 4 * sizeof(int));
  } else {
    to_long_dec(temp, &c);
    vv_del_bit(a, b, &c, &d);
    to_norm(&d, &scale);
    from_long_dec(d, result);
    set_sign(result, get_sign(value_1));
    set_scale(result, scale);
  }
  return res;
}

// int main () {
//   // src1 = 0;

//   // float num = 0;

//   // vv_decimal result = {0};
//   // vv_from_float_to_decimal(num, &result);
//   // for (int i = 0; i < 4; ++i) {
//   //   printf("%d ", result.bits[i]);
//   // }
//   vv_decimal origin;
//   int code_check = 0;
//   int code = 0;
//   // src1 = 0;

//   float num = 0;

//   vv_decimal result = {0};
//   code = vv_from_float_to_decimal(num, &result);
//   origin.bits[0] = 0b00000000000000000000000000000000;
//   origin.bits[1] = 0b00000000000000000000000000000000;
//   origin.bits[2] = 0b00000000000000000000000000000000;
//   origin.bits[3] = 0b00000000000000000000000000000000;
//   int check = vv_is_equal(origin, result);

//   printf("\n%d", check);
// }
