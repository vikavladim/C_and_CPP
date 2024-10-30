#include "calculate.h"

std::map<Operation, std::any> Calculate::operation_map_ =
    Calculate::CreateMap();

void Calculate::ReadFromInput() {
  while (!input_.empty()) {
    if (input_.front().what == TypeToken::kNumber ||
        input_.front().operation_cod == Operation::kX)
      NumberToStack();
    else
      PerformOperation();
    input_.pop();
  }
  if (stack_.size() < 1) {
    throw std::invalid_argument(
        "Some lexemes were not recognized in the input");
  }
  if (stack_.size() > 1) {
    throw std::invalid_argument("Missed operation");
  }
}

void Calculate::PerformOperation() {
  double result = 0;
  if (input_.front().IsBinOperation()) {
    if (stack_.size() < 2) {
      throw std::invalid_argument(
          "Insufficient operands in the stack to perform the operation");
    }
    double second = stack_.top();
    stack_.pop();
    double first = stack_.top();
    stack_.pop();
    result = std::any_cast<std::function<double(double, double)>>(
        operation_map_[input_.front().operation_cod])(first, second);
  } else {
    if (stack_.size() < 1) {
      throw std::invalid_argument(
          "Insufficient operands in the stack to perform the operation");
    }
    double first = stack_.top();
    stack_.pop();
    result = std::any_cast<std::function<double(double)>>(
        operation_map_[input_.front().operation_cod])(first);
  }
  stack_.push(result);
}

void Calculate::NumberToStack() {
  if (input_.front().what == TypeToken::kOperation)
    stack_.push(x_);
  else
    stack_.push(input_.front().number);
}

std::map<Operation, std::any> Calculate::CreateMap() {
  std::map<Operation, std::any> map;
  map[Operation::kPlusUn] =
      std::function<double(double)>([](double a) { return a; });
  map[Operation::kMinusUn] =
      std::function<double(double)>([](double a) { return -a; });
  map[Operation::kSin] =
      std::function<double(double)>(static_cast<double (*)(double)>(sin));
  map[Operation::kCos] =
      std::function<double(double)>(static_cast<double (*)(double)>(cos));
  map[Operation::kTan] =
      std::function<double(double)>(static_cast<double (*)(double)>(tan));
  map[Operation::kAsin] =
      std::function<double(double)>(static_cast<double (*)(double)>(asin));
  map[Operation::kAcos] =
      std::function<double(double)>(static_cast<double (*)(double)>(acos));
  map[Operation::kAtan] =
      std::function<double(double)>(static_cast<double (*)(double)>(atan));
  map[Operation::kLog] =
      std::function<double(double)>(static_cast<double (*)(double)>(log10));
  map[Operation::kLn] =
      std::function<double(double)>(static_cast<double (*)(double)>(log));
  map[Operation::kSqrt] =
      std::function<double(double)>(static_cast<double (*)(double)>(sqrt));
  map[Operation::kPow] = std::function<double(double, double)>(
      static_cast<double (*)(double, double)>(pow));
  map[Operation::kMod] =
      std::function<double(double, double)>([](double a, double b) {
        double c = fmod(a, b);
        if (c < 0) c += b;
        return c;
      });
  map[Operation::kMul] = std::function<double(double, double)>(
      [](double a, double b) { return a * b; });
  map[Operation::kDiv] = std::function<double(double, double)>(
      [](double a, double b) { return a / b; });
  map[Operation::kSum] = std::function<double(double, double)>(
      [](double a, double b) { return a + b; });
  map[Operation::kSub] = std::function<double(double, double)>(
      [](double a, double b) { return a - b; });
  return map;
}