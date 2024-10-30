#include "polish_notation.h"

void PolishNotation::ToRPN() {
  while (!input_.empty()) {
    Token t = input_.front();
    if (t.IsNumber())
      FromInputToOutput();
    else if (t.IsPrefix() || t.IsOpenParethesis())
      FromInputToStack();
    else if (t.IsCloseParethesis())
      //        else if (t.operation_cod == Operation::kRightParethesis)
      OpenParethesis();
    else if (t.IsBinOperation())
      BinOperation();
    else {
      throw std::invalid_argument("Catch me! I don't know what may go bad");
    }
  }
  while (!stack_.empty()) {
    FromStackToOutput();
  }
}

void PolishNotation::FromInputToOutput() {
  output_.push(input_.front());
  input_.pop();
}

void PolishNotation::FromInputToStack() {
  stack_.push(input_.front());
  input_.pop();
}

void PolishNotation::FromStackToOutput() {
  if (stack_.top().operation_cod == Operation::kLeftParethesis) {
    throw std::invalid_argument("Mismatched right parentheses in the input");
  }
  output_.push(stack_.top());
  stack_.pop();
}

void PolishNotation::OpenParethesis() {
  while (!stack_.empty() && !stack_.top().IsOpenParethesis()) {
    FromStackToOutput();
  }
  if (stack_.empty()) {
    throw std::invalid_argument("Mismatched left parentheses in the input");
  } else
    stack_.pop();
  input_.pop();
}

void PolishNotation::BinOperation() {
  while (!stack_.empty() &&
         ((stack_.top().IsPrefix() &&
           input_.front().operation_cod != Operation::kPow) ||
          stack_.top().IsMorePriorityOrLeftAssociation(input_.front()))) {
    FromStackToOutput();
  }
  FromInputToStack();
}

// void PolishNotation::PrintAll() {
//   std::queue<Token> temp = input_;
//   std::queue<Token> temp2 = output_;
//   std::stack<Token> temp3 = stack_;
//   std::cout << "=====================\ninput: ";
//   while (!temp.empty()) {
//     std::cout << temp.front() << " ";
//     temp.pop();
//   }
//   std::cout << std::endl;
//   std::cout << "output: ";
//   while (!temp2.empty()) {
//     std::cout << temp2.front() << " ";
//     temp2.pop();
//   }
//   std::cout << std::endl;
//   std::cout << "stack: ";
//   while (!temp3.empty()) {
//     std::cout << temp3.top() << " ";
//     temp3.pop();
//   }
//   std::cout << std::endl;
// }

void PolishNotation::ValidateParenthesis() {
  auto list_tokens = input_;
  std::stack<Token> temp;
  while (!list_tokens.empty()) {
    if (!temp.empty() && temp.top().IsOpenParethesis() &&
        list_tokens.front().IsCloseParethesis()) {
      throw std::invalid_argument("Empty parentheses in the input");
    }
    temp.push(list_tokens.front());
    list_tokens.pop();
  }
}
