/// @brief
/// \file
/// All enums. Using for struct token.
#ifndef SMARTCALC_SMARTCALC2_0_MODEL_EXPREEIONS_ENUMS_H
#define SMARTCALC_SMARTCALC2_0_MODEL_EXPREEIONS_ENUMS_H

namespace vv {
enum class Operation;
enum class TypeToken;
enum class Priority;
}  // namespace vv

/// @brief Class with different types of math operations. For example sin, sub,
/// etc
enum class Operation {
  kPlusUn,
  kMinusUn,
  kSin,
  kCos,
  kTan,
  kAsin,
  kAcos,
  kAtan,
  kLog,
  kLn,
  kSqrt,
  kPow,
  kMod,
  kMul,
  kDiv,
  kSum,
  kSub,
  kLeftParethesis,
  kRightParethesis,
  kX
};

/// @brief Class with types of tokens of the expression. It may be number or
/// operation
enum class TypeToken { kNumber, kOperation };

/// @brief Types of priorities of operations. For example, multiplication has
/// more higher priority then subtraction
enum class Priority { kLow, kMedium, kHigh, kHighest };

#endif  // SMARTCALC_SMARTCALC2_0_MODEL_EXPREEIONS_ENUMS_H