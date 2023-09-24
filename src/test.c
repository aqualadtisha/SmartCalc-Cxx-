#include <check.h>

#include "s21_BankCalc.h"

START_TEST(test_s21_operands) {
  int error = 0;
  char str[25] = "-2-3";
  double res = -5.000000;
  double s = s21_SmartCalc(str, 0, &error);

  ck_assert_double_eq(s, res);
  ck_assert_int_eq(error, 0);

  char str1[25] = "2 * 3 - 4 ^ 2 + 1";
  double res1 = -9.000000;
  double a = s21_SmartCalc(str1, 0, &error);
  ck_assert_double_eq(a, res1);
  ck_assert_int_eq(error, 0);

  char str2[25] = "2^3^2";
  double res2 = 512.000000;
  double b = s21_SmartCalc(str2, 0, &error);
  ck_assert_double_eq(b, res2);
  ck_assert_int_eq(error, 0);

  char str3[25] = "1 / 2 * 4";
  double res3 = 2.000000;
  double c = s21_SmartCalc(str3, 0, &error);
  ck_assert_double_eq(c, res3);
  ck_assert_int_eq(error, 0);

  char str4[25] = "( (((1) + (1))) )";
  double res4 = 2.000000;
  double d = s21_SmartCalc(str4, 0, &error);
  ck_assert_double_eq(d, res4);
  ck_assert_int_eq(error, 0);

  char str5[25] = "(5*9)-(2+(3-(2/1)+35))";
  double res5 = 7.000000;
  double e = s21_SmartCalc(str5, 0, &error);
  ck_assert_double_eq(e, res5);
  ck_assert_int_eq(error, 0);

  char str6[55] = "3.4mod3";
  double res6 = 0.400000;
  double f = s21_SmartCalc(str6, 0, &error);
  ck_assert_int_eq((f - res6) < 1e-7, 1);
  ck_assert_int_eq(error, 0);

  char str7[25] = "(-2)^2";
  double res7 = 4.000000;
  double g = s21_SmartCalc(str7, 0, &error);
  ck_assert_double_eq(g, res7);
  ck_assert_int_eq(error, 0);

  char str8[25] = "-2^2";
  double res8 = -4.000000;
  double h = s21_SmartCalc(str8, 0, &error);
  ck_assert_double_eq(h, res8);
  ck_assert_int_eq(error, 0);

  char str9[25] = "1+1/3*2^12-44";
  double res9 = 1322.3333333;
  double k = s21_SmartCalc(str9, 0, &error);
  ck_assert_double_eq((k - res9) < 1e-7, 1);
  ck_assert_int_eq(error, 0);

  char str10[25] = "+1++1+1++1";
  double res10 = 4.000000;
  double l = s21_SmartCalc(str10, 0, &error);
  ck_assert_double_eq(l, res10);
  ck_assert_int_eq(error, 0);

  char str11[25] = "-1--1--1--1";
  double res11 = 2.000000;
  double m = s21_SmartCalc(str11, 0, &error);
  ck_assert_double_eq(m, res11);
  ck_assert_int_eq(error, 0);

  char str12[45] = "(1+2)*4*cos(3.141592*7-2)+sin(2*3.141592)";
  double res12 = 4.993811;
  double n = s21_SmartCalc(str12, 0, &error);
  ck_assert_double_eq((n - res12) < 1e-7, 1);
  ck_assert_int_eq(error, 0);

  char str13[45] = "(11) * (11)";
  double res13 = 121.000000;
  double o = s21_SmartCalc(str13, 0, &error);
  ck_assert_double_eq(o, res13);
  ck_assert_int_eq(error, 0);

  char str14[45] = "(-1)+(-(-(-(-(-(-(-1)))))))";
  double res14 = -2.000000;
  double p = s21_SmartCalc(str14, 0, &error);
  ck_assert_double_eq(p, res14);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_s21_maths) {
  int error = 0;
  char str[25] = "sin(90)";
  double res = 0.8939970;
  double s = s21_SmartCalc(str, 0, &error);
  ck_assert_double_eq((s - res) < 1e-7, 1);

  char str10[25] = "ln((9.980000)^123)";
  double res10 = 282.9717201;
  double l = s21_SmartCalc(str10, 0, &error);
  ck_assert_double_eq((l - res10) < 1e-7, 1);

  char str6[55] = "-sqrt(3.141592^log(5-3.141592))+log(55/(2+3.141592))";
  double res6 = -0.137280;
  double f = s21_SmartCalc(str6, 0, &error);
  ck_assert_double_eq((f - res6) < 1e-7, 1);
}
END_TEST

