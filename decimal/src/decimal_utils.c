#include "decimal_utils.h"

int get_sign(vv_decimal num) { return (num.bits[3] >> 31) & 1; }

void set_sign(vv_decimal *num, int value) {
  if (value) {
    num->bits[3] |= (1 << 31);
  } else {
    num->bits[3] &= ~(1 << 31);
  }
}

int get_scale(vv_decimal num) { return (num.bits[3] >> 16) & 31; }

void set_scale(vv_decimal *num, int scale) {
  int sign = get_sign(*num);
  num->bits[3] = scale << 16;
  set_sign(num, sign);
}

// int get_len(vv_decimal num) {
//   int len = 0, bit = 0;
//   while ((unsigned long)len < 3 * 8 * sizeof(int) && bit == 0) {
//     bit = get_bit(num, len);
//     len++;
//   }
//   return 3 * 8 * sizeof(int) - len;
// }

int get_bit(vv_decimal num, int ind) {
  assert(ind < 96);
  return (num.bits[ind / 32] >> (ind % 32)) & 1;
}

// void set_bit(vv_decimal *num, int ind, int value) {
//   assert(ind < 96);
//   if (value) {
//     num->bits[ind / 32] |= 1 << (31 - (ind % 32));
//   } else {
//     num->bits[ind / 32] &= ~(1 << (31 - (ind % 32)));
//   }
// }

// int sdvig_vlevo_it(vv_decimal *n) {
//   int res = OK;
//   int first_bit1 = get_bit(*n, 0 * sizeof(int) * 8);
//   if (first_bit1 == 0) {
//     int first_bit3 = get_bit(*n, 2 * sizeof(int) * 8);
//     int first_bit2 = get_bit(*n, 1 * sizeof(int) * 8);
//     n->bits[2] <<= 1;
//     n->bits[1] <<= 1;
//     n->bits[0] <<= 1;
//     set_bit(n, 2 * sizeof(int) * 8 - 1, first_bit3);
//     set_bit(n, 1 * sizeof(int) * 8 - 1, first_bit2);
//   } else
//     res = TOO_BIG;
//   return res;
// }

// int sdvig_vlevo(vv_decimal *n, int kol) {
//   int res = OK;
//   for (int i = 0; i < kol && res == OK; i++) res = sdvig_vlevo_it(n);
//   return res;
// }

// int get_new_dec(vv_decimal star, vv_decimal *nov, int nudo) {
//   int bit = 0, len = get_len(star);
//   vv_decimal temp = {{0, 0, 0, 0}};
//   memcpy(nov, &temp, 3 * sizeof(int));
//   for (int i = 0; i < nudo; i++) {
//     bit = get_bit(star, 3 * 8 * sizeof(int) - len + i);
//     set_bit(nov, 3 * 8 * sizeof(int) - nudo + i, bit);
//   }
//   return OK;
// }

void to_long_dec(vv_decimal star, lvv_decimal *nov) {
  lvv_decimal u = {{0, 0, 0, 0, 0, 0, 0}};
  memcpy(nov, &u, 7 * sizeof(int));
  nov->bits[6] = star.bits[3];
  nov->bits[5] = star.bits[0];
  nov->bits[4] = star.bits[1];
  nov->bits[3] = star.bits[2];
}

void from_long_dec(lvv_decimal star, vv_decimal *nov) {
  vv_decimal u = {{0}};
  memcpy(nov, &u, 4 * sizeof(int));
  nov->bits[0] = star.bits[5];
  nov->bits[1] = star.bits[4];
  nov->bits[2] = star.bits[3];
  nov->bits[3] = star.bits[6];
}

int lget_sign(lvv_decimal num) { return (num.bits[6] >> 31) & 1; }

void lset_sign(lvv_decimal *num, int value) {
  int sign = lget_sign(*num);
  if ((!sign && value) || (sign && !value)) {
    num->bits[6] ^= 1 << 31;
  }
}

int lget_scale(lvv_decimal num) { return (num.bits[6] >> 16) & 31; }

void lset_scale(lvv_decimal *num, int scale) {
  int sign = lget_sign(*num);
  num->bits[6] = scale << 16;
  lset_sign(num, sign);
}

