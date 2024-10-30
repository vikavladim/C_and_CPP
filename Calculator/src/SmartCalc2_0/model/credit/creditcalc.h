#ifndef SMARTCALC_SMARTCALC2_0_MODEL_CREDIT_CREDITCALC_H
#define SMARTCALC_SMARTCALC2_0_MODEL_CREDIT_CREDITCALC_H

#include <cmath>
#include <vector>

namespace vv {
class CreditCalc;
}  // namespace vv

/// @brief class for calculation credit
class CreditCalc {
 public:
  /// @brief constructor, which calculate credit
  /// @param sum sum of credit
  /// @param months period of credit in months
  /// @param percent interest rate of credit
  /// @param is_annual true if credit is annual, false if credit is differential
  CreditCalc(const double& sum, const int& months, const double& percent,
             const bool& is_annual);
  /// @brief getter
  /// @return tottal debt
  double get_total() const { return total_; }
  /// @brief getter
  /// @return overpayment
  double get_overpayment() const { return overpayment_; }
  /// @brief getter
  /// @return vector of monthly payment
  std::vector<double> get_monthly_payment() const { return monthly_payment_; }

 private:
  double total_ = 0;
  double overpayment_ = 0;
  std::vector<double> monthly_payment_;

  double sum_ = 0;
  int months_ = 0;
  double percent_ = 0;

  void Annual();
  void Differential();
};

#endif  // SMARTCALC_SMARTCALC2_0_MODEL_CREDIT_CREDITCALC_H
