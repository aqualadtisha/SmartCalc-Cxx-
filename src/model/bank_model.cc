//
// Created by Aqualad Tisha on 8/17/23.
//

#include "bank_model.h"
void s21::CreditModel::StartCredit(double sum, int months, double percent,
                                   int type, Payment *res) {
  ModelFull(sum, months, percent, res);
  if (type == kAnnuity) {
    Annuity();
  } else if (type == kDifferentiated) {
    Differentiated();
  } else {
    status_ = false;
  }
}
void s21::CreditModel::Annuity() {
  res_->monthly_payment =
      (sum_ * (percent_ / 12)) /
      (1 - (1 / std::pow((1 + (percent_ / 12)), (months_))));
  res_->total_payment = res_->monthly_payment * months_;
  res_->overprice = res_->total_payment - sum_;
}
void s21::CreditModel::Differentiated() {
  res_->monthly_payment = sum_ / (months_);  // monthly for main sum
  for (int i = 1; i <= months_; i++) {
    double overprice =
        (sum_ - ((i - 1) * res_->monthly_payment)) * percent_ / 12;
    res_->overprice += overprice;
    sum_changes_ -= res_->monthly_payment;

    res_->table_[0].push_back(i);
    res_->table_[1].push_back(res_->monthly_payment + overprice);
    res_->table_[2].push_back(res_->monthly_payment);
    res_->table_[3].push_back(overprice);
    res_->table_[4].push_back(sum_changes_);
  }
  res_->total_payment = sum_ + res_->overprice;
}
void s21::CreditModel::ModelFull(double sum, int months, double percent,
                                 s21::Payment *p) {
  percent_ = percent / 100;
  sum_ = sum;
  months_ = months;
  res_ = p;
  sum_changes_ = sum;
}
