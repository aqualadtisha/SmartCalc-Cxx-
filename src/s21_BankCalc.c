#include "s21_BankCalc.h"

RES_credit s21_credit_calc(double sum, int months, double percent, int type,
                           double table[months][5]) {
  RES_credit payment = {0};
  percent /= 100;
  if (type == annuity) {
    annuity_type(sum, months, percent, &payment);
  } else if (type == differentiated) {
    differentiated_type(sum, months, percent, &payment, table);
  } else
    payment.Error = 1;
  return payment;
}

void annuity_type(double sum, int months, double percent, RES_credit *payment) {
  payment->monthly_payment =
      (sum * (percent / 12)) / (1 - (1 / pow((1 + (percent / 12)), (months))));
  payment->total_payment = payment->monthly_payment * months;
  payment->overprice = payment->total_payment - sum;
}

void differentiated_type(double sum, int months, double percent,
                         RES_credit *payment, double table[months][5]) {
  payment->monthly_payment = sum / (months);  // monthly for main sum
  double sum_changes = sum;
  for (int i = 1; i <= months; i++) {
    double overprice =
        (sum - ((i - 1) * payment->monthly_payment)) * percent / 12;
    payment->overprice += overprice;
    sum_changes -= payment->monthly_payment;

    table[i - 1][0] = i;
    table[i - 1][1] = payment->monthly_payment + overprice;
    table[i - 1][2] = payment->monthly_payment;
    table[i - 1][3] = overprice;
    table[i - 1][4] = sum_changes;
  }
  payment->total_payment = sum + payment->overprice;
}