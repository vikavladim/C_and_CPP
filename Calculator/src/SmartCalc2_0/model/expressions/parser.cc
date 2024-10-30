#include "parser.h"

void MyParser::Parse() {
  while (position < input_.length()) {
    if (!GetToken()) {
      throw std::invalid_argument("Bad parse");
    }
    SkipSpaces();
  }
}

bool MyParser::FindSubstring(std::string_view substr) {
  unsigned long temp_position = position;
  if (substr.length() > input_.length() - temp_position) return false;
  for (unsigned long i = 0; i < substr.length(); ++i, ++temp_position) {
    if (substr[i] != input_[temp_position]) {
      return false;
    }
  }
  position = temp_position;
  return true;
}

bool MyParser::FindNumber() {
  std::istringstream iss{std::string(input_)};
  double number;
  iss.seekg(position, std::ios_base::beg);
  iss >> number;
  if (!iss.fail() || iss.eof()) {
    position = iss.tellg();
    output.push(Token(number));
    next_may_be_un_ = false;
  }
  return !iss.fail() || iss.eof();
}

void MyParser::SkipSpaces() {
  while (position < input_.length() && isspace(input_[position])) {
    ++position;
  }
}

bool MyParser::GetToken() { return FindOperation() || FindNumber(); }

bool MyParser::FindOperation() {
  Operation operation_cod = Operation::kX;
  bool next_may_be_un = true;
  if (FindSubstring("sin"))
    operation_cod = Operation::kSin;
  else if (FindSubstring("cos"))
    operation_cod = Operation::kCos;
  else if (FindSubstring("tan"))
    operation_cod = Operation::kTan;
  else if (FindSubstring("asin"))
    operation_cod = Operation::kAsin;
  else if (FindSubstring("acos"))
    operation_cod = Operation::kAcos;
  else if (FindSubstring("atan"))
    operation_cod = Operation::kAtan;
  else if (FindSubstring("log"))
    operation_cod = Operation::kLog;
  else if (FindSubstring("ln"))
    operation_cod = Operation::kLn;
  else if (FindSubstring("sqrt"))
    operation_cod = Operation::kSqrt;
  else if (FindSubstring("mod"))
    operation_cod = Operation::kMod;
  else if (FindSubstring("("))
    operation_cod = Operation::kLeftParethesis;
  else if (FindSubstring(")")) {
    next_may_be_un = false;
    operation_cod = Operation::kRightParethesis;
  } else if (FindSubstring("+"))
    operation_cod = next_may_be_un_ ? Operation::kPlusUn : Operation::kSum;
  else if (FindSubstring("*"))
    operation_cod = Operation::kMul;
  else if (FindSubstring("/"))
    operation_cod = Operation::kDiv;
  else if (FindSubstring("^"))
    operation_cod = Operation::kPow;
  else if (FindSubstring("x")) {
    next_may_be_un = false;
    operation_cod = Operation::kX;
  } else if (FindSubstring("-"))
    operation_cod = next_may_be_un_ ? Operation::kMinusUn : Operation::kSub;
  else
    return false;

  output.push(Token(operation_cod));
  next_may_be_un_ = next_may_be_un;
  return true;
}

// bool MyParser::IsUn() {
//   // if (output.empty() ||
//   //     (output.back().what == TypeToken::kOperation &&
//   //      output.back().operation_cod >= Operation::kSin &&
//   //      output.back().operation_cod <= Operation::kLeftParethesis)) {
//   //   return true;
//   // } else {
//   //   return false;
//   // }
//   if (next_may_be_un_) {
//     // if (prev_type_ == TypeToken::kOperation) {
//     return true;
//   } else {
//     return false;
//   }
// }