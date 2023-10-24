//
// Created by Aqualad Tisha on 8/6/23.
//

#ifndef CPP3_SMARTCALC_V2_0_1_CALC_MODULES_H
#define CPP3_SMARTCALC_V2_0_1_CALC_MODULES_H

#include <array>
#include <cmath>
#include <iostream>
#include <list>
#include <map>
#include <regex>
#include <stack>
#include <utility>

enum All {
  kOk = true,
  kError = false,
  kSin = 2,
  kCos = 3,
  kTan = 4,
  kAsin = 5,
  kAcos = 6,
  kAtan = 7,
  kLog = 8,
  kLn = 9,
  kSqrt = 10,
  kMod = 11,
  kUnarySub = 12,
  kLBracket = 14,
  kNumber = 20,
  kFunction = 21,
};

namespace s21 {

inline static bool IsMathWord(char c);
inline static bool IsMath(const std::string& str);
inline static bool IsOperand(char c);
inline static bool IsNumbOrMath(char c);

inline static bool IsMathWord(char c) {
  std::string sub = "actlsm";
  return (sub.find(c) != std::string::npos);
}

inline static bool IsMath(const std::string& str) {
  return str == "acos" || str == "cos" || str == "sin" || str == "asin" ||
         str == "tan" || str == "atan" || str == "sqrt" || str == "ln" ||
         str == "log" || str == "mod";
}

inline static bool IsOperand(char c) {
  std::string sub = "+-*/^";
  return (sub.find(c) != std::string::npos);
}
inline static bool IsNumbOrMath(char c) {
  return isdigit(c) || c == 'x' || IsMathWord(c);
}

const static std::map<int, long double (*)(long double)> math_function_ = {
    {kSin, std::sin},   {kAsin, std::asin}, {kCos, std::cos},
    {kAcos, std::acos}, {kTan, std::tan},   {kAtan, std::atan},
    {kLog, std::log10}, {kLn, std::log},    {kSqrt, std::sqrt}};

const static std::map<std::string, int> opers = {
    {"sin", 2},  {"cos", 3}, {"tan", 4}, {"asin", 5},  {"acos", 6},
    {"atan", 7}, {"log", 8}, {"ln", 9},  {"sqrt", 10}, {"mod", 11}};

class Node {
 public:
  Node(int type, long double number) {
    if (!type) {
      numb_ = number;
      type_ = kNumber;
    } else {
      leksema_ = type;
      PriorityCheck();
    }
  };

  void PriorityCheck() {
    if (leksema_ == kMod){
      priority_ = 6;
    } else if (leksema_ == '*' || leksema_ == '/') {
      priority_ = 2;
    } else if (leksema_ == '-' || leksema_ == '+') {
      priority_ = 1;
    } else if (leksema_ == kLBracket) {
      priority_ = 0;
    }
    type_ = kFunction;
  };

  int Priority() const { return priority_; }
  int Leksema() const { return leksema_; }
  long double Numb() const { return numb_; }
  int Type() const { return type_; }
  void SetNumb(long double n) { numb_ = n; }

 private:
  int leksema_ = 0;
  long double numb_ = 0;
  int priority_ = 8;
  int type_ = 0;
};

class Calculate {
 public:
  Calculate() = default;
  explicit Calculate(std::list<Node>& l) : list_(&l){};

  void Calculating();
  bool Status() const { return status_; }
  std::string Result() const { return std::to_string(result_); };

 private:
  bool status_ = kOk;
  long double result_ = 0;
  std::list<Node>* list_ = nullptr;
};

class Validator {
 public:
  Validator() = default;
  explicit Validator(std::string str) : expression_(std::move(str)){};

  void Validating();
  void NumbValidator();
  void MathValidator();

  bool Status() const { return status_; }

 private:
  bool status_ = kOk;
  int i_ = 0;
  int l_count_ = 0;
  int r_count_ = 0;
  std::string expression_;
};

class Parser {
 public:
  Parser() = default;
  explicit Parser(std::string str, long double x)
      : expression_(std::move(str)), x_(x){};

  void ParsingInit();
  bool Status() const { return status_; }
  std::list<Node>& TakeList() { return list_; }

 private:
  std::string expression_{};
  long double x_ = 0;
  bool status_ = kOk;
  int i_ = 0;
  std::string sub_str_{};
  std::list<Node> list_{};
  std::list<Node> stack_{};

  bool UnarySubCheck();
  void Parsing();
  void NewNodeAdd(int c);
  void AddNumb();
  void AddMath();
  void TakeFromStack(int priority);
};
}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_CALC_MODULES_H
