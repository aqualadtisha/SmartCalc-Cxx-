#ifndef C7_SMARTCALC_V1_0_0_SRC_S21_BANKCALC_H_
#define C7_SMARTCALC_V1_0_0_SRC_S21_BANKCALC_H_

#include "s21_SmartCalc.h"

typedef enum {
  annuity = 0,
  differentiated = 1,
} Type;

typedef struct {
  double monthly_payment;
  double overprice;
  double total_payment;
  int Error;
} RES_credit;

RES_credit s21_credit_calc(double sum, int months, double percent, int type,
                           double table[months][5]);
void annuity_type(double sum, int months, double percent, RES_credit *payment);
void differentiated_type(double sum, int months, double percent,
                         RES_credit *payment, double table[months][5]);

#endif  // C7_SMARTCALC_V1_0_0_SRC_S21_BANKCALC_H_
