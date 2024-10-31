#include <memory>
#include <string>

#include "Common.h"

class NumberExpression : public Expression {
 public:
  NumberExpression(int value) : value_(value) {}
  int Evaluate() const { return value_; }
  std::string ToString() const { return std::to_string(value_); }

 private:
  int value_;
};

class SumExpression : public Expression {
 public:
  SumExpression(ExpressionPtr left, ExpressionPtr right)
      : left_(std::move(left)), right_(std::move(right)) {}
  int Evaluate() const { return left_->Evaluate() + right_->Evaluate(); }
  std::string ToString() const {
    return "(" + left_->ToString() + ")" + "+" + "(" + right_->ToString() + ")";
  }

 private:
  ExpressionPtr left_, right_;
};

class ProductExpression : public Expression {
 public:
  ProductExpression(ExpressionPtr left, ExpressionPtr right)
      : left_(std::move(left)), right_(std::move(right)) {}
  int Evaluate() const { return left_->Evaluate() * right_->Evaluate(); }
  std::string ToString() const {
    return "(" + left_->ToString() + ")" + "*" + "(" + right_->ToString() + ")";
  }

 private:
  ExpressionPtr left_, right_;
};

// Функции для формирования выражения
ExpressionPtr Value(int value) {
  return std::make_unique<NumberExpression>(value);
}
ExpressionPtr Sum(ExpressionPtr left, ExpressionPtr right) {
  return std::make_unique<SumExpression>(std::move(left), std::move(right));
}
ExpressionPtr Product(ExpressionPtr left, ExpressionPtr right) {
  return std::make_unique<ProductExpression>(std::move(left), std::move(right));
}
