//
// Created by Aqualad Tisha on 8/17/23.
//
#include "calc_model.h"

namespace s21 {
void SimpleCalcModel::StartWork(std::string str, long double x) {
  expression_ = std::move(str);
  NoTabStr();

  if (expression_.empty())
    expression_ = "ERROR";
  else {
    x_ = x;
    Validate();
    if (status_ == kOk) Parse();
    if (status_ == kOk) Calculation();
    if (status_ == kOk)
      expression_ = calc_.Result();
    else
      expression_ = "ERROR";
  }
};

void SimpleCalcModel::NoTabStr() {
  auto start = expression_.begin();
  auto end = expression_.end();
  while (start != end) {
    if (*start == ' ')
      start = expression_.erase(start);
    else
      start++;
  }
}

void SimpleCalcModel::Calculation() {
  calc_ = Calculate(pars_.TakeList());
  calc_.Calculating();
  status_ = calc_.Status();
}

void SimpleCalcModel::Parse() {
  pars_ = Parser(expression_, x_);
  pars_.ParsingInit();
  status_ = pars_.Status();
}

void SimpleCalcModel::Validate() {
  valid_ = Validator(expression_);
  valid_.Validating();
  status_ = valid_.Status();
}
}  // namespace s21