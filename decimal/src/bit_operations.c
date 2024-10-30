#include "bit_operations.h"

int vv_umn_bit(lvv_decimal a, lvv_decimal b, lvv_decimal *result) {
  int res = OK, len = 6 * 8 * sizeof(int) - lget_len(b) - 1;
  lvv_decimal temp = {{0, 0, 0, 0, 0, 0, 0}};
  for (int i = 6 * 8 * sizeof(int) - 1; i >= len && res == OK; i--) {
    if (lget_bit(b, i) == 1) res = vv_plus_bit(temp, a, &temp);
    if (res == OK && i > 0) res = lsdvig_vlevo_it(&a);
  }
  if (res == OK) memcpy(result, &temp, 6 * sizeof(int));
  return res;
}

int vv_del_bit(lvv_decimal a, lvv_decimal b, lvv_decimal *result,
               lvv_decimal *ostatok) {
  int res = OK, len_a = lget_len(a), len_b = lget_len(b), bit = 0;
  lvv_decimal new_a = {{0, 0, 0, 0, 0, 0, 0}};
  lvv_decimal temp_res = {{0, 0, 0, 0, 0, 0, 0}};
  lget_new_dec(a, &new_a, len_b);
  for (unsigned long i = 6 * 8 * sizeof(int) - len_a + len_b;
       i <= 6 * 8 * sizeof(int); i++) {
    if (mem_dec(new_a, b) >= 0) {
      bit = 1;
      vv_minus_bit(new_a, b, &new_a);
    } else {
      bit = 0;
    }
    lsdvig_vlevo_it(&temp_res);
    lset_bit(&temp_res, 6 * 8 * sizeof(int) - 1, bit);
    if ((unsigned long)i < 6 * 8 * sizeof(int)) {
      lsdvig_vlevo_it(&new_a);
      lset_bit(&new_a, 6 * 8 * sizeof(int) - 1, lget_bit(a, i));
    }
  }
  memcpy(result, &temp_res, 6 * sizeof(int));
  memcpy(ostatok, &new_a, 6 * sizeof(int));
  return res;
}

int vv_plus_bit(lvv_decimal value_1, lvv_decimal value_2, lvv_decimal *result) {
  int res = OK;
  int zapomnili = 0, bit = 0;
  for (int i = 6 * 8 * sizeof(int) - 1; i >= 0; i--) {
    bit = lget_bit(value_1, i) + lget_bit(value_2, i) + zapomnili;
    zapomnili = bit / 2;
    bit %= 2;
    lset_bit(result, i, bit);
  }
  if (zapomnili > 0) res = TOO_BIG;
  return res;
}

int vv_minus_bit(lvv_decimal um1, lvv_decimal vy, lvv_decimal *um) {
  int zanili = 0, bit = 0, res = OK;
  memcpy(um, &um1, 6 * sizeof(int));
  for (int i = 6 * 8 * sizeof(int) - 1; i >= 0; i--) {
    bit = lget_bit(*um, i);
    bit = bit - lget_bit(vy, i) - zanili;
    if (bit < 0) {
      bit += 2;
      zanili = 1;
    } else
      zanili = 0;
    lset_bit(um, i, bit);
  }
  if (zanili > 0) res = TOO_BIG;
  return res;
}