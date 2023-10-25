//
// Created by Aqualad Tisha on 8/17/23.
//

#include "calc_modules.h"

namespace s21 {

////////////////////////// Validator Part ////////////////////////////////

void Validator::Validating() {
  if ((IsOperand(expression_[0]) && expression_[0] != '+' &&
       expression_[0] != '-') ||
      expression_[0] == ')')
    status_ = kError;

  for (; status_ && expression_[i_] != '\0'; i_++) {

    if (IsMathWord(expression_[i_])) {  // check maths
      MathValidator();

    } else if (expression_[i_] == ')') {  // check brackets
      if (l_count_ == 0 || expression_[i_ - 1] == '(' ||
          (expression_[i_ + 1] != 'm' && IsNumbOrMath(expression_[i_ + 1]))) {
        status_ = kError;
      }
      r_count_++;

    } else if (expression_[i_] == '(') {

      if (i_ != 0 && isdigit(expression_[i_ - 1])) status_ = kError;
      l_count_++;

    } else if (isdigit(expression_[i_])) {  // check numb
      NumbValidator();

      if (expression_[i_ + 1] != '\0' &&
          (IsMathWord(expression_[i_ + 1]) && expression_[i_ + 1] != 'm')) {
        status_ = kError;
      }

    } else if (IsOperand(expression_[i_])) {  // check operands
      if (!(expression_[i_ + 1] == '+' || expression_[i_ + 1] == '-' ||
            IsNumbOrMath(expression_[i_ + 1]) || expression_[i_ + 1] == '(')) {
        status_ = kError;
      }

    } else if (expression_[i_] == 'x') {

      if (expression_[i_ + 1] == 'x') {
        status_ = kError;
      }
    } else {  // error symbols
      status_ = kError;
    }

  }

  if (r_count_ != l_count_) status_ = kError;
}

void Validator::NumbValidator() {
  int p_count = 0;
  for (; status_ && (isdigit(expression_[i_]) || expression_[i_] == '.');
       i_++) {
    if (expression_[i_] == '.') {
      if (p_count) {
        status_ = kError;
      } else {
        p_count++;
      }
    }
  }
  i_--;
}
void Validator::MathValidator() {
  int count = 0;
  int start = i_;

  while (expression_[i_] >= 'a' && 't' >= expression_[i_]) {
    count++;
    i_++;
  }

  std::string sub_str = expression_.substr(start, count);

  if (sub_str.size() > 4 || sub_str.size() < 2) status_ = kError;
  if (!(IsMath(sub_str))) status_ = kError;
  if (!sub_str.find("mod")) {
    if (i_ == 0 || !(isdigit(expression_[i_ - 4]) || expression_[i_ - 4] == ')') || !isdigit(expression_[i_]))
      status_ = kError;
  } else {
    if (expression_[i_] != '(') {
      status_ = kError;
    } else {
      l_count_++;
      if (!(IsNumbOrMath(expression_[i_ + 1]) || expression_[i_ + 1] == '(' ||
            expression_[i_ + 1] == ')' || expression_[i_ + 1] == '-'))
        status_ = kError;
    }
  }
}

///////////////////// Parsing Part //////////////////////////////

void Parser::ParsingInit() {
  for (; expression_[i_] != '\0' && status_; i_++) {
    Parsing();
  }
  TakeFromStack(0);
  stack_.clear();
}

bool Parser::UnarySubCheck() {
  bool check = false;
  if (expression_[i_] == '-' && (i_ == 0 || expression_[i_ - 1] == '(' ||
                                 IsOperand(expression_[i_ - 1]))) {
    if (IsNumbOrMath(expression_[i_ + 1]) || expression_[i_ + 1] == '(' ||
        expression_[i_ + 1] == '-' || expression_[i_ + 1] == '+') {
      stack_.emplace_back(kUnarySub, 0);
      check = true;
    } else {
      status_ = kError;
    }
  }
  return check;
}

void Parser::Parsing() {
  if (expression_[i_] == ')') {  // bracket
    TakeFromStack(0);
    if (!stack_.empty()) stack_.pop_back();
  } else if (expression_[i_] == '(') {
    stack_.emplace_back(kLBracket, 0);
  } else if (isdigit(expression_[i_]) || expression_[i_] == 'x') {
    AddNumb();
  } else if (IsOperand(expression_[i_]) && !UnarySubCheck()) {
    NewNodeAdd(expression_[i_]);
  } else if (IsMathWord(expression_[i_])) {
    AddMath();
  }
}

void Parser::NewNodeAdd(int c) {
  Node New(c, 0);
  if (!stack_.empty() && stack_.back().Priority() >= New.Priority() &&
      New.Priority() != 8) {
    TakeFromStack(New.Priority());
  }
  stack_.push_back(New);
}

void Parser::AddNumb() {
  if (expression_[i_] == 'x')
    list_.emplace_back(0, x_);
  else {
    int i = i_, p = 0;
    for (; isdigit(expression_[i_ + 1]) || expression_[i_ + 1] == '.'; i_++) {
      if (expression_[i_ + 1] == '.') p++;
    }
    if (p > 1)
      status_ = kError;
    else {
      std::string sub_str = expression_.substr(i, i_ - i + 1);
      long double numb = std::stold(sub_str);
      list_.emplace_back(0, numb);
    }
  }
}

void Parser::AddMath() {
  int count = 0;
  int start = i_;
  while (expression_[i_] >= 'a' && 't' >= expression_[i_]) {
    count++;
    i_++;
  }
  sub_str_ = expression_.substr(start, count);

  for (int i = 0; i < 10; i++)
    if (int node = opers.find(sub_str_)->second) {
      NewNodeAdd(node);
      break;
    }
  i_--;
}

void Parser::TakeFromStack(int priority) {
  auto node = stack_.back();
  while (!stack_.empty() && node.Leksema() != kLBracket &&
         priority <= node.Priority()) {
    list_.push_back(node);
    stack_.pop_back();
    node = stack_.back();
  }
}

void Calculate::Calculating() {
  auto iter = list_->begin();

  while (list_->size() > 1) {
    while (iter != list_->end() && iter->Type() != kFunction) {
      iter++;
    }
    auto leksema = iter->Leksema();
    iter--;

    if (leksema > kUnarySub || leksema == kMod) {
      auto n2 = iter->Numb();
      iter--;
      if (leksema == '+') iter->SetNumb(iter->Numb() + n2);
      if (leksema == '-') iter->SetNumb(iter->Numb() - n2);
      if (leksema == '*') iter->SetNumb(iter->Numb() * n2);
      if (leksema == '/') iter->SetNumb(iter->Numb() / n2);
      if (leksema == kMod) iter->SetNumb(fmod(iter->Numb(), n2));
      if (leksema == '^') iter->SetNumb(pow(iter->Numb(), n2));
      iter = list_->erase(++iter);
      iter = list_->erase(iter);
    } else if (iter->Leksema() == 0 && iter != --list_->end()) {
      if (leksema == kUnarySub)
        iter->SetNumb(-(iter->Numb()));
      else {
        auto map = math_function_.find(leksema);
        iter->SetNumb(map->second(iter->Numb()));
      }
      iter = list_->erase(++iter);
    } else
      status_ = kError;
  }
  status_ = list_->size() == 1 ? kOk : kError;
  if (status_) result_ = list_->front().Numb();
}

}  // namespace s21