#ifndef SMARTCALC_SMARTCALC2_0_MODEL_EXPRESSIONS_PARSER_H
#define SMARTCALC_SMARTCALC2_0_MODEL_EXPRESSIONS_PARSER_H

#include <cstring>
#include <queue>
#include <sstream>

#include "token.h"

namespace vv {
class MyParser;
}  // namespace vv

/// @brief Class for parsing string expression to queue of tokens struct
class MyParser {
 public:
  /// @brief Constructor, do parse for special structs of tokens
  /// @param input string with the expression
  MyParser(const std::string_view& input) : input_(input) { Parse(); }
  /// @brief getter
  /// @return queue of tokens
  std::queue<Token> get_output() const { return output; }

 private:
  std::string_view input_;
  std::queue<Token> output;
  unsigned long position = 0;
  bool next_may_be_un_ = true;

  void Parse();
  bool FindSubstring(std::string_view substr);
  bool FindNumber();
  void SkipSpaces();
  bool GetToken();
  bool FindOperation();
  // bool IsUn();
};

#endif  // SMARTCALC_SMARTCALC2_0_MODEL_EXPRESSIONS_PARSER_H
