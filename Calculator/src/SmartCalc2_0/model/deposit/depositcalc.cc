#include "depositcalc.h"

DepositCalc::DepositCalc(QDate start, QDate end, const double& sum,
                         const double& deposit_percent,
                         const double& tax_percent, const Period& frequency,
                         const bool& is_capitalized,
                         QVector<QPair<QDate, double>> withdraw_and_deposits)
    : start_(start),
      end_(end),
      sum_(sum),
      deposit_percent_(deposit_percent / 100),
      no_tax_sum_(tax_percent * 10000),
      frequency_(frequency),
      is_capitalized_(is_capitalized),
      day_percent_(deposit_percent / 100 /
                   (QDate::isLeapYear(start_.year()) ? 366 : 365)),
      total_(sum) {
  auto compareByDate = [](const QPair<QDate, double>& pair1,
                          const QPair<QDate, double>& pair2) -> bool {
    return pair1.first < pair2.first;
  };
  std::sort(withdraw_and_deposits.begin(), withdraw_and_deposits.end(),
            compareByDate);
  withdraw_and_deposits_ = withdraw_and_deposits;
  Calculate();
}

void DepositCalc::Calculate() {
  QDate current = start_;
  QDate last = current;
  QDate new_year(current.year(), 1, 1);
  double percents_sum = 0;
  double days = 0;
  double sum_per_year = 0;
  while (current < end_) {
    last = current;
    current = AddDays(current);
    percents_sum = 0;
    if (last.year() == current.year()) {
      percents_sum += sum_ * day_percent_ * last.daysTo(current);
      percents_sum += CalcFromDateToDate(last, current);
    } else {
      AddTax(sum_per_year);
      new_year = new_year.addYears(1);
      percents_sum += CalcFromDateToDate(last, new_year);
      percents_sum += sum_ * day_percent_ * (last.daysTo(new_year) - 1);
      day_percent_ =
          deposit_percent_ / (QDate::isLeapYear(current.year()) ? 366 : 365);
      percents_sum += sum_ * day_percent_ * (new_year.daysTo(current) + 1);
      percents_sum += CalcFromDateToDate(last, current);
    }

    if (is_capitalized_) sum_ += percents_sum;
    sum_per_year += percents_sum;
    profit_ += percents_sum;
    if (percents_sum <= 0 || sum_ <= 0) {
      throw std::invalid_argument("Invalid withdraw");
    }
    deposits_.push_back(
        std::tuple<QDate, double, double>(current, percents_sum, sum_));
  }
  AddTax(sum_per_year);
  total_ += profit_;
}

QDate DepositCalc::AddDays(QDate date) {
  switch (frequency_) {
    case Period::kDay:
      date = date.addDays(1);
      break;
    case Period::kWeek:
      date = date.addDays(7);
      break;
    case Period::kMonth:
      date = date.addMonths(1);
      break;
    case Period::kQuarter:
      date = date.addMonths(3);
      break;
    case Period::kHalfAYear:
      date = date.addMonths(6);
      break;
    case Period::kYear:
      date = date.addYears(1);
      break;
    case Period::kEndOfTerm:
      date = end_;
      break;
  }

  return date;
}

double DepositCalc::CalcWithdraw(QDate last, QDate current) {
  double percents_sum = 0;
  percents_sum += withdraw_and_deposits_.begin()->second * day_percent_ *
                  (withdraw_and_deposits_.begin()->first.daysTo(current));
  sum_ += withdraw_and_deposits_.begin()->second;
  withdraw_and_deposits_.erase(withdraw_and_deposits_.begin());
  return percents_sum;
}

double DepositCalc::CalcFromDateToDate(QDate start, QDate end) {
  double summ = 0;
  while (withdraw_and_deposits_.begin() != withdraw_and_deposits_.end() and
         start <= withdraw_and_deposits_.begin()->first and
         end >= withdraw_and_deposits_.begin()->first) {
    summ += CalcWithdraw(start, end);
  }
  return summ;
}

void DepositCalc::AddTax(double& sum_per_year) {
  if (sum_per_year - no_tax_sum_ > 0)
    tax_sum_ += (sum_per_year - no_tax_sum_) * 0.13;
  sum_per_year = 0;
}
