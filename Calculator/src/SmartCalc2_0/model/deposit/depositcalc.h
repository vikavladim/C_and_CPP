#ifndef SMARTCALC_SMARTCALC2_0_MODEL_DEPOSIT_DEPOSITCALC_H
#define SMARTCALC_SMARTCALC2_0_MODEL_DEPOSIT_DEPOSITCALC_H

#include <QApplication>
#include <QDate>
#include <QDebug>
#include <QPair>
#include <QVector>
#include <algorithm>
#include <iostream>
#include <random>

namespace vv {
enum class Period;
class DepositCalc;
}  // namespace vv

/// @brief enum for frequency of interest accruals
enum class Period {
  kDay,
  kWeek,
  kMonth,
  kQuarter,
  kHalfAYear,
  kYear,
  kEndOfTerm
};

/// @brief class, wich calculate deposit
class DepositCalc {
 public:
  /// @brief getter
  /// @return total sum of deposit
  double get_total() const { return total_; }
  /// @brief getter
  /// @return deposit profit
  double get_profit() const { return profit_; }
  /// @brief getter
  /// @return sum of tax payment
  double get_tax_sum() const { return tax_sum_; }
  QVector<std::tuple<QDate, double, double>> get_deposits() const {
    return deposits_;
  }

  DepositCalc(QDate start, QDate end, const double& sum,
              const double& deposit_percent, const double& tax_percent,
              const Period& frequency, const bool& is_capitalized,
              QVector<QPair<QDate, double>> withdraw_and_deposits);

 private:
  QDate start_;
  QDate end_;
  double sum_ = 0;
  double deposit_percent_ = 0;
  double no_tax_sum_ = 0;
  Period frequency_ = Period::kMonth;
  bool is_capitalized_ = true;
  QVector<QPair<QDate, double>> withdraw_and_deposits_;

  double day_percent_ = 0;

  double total_ = 0;
  double profit_ = 0;
  double tax_sum_ = 0;
  QVector<std::tuple<QDate, double, double>> deposits_;

  void Calculate();
  QDate AddDays(QDate date);
  double CalcWithdraw(QDate last, QDate current);
  double CalcFromDateToDate(QDate start_, QDate end_);
  void AddTax(double& sum_per_year);
};
#endif  // SMARTCALC_SMARTCALC2_0_MODEL_DEPOSIT_DEPOSITCALC_H