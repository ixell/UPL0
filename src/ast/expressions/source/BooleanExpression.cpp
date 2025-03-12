#include "BooleanExpression.hpp"

BooleanExpression::BooleanExpression(bool value)
    : value(value) {}

BooleanExpression::BooleanExpression(const BooleanExpression& other) = default;

ExpressionType BooleanExpression::get_type() const {
    return ExpressionType::BooleanExpression;
}

BooleanExpression::~BooleanExpression() = default;

Expression* BooleanExpression::copy() const {
    return static_cast<Expression*>(new BooleanExpression(*this));
};

bool BooleanExpression::get_value() const {
    return value;
}

void BooleanExpression::change_value(bool value) {
    this->value = value;
}
