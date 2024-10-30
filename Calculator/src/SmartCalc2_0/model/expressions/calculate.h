#ifndef SMARTCALC_SMARTCALC2_0_MODEL_EXPREEIONS_CALCULATE_H
#define SMARTCALC_SMARTCALC2_0_MODEL_EXPREEIONS_CALCULATE_H

#include <stdio.h>

#include <any>
#include <array>
#include <cmath>
#include <functional>
#include <map>
#include <stdexcept>

#include "polish_notation.h"

namespace vv {
class Calculate;
}  // namespace vv

/// @brief Class for calculating expressions
class Calculate {
 public:
  /// @brief Constructor, perform operations
  /// @param pn reverse polish notation of expression
  /// @param x value of x
  Calculate(const PolishNotation& pn, const double& x)
      : input_(pn.get_output()), x_(x) {
    ReadFromInput();
  }
  /// @brief Create reverse polish notation and calculate it
  /// @param str expression
  /// @param x value of x
  Calculate(const std::string_view& str, const double& x)
      : input_(PolishNotation(str).get_output()), x_(x) {
    ReadFromInput();
  }
  /// @brief Create reverse polish notation and calculate it with x=0
  /// @param str expression
  Calculate(const std::string_view& str)
      : input_(PolishNotation(str).get_output()), x_(0) {
    ReadFromInput();
  }
  /// @brief getter
  /// @return result of expression, top of stack
  double get_result() const { return stack_.top(); }

 private:
  std::stack<double> stack_;
  std::queue<Token> input_;
  double x_ = 0;
  static std::map<Operation, std::any> operation_map_;
  void ReadFromInput();
  void PerformOperation();
  void NumberToStack();
  static std::map<Operation, std::any> CreateMap();
};

#endif  // SMARTCALC_SMARTCALC2_0_MODEL_EXPREEIONS_CALCULATE_H
