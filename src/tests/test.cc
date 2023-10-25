//
// Created by Aqualad Tisha on 8/16/23.
//

#include <gtest/gtest.h>
#include "../controller/calc_controller.h"

#include "../model/calc_model.h"
#include "../model/bank_model.h"

namespace s21 {

  TEST(TestS21SmartCalc, Simple0) {
    SimpleCalcModel m;
    m.StartWork("2 * 3 - 4 ^ 2 + 1", 0);
    EXPECT_EQ(m.Status(), true);
    EXPECT_EQ(m.ResultNum(), -9);
  }

  TEST(TestS21SmartCalc, Simple1) {
    SimpleCalcModel m;
    m.StartWork("-2-3", 0);
    EXPECT_EQ(m.Status(), true);
    EXPECT_EQ(m.ResultNum(), -5);
  }

  TEST(TestS21SmartCalc, Simple2) {
    SimpleCalcModel m;
    m.StartWork("2^3^2", 0);
    EXPECT_EQ(m.Status(), true);
    EXPECT_EQ(m.ResultNum(), 512);
  }

  TEST(TestS21SmartCalc, Simple3) {
    SimpleCalcModel m;
    m.StartWork("1 / 2 * 4", 0);
    EXPECT_EQ(m.Status(), true);
    EXPECT_EQ(m.ResultNum(), 2);
  }

  TEST(TestS21SmartCalc, Simple5) {
    SimpleCalcModel m;
    m.StartWork("(5*9)-(2+(3-(2/1)+35))", 0);
    EXPECT_EQ(m.Status(), true);
    EXPECT_EQ(m.ResultNum(), 7);
  }


  TEST(TestS21SmartCalc, Simple6) {
    SimpleCalcModel m;
    m.StartWork("-2^2", 0);
    EXPECT_EQ(m.Status(), true);
    EXPECT_EQ(m.ResultNum(), -4);
  }

  TEST(TestS21SmartCalc, Simple7) {
    SimpleCalcModel m;
    m.StartWork("1+1/3*2^12-44", 0);
    EXPECT_EQ(m.Status(), true);
    EXPECT_EQ((m.ResultNum() - 1322.33) < 1e-2, 1);
  }

  TEST(TestS21SmartCalc, Simple8) {
    SimpleCalcModel m;
    m.StartWork("-1----1", 0);
    EXPECT_EQ(m.Status(), true);
    EXPECT_EQ(m.ResultNum(), 0);

    m.StartWork("(-1)+(-(-(-(-(-(-(-1)))))))", 0);
    EXPECT_EQ(m.Status(), true);
    EXPECT_EQ(m.ResultNum(), -2);

    m.StartWork("( (((1) + (1))) )", 0);
    EXPECT_EQ(m.Status(), true);
    EXPECT_EQ(m.ResultNum(), 2);
  }

  TEST(TestS21SmartCalc, Math0) {
    SimpleCalcModel m;
    m.StartWork("3.4mod3", 0);
    EXPECT_EQ(m.Status(), true);
    EXPECT_EQ(m.ResultNum() - 0.4 < 1e-2, 1);
  }

  TEST(TestS21SmartCalc, Math1) {
    SimpleCalcModel m;
    m.StartWork("(1+2)*4*cos(3.141592*7-2)+sin(2*3.141592)", 0);
    EXPECT_EQ(m.Status(), true);
    EXPECT_EQ(m.ResultNum(), 4.993811);
  }
  TEST(TestS21SmartCalc, Math2) {
    SimpleCalcModel m;
    m.StartWork("sin(90)", 0);
    EXPECT_EQ(m.Status(), true);
    EXPECT_EQ(m.ResultNum() - 0.8939970 < 1e-6, 1); ///0.8939970
  }

  TEST(TestS21SmartCalc, Math4) {
    SimpleCalcModel m;
    m.StartWork("ln((9.980000)^123)", 0);
    EXPECT_EQ(m.Status(), true);
    EXPECT_EQ(m.ResultNum() - 282.9717201 < 1e-3, 1);
  }

  TEST(TestS21SmartCalc, Math5) {
    SimpleCalcModel m;
    Controller c(&m, nullptr);
    c.StartWork("-sqrt(3.141592^log(5-3.141592))+log(55/(2+3.141592))", 0);
    EXPECT_EQ(m.Status(), true);
    EXPECT_EQ(m.ResultNum() + 0.137280 < 1e-5, 1);
  }