int lget_len(lvv_decimal num) {
  int len = 0, bit = 0;
  while ((unsigned long)len < 6 * 8 * sizeof(int) && bit == 0) {
    bit = lget_bit(num, len);
    len++;
  }
  if (bit != 0) len--;
  return 6 * 8 * sizeof(int) - len;
}

int lget_bit(lvv_decimal num, int ind) {
  assert(ind < 96 * 2);
  return (num.bits[ind / 32] >> (31 - (ind % 32))) & 1;
}

void lset_bit(lvv_decimal *num, int ind, int value) {
  assert(ind < 96 * 2);
  if (value) {
    num->bits[ind / 32] |= 1 << (31 - (ind % 32));
  } else {
    num->bits[ind / 32] &= ~(1 << (31 - (ind % 32)));
  }
}

int lsdvig_vlevo_it(lvv_decimal *n) {
  int res = OK;
  int first_bit1 = lget_bit(*n, 0 * sizeof(int) * 8);
  if (first_bit1 == 0) {
    int first_bit3 = lget_bit(*n, 2 * sizeof(int) * 8);
    int first_bit2 = lget_bit(*n, 1 * sizeof(int) * 8);
    int first_bit4 = lget_bit(*n, 3 * sizeof(int) * 8);
    int first_bit5 = lget_bit(*n, 4 * sizeof(int) * 8);
    int first_bit6 = lget_bit(*n, 5 * sizeof(int) * 8);
    n->bits[2] <<= 1;
    n->bits[1] <<= 1;
    n->bits[0] <<= 1;
    n->bits[3] <<= 1;
    n->bits[4] <<= 1;
    n->bits[5] <<= 1;
    lset_bit(n, 2 * sizeof(int) * 8 - 1, first_bit3);
    lset_bit(n, 1 * sizeof(int) * 8 - 1, first_bit2);
    lset_bit(n, 3 * sizeof(int) * 8 - 1, first_bit4);
    lset_bit(n, 4 * sizeof(int) * 8 - 1, first_bit5);
    lset_bit(n, 5 * sizeof(int) * 8 - 1, first_bit6);
  } else
    res = TOO_BIG;
  return res;
}

// int lsdvig_vlevo(lvv_decimal *n, int kol) {
//   int res = OK;
//   for (int i = 0; i < kol && res == OK; i++) res = lsdvig_vlevo_it(n);
//   return res;
// }

int lget_new_dec(lvv_decimal star, lvv_decimal *nov, int nudo) {
  int bit = 0, len = lget_len(star);
  lvv_decimal temp = {{0, 0, 0, 0, 0, 0, 0}};
  memcpy(nov, &temp, 6 * sizeof(int));
  if (len <= nudo) {
    memcpy(nov, &star, 6 * sizeof(int));
  } else {
    for (int i = 0; i < nudo; i++) {
      bit = lget_bit(star, 6 * 8 * sizeof(int) - len + i);
      lset_bit(nov, 6 * 8 * sizeof(int) - nudo + i, bit);
    }
  }
  return OK;
}

void norm_for_plus_minus(lvv_decimal *a, lvv_decimal *b) {
  lvv_decimal des = {{0, 0, 0, 0, 0, 10, 0}};
  int scale_a = lget_scale(*a), scale_b = lget_scale(*b);
  while (scale_a > scale_b) {
    vv_umn_bit(*b, des, b);
    scale_b++;
  }
  while (scale_a < scale_b) {
    vv_umn_bit(*a, des, a);
    scale_a++;
  }
  lset_scale(a, scale_a);
  lset_scale(b, scale_b);
}

int is_eq(vv_decimal first, vv_decimal second) {
  lvv_decimal a = {0}, b = {0}, nuli = {0};
  to_long_dec(first, &a);
  to_long_dec(second, &b);
  norm_for_plus_minus(&a, &b);
  int znak1 = lget_sign(a), znak2 = lget_sign(b), mem = mem_dec(a, b), res = 0;
  if (memcmp(&a, &nuli, 6 * sizeof(int)) == 0 &&
      memcmp(&b, &nuli, 6 * sizeof(int)) == 0)
    res = 0;
  else if (!znak1 && !znak2) {
    res = mem;
  } else if (znak1 && znak2)
    res = -mem;
  else if (znak1)
    res = -1;
  else
    res = 1;
  return res;
}

