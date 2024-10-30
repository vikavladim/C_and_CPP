#if !defined(DECIMAL_UTILS_H)
#define DECIMAL_UTILS_H
#include "bit_operations.h"
#include "vv_decimal.h"
// RETURN MEANS: 1 -- negative, 0 -- positive
int get_sign(vv_decimal num);
int lget_sign(lvv_decimal num);
// VALUE MEANS: 1 -- negative, 0 -- positive
void set_sign(vv_decimal *num, int value);
void lset_sign(lvv_decimal *num, int value);
int get_scale(vv_decimal num);
void set_scale(vv_decimal *num, int scale);
int lget_scale(lvv_decimal num);
void lset_scale(lvv_decimal *num, int scale);
// RETURN {1, 0}
int get_bit(vv_decimal num, int ind);
int lget_bit(lvv_decimal num, int ind);
// VALUE {1, 0}
// void set_bit(vv_decimal *num, int ind, int value);
void lset_bit(lvv_decimal *num, int ind, int value);
// int get_len(vv_decimal num);
// int sdvig_vlevo_it(vv_decimal *n);
// int sdvig_vlevo(vv_decimal *n, int kol);
// int get_new_dec(vv_decimal star, vv_decimal *nov, int nudo);

int lget_len(lvv_decimal num);
int lsdvig_vlevo_it(lvv_decimal *n);
// int lsdvig_vlevo(lvv_decimal *n, int kol);
int lget_new_dec(lvv_decimal star, lvv_decimal *nov, int nudo);
void to_long_dec(vv_decimal star, lvv_decimal *nov);
void from_long_dec(lvv_decimal star, vv_decimal *nov);
void norm_for_plus_minus(lvv_decimal *a, lvv_decimal *b);
int is_eq(vv_decimal a, vv_decimal b);
int mem_dec(lvv_decimal a, lvv_decimal b);
int to_norm(lvv_decimal *a, int *b);
void min_scale(lvv_decimal *a, int *scale);
void decimal_init(vv_decimal *dst, int one, int two, int three, int four);
int parse_float(float src, int *scale);

// void print_dec_bits(vv_decimal a);
// void print_dec(vv_decimal a);
// void lprint_dec(lvv_decimal a);
// void lprint_dec_bits(lvv_decimal a);

#endif  // DECIMAL_UTILS_H