  TEST(TestS21SmartCalc, Math6) {
    SimpleCalcModel m;
    Controller c(&m, nullptr);
    c.StartWork("(((8 * 2) - (6 ^ 2)) mod 5) + 3 * 4) / (7 + 1)", 0);
    EXPECT_EQ(m.Status(), false);
  }

  TEST(TestS21SmartCalc, Math7) {
    SimpleCalcModel m;
    Controller c(&m, nullptr);
    c.StartWork("((((9 + 3) ^ 2) mod 7) + 4 * (8 - 2)) ^ 3 - 1", 0);
    EXPECT_EQ(m.Status(), true);
    EXPECT_EQ(m.ResultNum() - 21951 < 1e-5, 1);
  }

  TEST(TestS21SmartCalc, Math8) {
    SimpleCalcModel m;
    Controller c(&m, nullptr);
    c.StartWork("((asin(0.5) ^ 2) + (acos(0.3) * atan(1.2))) / (tan(45) + sin(30))", 0);
    EXPECT_EQ(m.Status(), true);
    EXPECT_EQ(m.ResultNum() - 2.189711247886146 < 1e-6, 1);
  }

  TEST(TestS21SmartCalc, Errors) {
    SimpleCalcModel m;
    m.StartWork("2-", 0);
    EXPECT_EQ(m.Status(),  false);
    EXPECT_EQ(m.Result(), "ERROR");

    m.StartWork("-", 0);
    EXPECT_EQ(m.Status(), false);
    EXPECT_EQ(m.Result(), "ERROR");

    m.StartWork("sin(^)", 0);
    EXPECT_EQ(m.Status(), false);
    EXPECT_EQ(m.Result(), "ERROR");

    m.StartWork("sin(6-)", 0);
    EXPECT_EQ(m.Status(), false);
    EXPECT_EQ(m.Result(), "ERROR");

    m.StartWork("sin( )", 0);
    EXPECT_EQ(m.Status(), false);
    EXPECT_EQ(m.Result(), "ERROR");

    m.StartWork("mod 2", 0);
    EXPECT_EQ(m.Status(), false);
    EXPECT_EQ(m.Result(), "ERROR");

    m.StartWork("2mod", 0);
    EXPECT_EQ(m.Status(), false);
    EXPECT_EQ(m.Result(), "ERROR");

    m.StartWork("sin(30))", 0);
    EXPECT_EQ(m.Status(), false);
    EXPECT_EQ(m.Result(), "ERROR");

    m.StartWork("-1-1(-1)", 0);
    EXPECT_EQ(m.Status(), false);
    EXPECT_EQ(m.Result(), "ERROR");

    m.StartWork("-1-1=3", 0);
    EXPECT_EQ(m.Status(), false);
    EXPECT_EQ(m.Result(), "ERROR");
//
    m.StartWork("()", 0);
    EXPECT_EQ(m.Status(), false);
    EXPECT_EQ(m.Result(), "ERROR");

    m.StartWork(".", 0);
    EXPECT_EQ(m.Status(), false);
    EXPECT_EQ(m.Result(), "ERROR");

    m.StartWork("aacos(0.3)", 0);
    EXPECT_EQ(m.Status(), false);
    EXPECT_EQ(m.Result(), "ERROR");

    m.StartWork("sin(60)cos(60)", 0);
    EXPECT_EQ(m.Status(), false);
    EXPECT_EQ(m.Result(), "ERROR");

    m.StartWork(" ", 0);
    EXPECT_EQ(m.Status(), false);
    EXPECT_EQ(m.Result(), "ERROR");

    m.StartWork("12 * 3.4.6 + 9", 0);
    EXPECT_EQ(m.Status(), false);
    EXPECT_EQ(m.Result(), "ERROR");

  }

  TEST(TestS21SmartCalc, Credit) {
    Payment result;
    CreditModel m;
    Controller c(nullptr, &m);

    c.CalcCredit(1000000, 12, 5.6, 1, &result);
    EXPECT_EQ(result.overprice - 30333.33 < 1e-2, 1);
    EXPECT_EQ(result.total_payment - 1030333.33 < 1e-2, 1);
    EXPECT_EQ(m.Status(), true);

    c.CalcCredit(1000000, 12, 5.6, 0, &result);
    EXPECT_EQ(result.monthly_payment - 85882.69 < 1e-2, 1);
    EXPECT_EQ(result.overprice - 30592.28 < 1e-2, 1);
    EXPECT_EQ(result.total_payment - 1030592.28 < 1e-2, 1);
    EXPECT_EQ(m.Status(), true);

    c.CalcCredit(1000000, 12, 5.6, 2, &result);
    EXPECT_EQ(m.Status(), false);
  }

}


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}