#include "parser.h"

void Token::SetPriority() {
  // if (operation_cod >= Operation::kSin && operation_cod <=
  // Operation::kMinusUn)
  //   priority = Priority::kHighest;
  if (operation_cod < Operation::kSin
      //  && operation_cod <= Operation::kPlusUn
  )
    priority = Priority::kHighest;
  if (operation_cod == Operation::kPow) priority = Priority::kHigh;
  if (operation_cod >= Operation::kMod && operation_cod <= Operation::kDiv)
    priority = Priority::kMedium;
  if (operation_cod >= Operation::kSum && operation_cod <= Operation::kSub)
    priority = Priority::kLow;
}

bool Token::IsNumber() {
  if (what == TypeToken::kNumber || operation_cod == Operation::kX) return true;
  return false;
}

bool Token::IsOpenParethesis() {
  if (what == TypeToken::kOperation &&
      operation_cod == Operation::kLeftParethesis)
    return true;
  return false;
}

bool Token::IsCloseParethesis() {
  if (what == TypeToken::kOperation &&
      operation_cod == Operation::kRightParethesis)
    return true;
  return false;
}

bool Token::IsPrefix() {
  if (
      // operation_cod >= Operation::kPlusUn &&
      operation_cod <= Operation::kSqrt)
    return true;
  return false;
}

bool Token::IsBinOperation() {
  if (operation_cod >= Operation::kPow && operation_cod <= Operation::kSub)
    return true;
  return false;
}

bool Token::IsMorePriorityOrLeftAssociation(const Token& other) {
  // if (operation_cod != Operation::kLeftParethesis &&
  //     (priority >= other.priority ||
  //      (priority == other.priority && IsBinOperation()
  //       // &&operation_cod != Operation::kPow
  //       )))
  if (IsBinOperation() &&
      (priority > other.priority ||
       (priority == other.priority && operation_cod != Operation::kPow)))
    return true;
  return false;
}

// std::ostream& operator<<(std::ostream& os, Token& token) {
//   if (token.what == TypeToken::kOperation) {
//     switch (token.operation_cod) {
//       case Operation::kX:
//         os << "kX";
//         break;
//       case Operation::kSin:
//         os << "sin";
//         break;
//       case Operation::kCos:
//         os << "cos";
//         break;
//       case Operation::kTan:
//         os << "tan";
//         break;
//       case Operation::kAsin:
//         os << "asin";
//         break;
//       case Operation::kAcos:
//         os << "acos";
//         break;
//       case Operation::kAtan:
//         os << "atan";
//         break;
//       case Operation::kLog:
//         os << "log";
//         break;
//       case Operation::kLn:
//         os << "ln";
//         break;
//       case Operation::kSqrt:
//         os << "sqrt";
//         break;
//       case Operation::kMod:
//         os << "mod";
//         break;
//       case Operation::kMul:
//         os << "*";
//         break;
//       case Operation::kPow:
//         os << "^";
//         break;
//       case Operation::kDiv:
//         os << "/";
//         break;
//       case Operation::kSum:
//       case Operation::kPlusUn:
//         os << "+";
//         break;
//       case Operation::kSub:
//       case Operation::kMinusUn:
//         os << "-";
//         break;
//       case Operation::kLeftParethesis:
//         os << "(";
//         break;
//       case Operation::kRightParethesis:
//         os << ")";
//         break;
//     }
//   } else
//     os << token.number;
//   return os;
// }
