//
// Created by Aqualad Tisha on 8/5/23.
//

#ifndef CPP3_SMARTCALC_V2_0_1_CALC_MODEL_H
#define CPP3_SMARTCALC_V2_0_1_CALC_MODEL_H

#include <utility>

#include "calc_modules.h"

namespace s21 {

class SimpleCalcModel {
 public:
  void StartWork(std::string str, long double x);
  std::string Result() const { return expression_; }
  long double ResultNum() const { return std::stold(expression_); }
  bool Status() const { return status_; }

 private:
  bool status_ = kError;
  long double x_ = 0;
  Calculate calc_;
  Parser pars_;
  Validator valid_;
  std::string expression_{};

  void NoTabStr();
  void Calculation();
  void Parse();
  void Validate();
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_CALC_MODEL_H
