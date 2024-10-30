#ifndef SMARTCALC_SMARTCALC2_0_MODEL_EXPRESSIONS_POLISH_NOTATION_H
#define SMARTCALC_SMARTCALC2_0_MODEL_EXPRESSIONS_POLISH_NOTATION_H

#include <queue>
#include <stack>

#include "parser.h"

namespace vv {
class PolishNotation;
}  // namespace vv

/// @brief class for translation from infix notation to postfix notation
class PolishNotation {
 public:
  /// @brief getter
  /// @return queue of tokens in reverse polish notation
  std::queue<Token> get_output() const { return output_; }
  /// @brief constructor, which creates reverse polish notation
  /// @param parser class with information about structs of tokens
  PolishNotation(const MyParser& parser) : input_(parser.get_output()) {
    ValidateParenthesis();
    ToRPN();
  }
  PolishNotation(const std::queue<Token>& input) : input_(input) {
    ValidateParenthesis();
    ToRPN();
  }
  /// @brief constructor, which creates reverse polish notation
  /// @param str expression
  PolishNotation(const std::string_view& str)
      : input_(MyParser(str).get_output()) {
    ValidateParenthesis();
    ToRPN();
  }

 private:
  std::queue<Token> input_;
  std::queue<Token> output_;
  std::stack<Token> stack_;

  void ToRPN();
  void FromInputToOutput();
  void FromInputToStack();
  void FromStackToOutput();
  void OpenParethesis();
  void BinOperation();
  // void PrintAll();
  void ValidateParenthesis();
};

#endif  // SMARTCALC_SMARTCALC2_0_MODEL_EXPRESSIONS_POLISH_NOTATION_H
