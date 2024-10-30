#include "creditcalc.h"

#include <iostream>

CreditCalc::CreditCalc(const double& sum, const int& months,
                       const double& percent, const bool& is_annual)
    : sum_(sum), months_(months), percent_(percent / 12 / 100) {
  // Validate();
  if (is_annual)
    Annual();
  else
    Differential();
  overpayment_ = total_ - sum_;
}

void CreditCalc::Annual() {
  double result =
      sum_ *
      (percent_ +
       percent_ / (pow(1. + percent_, static_cast<double>(months_)) - 1.));
  for (int i = 0; i < months_; ++i) {
    monthly_payment_.push_back(result);
    total_ += monthly_payment_[i];
  }
}

void CreditCalc::Differential() {
  for (int i = 0; i < months_; ++i) {
    double remains = sum_ - sum_ * i / static_cast<double>(months_);
    monthly_payment_.push_back(sum_ / static_cast<double>(months_) +
                               remains * percent_);
    total_ += monthly_payment_[i];
  }
}
