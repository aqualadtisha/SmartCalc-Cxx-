//
// Created by Aqualad Tisha on 8/5/23.
//

#ifndef CPP3_SMARTCALC_V2_0_1_CALC_CONTROLLER_H
#define CPP3_SMARTCALC_V2_0_1_CALC_CONTROLLER_H

#include <utility>

#include "../model/bank_model.h"
#include "../model/calc_model.h"

namespace s21 {
class Controller {
 public:
  Controller() = default;
  explicit Controller(SimpleCalcModel *m, CreditModel *c)
      : calc_(m), credit_(c){};

  inline void StartWork(std::string expression_, long double x) {
    calc_->StartWork(std::move(expression_), x);
    status_ = calc_->Status();
  };

  inline void CalcCredit(double sum, int months, double percent, int type,
                         Payment *res) {
    credit_->StartCredit(sum, months, percent, type, res);
    status_ = credit_->Status();
  };

  inline long double ResultNum() const {
    return (calc_ == nullptr) ? 0 : calc_->ResultNum();
  }
  inline std::string Result() const {
    return (calc_ == nullptr) ? "No model" : calc_->Result();
  }
  inline bool Status() const { return status_; }
  inline bool IsCred() const { return (credit_ != nullptr); }

 private:
  bool status_ = true;

  SimpleCalcModel *calc_ = nullptr;
  CreditModel *credit_ = nullptr;
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_CALC_CONTROLLER_H