START_TEST(test_s21_errors) {
  int error = 0;

  char str[25] = "2-";
  double s = s21_SmartCalc(str, 0, &error);
  ck_assert_int_eq(-1, error);
  ck_assert_int_eq(s, 0);

  char str1[25] = "-";
  double a = s21_SmartCalc(str1, 0, &error);
  ck_assert_int_eq(0, a);
  ck_assert_int_eq(-1, error);

  char str2[25] = "sin(^)";
  double b = s21_SmartCalc(str2, 0, &error);
  ck_assert_int_eq(-1, error);
  ck_assert_int_eq(b, 0);

  char str3[25] = "sin(6-)";
  double c = s21_SmartCalc(str3, 0, &error);
  ck_assert_int_eq(c, 0);
  ck_assert_int_eq(-1, error);

  char str4[25] = "mod 2";
  double d = s21_SmartCalc(str4, 0, &error);
  ck_assert_int_eq(-1, error);
  ck_assert_int_eq(d, 0);

  char str41[25] = "2mod";
  double d1 = s21_SmartCalc(str41, 0, &error);
  ck_assert_int_eq(-1, error);
  ck_assert_int_eq(d1, 0);

  char str5[25] = "2 *";
  double e = s21_SmartCalc(str5, 0, &error);
  ck_assert_int_eq(-1, error);
  ck_assert_int_eq(e, 0);

  char str6[25] = "sin()";
  double f = s21_SmartCalc(str6, 0, &error);
  ck_assert_int_eq(-1, error);
  ck_assert_int_eq(f, 0);

  char str7[25] = "sin(30))";
  double g = s21_SmartCalc(str7, 0, &error);
  ck_assert_int_eq(-1, error);
  ck_assert_int_eq(g, 0);

  char str8[25] = "-1-1(-1)";
  double h = s21_SmartCalc(str8, 0, &error);
  ck_assert_int_eq(-1, error);
  ck_assert_int_eq(h, 0);

  char str9[25] = "-1-1=3";
  double i = s21_SmartCalc(str9, 0, &error);
  ck_assert_int_eq(-1, error);
  ck_assert_int_eq(i, 0);

  char str10[25] = "()";
  double j = s21_SmartCalc(str10, 0, &error);
  ck_assert_int_eq(-1, error);
  ck_assert_int_eq(j, 0);

  char str11[25] = ".";
  double m = s21_SmartCalc(str11, 0, &error);
  ck_assert_int_eq(-1, error);
  ck_assert_int_eq(m, 0);

  char str12[45] = "aacos(0.3)";
  double n = s21_SmartCalc(str12, 0, &error);
  ck_assert_int_eq(-1, error);
  ck_assert_int_eq(n, 0);

  char str13[45] = "sin(60)cos(60)";
  double o = s21_SmartCalc(str13, 0, &error);
  ck_assert_int_eq(-1, error);
  ck_assert_int_eq(o, 0);

  char str14[45] = " ";
  double p = s21_SmartCalc(str14, 0, &error);
  ck_assert_int_eq(-1, error);
  ck_assert_int_eq(p, 0);

  char str15[45] = "";
  double r = s21_SmartCalc(str15, 0, &error);
  ck_assert_int_eq(-1, error);
  ck_assert_int_eq(r, 0);
}
END_TEST

START_TEST(test_s21_credit) {
  RES_credit result;
  double table[12][5];
  result = s21_credit_calc(1000000, 12, 5.6, differentiated, table);

  ck_assert_double_eq(result.overprice - 30333.33 < 1e-2, 1);
  ck_assert_double_eq(result.total_payment - 1030333.33 < 1e-2, 1);
  ck_assert_int_eq(result.Error, 0);

  result = s21_credit_calc(1000000, 12, 5.6, annuity, table);
  ck_assert_double_eq(result.monthly_payment - 85882.69 < 1e-2, 1);
  ck_assert_double_eq(result.overprice - 30592.28 < 1e-2, 1);
  ck_assert_double_eq(result.total_payment - 1030592.28 < 1e-2, 1);
  ck_assert_int_eq(result.Error, 0);

  result = s21_credit_calc(1000000, 12, 5.6, 2, table);
  ck_assert_int_eq(result.Error, 1);
}
END_TEST

Suite *s21_calc_test(void) {
  Suite *s = suite_create("s21_calc_test");

  TCase *tc_s21_create_matrix = tcase_create("test_s21_operands");
  suite_add_tcase(s, tc_s21_create_matrix);
  tcase_add_test(tc_s21_create_matrix, test_s21_operands);

  TCase *tc_s21_eq_matrix = tcase_create("test_s21_errors");
  suite_add_tcase(s, tc_s21_eq_matrix);
  tcase_add_test(tc_s21_eq_matrix, test_s21_errors);
  //
  TCase *tc_s21_sum_matrix = tcase_create("test_s21_maths");
  suite_add_tcase(s, tc_s21_sum_matrix);
  tcase_add_test(tc_s21_sum_matrix, test_s21_maths);

  TCase *tc_s21_sum = tcase_create("test_s21_credit");
  suite_add_tcase(s, tc_s21_sum);
  tcase_add_test(tc_s21_sum, test_s21_credit);
  return s;
}

int main(void) {
  int number_failed = 0;
  Suite *s = s21_calc_test();
  SRunner *sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