int mem_dec(lvv_decimal a, lvv_decimal b) {
  int res = 0;
  for (unsigned long i = 0; i < 6 * 8 * sizeof(int) && res == 0; i++)
    res = lget_bit(a, i) - lget_bit(b, i);
  return res;
}

int to_norm(lvv_decimal *a, int *scale) {  // здесь надо что-нибудь возвращать
  int res = OK;
  lvv_decimal des = {{0, 0, 0, 0, 0, 10, 0}}, odin = {{0, 0, 0, 0, 0, 1, 0}},
              ostatok = {{0}};
  while (((unsigned long)lget_len(*a) > 3 * 8 * sizeof(int) || *scale > 28) &&
         *scale >= 0) {
    *scale -= 1;
    vv_del_bit(*a, des, a, &ostatok);
  }  //|| (ostatok.bits[5] == 5 && lget_bit(*a, 95) == 1)
  if (ostatok.bits[5] >= 5) {
    vv_plus_bit(*a, odin, a);
    res = to_norm(a, scale);
  }
  return res;
}

void min_scale(lvv_decimal *a, int *scale) {
  lvv_decimal temp2 = {{0}}, des = {{0, 0, 0, 0, 0, 10, 0}}, d = {{0}},
              nuli = {{0}};
  memcpy(&temp2, a, 6 * sizeof(int));
  while (mem_dec(nuli, d) == 0 && *scale >= 0) {
    memcpy(a, &temp2, 6 * sizeof(int));
    vv_del_bit(temp2, des, &temp2, &d);
    *scale -= 1;
  }
  *scale += 1;
}

void decimal_init(vv_decimal *dst, int one, int two, int three, int four) {
  dst->bits[0] = one;
  dst->bits[1] = two;
  dst->bits[2] = three;
  dst->bits[3] = four;
}

int parse_float(float src, int *scale) {
  char exp_string[20] = {0};
  char number_string[20] = {0};
  number_string[0] = '0';
  int number;
  sprintf(exp_string, "%.6E", src);
  int exp;
  char n1;
  char n2[7];
  sscanf(exp_string, "%c.%6sE%d", &n1, n2, &exp);
  sprintf(number_string, "%c%s", n1, n2);
  *scale = strlen(number_string) - exp - 1;
  for (int i = strlen(number_string) - 1; i >= 0; --i) {
    if (number_string[i] == '0' && i != 0) {
      number_string[i] = '\0';
      --(*scale);
    } else {
      break;
    }
  }
  sscanf(number_string, "%d", &number);
  return number;
}

// void print_dec_bits(vv_decimal a) {
//   printf("znak=%c stepen=%d\n", get_sign(a), get_scale(a));
//   // for (int i = 3 * 8 * sizeof(int); i < 4 * 8 * sizeof(int); i++)
//   //   printf("%d", lget_bit(*((lvv_decimal *)&a), i));
//   // printf("\n");
//   for (int i = 0; i < 3 * 8 * sizeof(int); i++) {
//     printf("%d", get_bit(a, i));
//   }
//   printf("\n");
// }

// void lprint_dec_bits(lvv_decimal a) {
//   printf("znak=%c stepen=%d\n", lget_sign(a), lget_scale(a));
//   // for (int i = 3 * 8 * sizeof(int); i < 4 * 8 * sizeof(int); i++)
//   //   printf("%d", lget_bit(*((lvv_decimal *)&a), i));
//   // printf("\n");
//   for (int i = 0; i < 6 * 8 * sizeof(int); i++) {
//     printf("%d", lget_bit(a, i));
//   }
//   printf("\n");
// }

// void print_dec(vv_decimal a) {
//   printf("znak=%c stepen=%d\n", get_sign(a) == 1 ? '-' : '+', get_scale(a));
//   for (int i = 0; i < 3; i++) {
//     printf("%d ", a.bits[i]);
//   }
//   printf("\n");
// }

// void lprint_dec(lvv_decimal a) {
//   printf("znak=%c stepen=%d\n", lget_sign(a) == 1 ? '-' : '+',
//   lget_scale(a)); for (int i = 0; i < 6; i++) {
//     printf("%d ", a.bits[i]);
//   }
//   printf("\n");
// }
