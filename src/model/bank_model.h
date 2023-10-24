//
// Created by Aqualad Tisha on 8/17/23.
//

#ifndef CPP3_SMARTCALC_V2_0_1_BANK_MODEL_H
#define CPP3_SMARTCALC_V2_0_1_BANK_MODEL_H

#include <array>
#include <valarray>
#include <vector>
namespace s21 {

enum AllCredit { kAnnuity = 0, kDifferentiated = 1 };

struct Payment {
  using Array = std::vector<std::vector<double>>;

  double monthly_payment = 0;
  double overprice = 0;
  double total_payment = 0;
  Array table_{{}, {}, {}, {}, {}};
};

class CreditModel {
 public:
  CreditModel() = default;
  void ModelFull(double sum, int months, double percent, Payment *p);
  void StartCredit(double sum, int months, double percent, int type,
                   Payment *res);
  bool Status() const { return status_; }

 private:
  double sum_ = 0;
  double sum_changes_ = 0;
  int months_ = 0;
  double percent_ = 0;
  bool status_ = true;
  Payment *res_{};

  void Annuity();
  void Differentiated();
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_BANK_MODEL_H
