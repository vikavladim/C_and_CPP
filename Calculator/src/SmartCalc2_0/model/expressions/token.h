#ifndef SMARTCALC_SMARTCALC2_0_MODEL_EXPRESSIONS_TOKEN_H
#define SMARTCALC_SMARTCALC2_0_MODEL_EXPRESSIONS_TOKEN_H

// #include <any>
#include <iostream>
#include <list>
#include <ostream>

#include "enums.h"

namespace vv {
class Token;
}  // namespace vv

/// @brief struct, witch hold information about lexem of expression
struct Token {
  /// @brief type of token(number/operation)
  TypeToken what = TypeToken::kNumber;
  /// @brief value of number
  double number = 0;
  /// @brief cod of operation
  Operation operation_cod = Operation::kX;
  /// @brief priority of operation
  Priority priority = Priority::kLow;
  /// @brief empty constructor
  Token() {}
  /// @brief constructor, which create number-token
  /// @param number value of number
  Token(const double& number) : number(number) {}
  /// @brief constructor, which create operation-token, assisn priority
  /// @param cod cod of operation
  Token(const Operation& cod)
      : what(TypeToken::kOperation), operation_cod(cod) {
    SetPriority();
  }

  // Token(const Operation& cod, const std::any& func)
  //     : what(TypeToken::kOperation), operation_cod(cod), function(func) {
  //   SetPriority();
  // }
  /// @brief something like setter for priority
  void SetPriority();

  /// @brief check if token is number
  /// @return true if token is number
  bool IsNumber();

  /// @brief check if token is open parenthesis
  /// @return true if token is open parenthesis
  bool IsOpenParethesis();
  /// @brief check if token is close parenthesis
  /// @return true if token is close parenthesis
  bool IsCloseParethesis();
  /// @brief check if token is prefix function (first is operation, then
  /// operand)
  /// @return true if token is prefix function
  bool IsPrefix();
  /// @brief check if token is bin operation (need two operands for perform
  /// operation)
  /// @return true if token is bin operation
  bool IsBinOperation();
  /// @brief check if token is more priority, then param or it is left
  /// association operation
  /// @param other it, which compare with
  /// @return true if token is more priority or left association operation
  bool IsMorePriorityOrLeftAssociation(const Token& other);
  /// @brief operator for debug output
  /// @param os output
  /// @param token token
  /// @return modified output
  // friend std::ostream& operator<<(std::ostream& os, Token& token);
  // std::any function;
};

#endif  // SMARTCALC_SMARTCALC2_0_MODEL_EXPRESSIONS_TOKEN_H
