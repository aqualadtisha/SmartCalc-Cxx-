#ifndef S21_SMARTCALC_H_
#define S21_SMARTCALC_H_
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

typedef enum {
  OK = 0,
  ERROR = 1,

  SIN = 2,
  COS = 3,
  TAN = 4,
  ASIN = 5,
  ACOS = 6,
  ATAN = 7,
  LOG = 8,
  LN = 9,
  SQRT = 10,
  unary_SUB = 11,
  SUB = 12,
  SUM = 13,
  MUL = 14,
  DIV = 15,
  POW = 16,
  MOD = 17,
  L_bracket = 18,
  R_bracket = 19,
  Number = 20,
  Function = 21,
} all;

typedef struct {
  int r_count;
  int l_count;
  int i;
  int error;
  char str[6];
  double x;
} Counts;

#define is_math_word(c)                                                 \
  (c) == 'a' || (c) == 'c' || (c) == 't' || (c) == 'l' || (c) == 's' || \
      (c) == 'm'
#define is_math_func(str)                                                    \
  !strcmp(str, "acos") || !strcmp(str, "cos") || !strcmp(str, "sin") ||      \
      !strcmp(str, "asin") || !strcmp(str, "tan") || !strcmp(str, "atan") || \
      !strcmp(str, "sqrt") || !strcmp(str, "ln") || !strcmp(str, "log") ||   \
      !strcmp(str, "mod")
#define is_numb(a) ((a) >= '0' && (a) <= '9')
#define is_point(c) c == '.'
#define is_operand(c) \
  (c) == '+' || (c) == '-' || (c) == '*' || (c) == '/' || (c) == '^'
#define is_bracket(c) (c) == '(' || (c) == ')'
#define is_word(c)                                                           \
  !(is_numb(c)) && !(is_operand(c)) && !(is_bracket(c)) && !(is_point(c)) && \
      (c) != ' '
#define is_max_priority(a, b) (a) == 8 && (b) == 8
#define is_numb_or_math(c) is_numb(c) || is_math_word(c) || (c) == 'x'

double s21_SmartCalc(const char *str, double x, int *Error);
void validator(int *line, Counts *C);
void no_tab_str(const char *str, int *line, Counts *C);
void numb_validator(const int *line, Counts *C);
void math_validator(const int *line, Counts *C);
void parsing_init(const int *line, Counts *C, LIST *root_l);
void unary_minus_add(const int *line, Counts *C, LIST *root_s, LIST *top_s);
void parser(const int *line, Counts *C, LIST *root_l, LIST *root_s, LIST *top_s,
            LIST *top_l);
void numb_add_to_list(const int *line, Counts *C, LIST *top_l, LIST *root_l);
void math_add_to_list(const int *line, Counts *C, LIST *top_s, LIST *root_l,
                      LIST *root_s);
double numb_count(const int *line, Counts *C);
void result_mul(const int *line, Counts *C, double *result, int *len);
int priority_check(int operand);
int math_check(const char *str);
int operand_check(int c);
LIST *take_from_stack(LIST *top, LIST **root_s, LIST *root_l, int priority);
double calculate(LIST *root_l, Counts *C);

#endif  // S21_SMARTCALC_H_
