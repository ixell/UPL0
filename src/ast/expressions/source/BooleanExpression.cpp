#include "BooleanExpression.hpp"

BooleanExpression::BooleanExpression(bool value)
    : value(value) {}

ExpressionType BooleanExpression::get_type() const {
    return ExpressionType::BooleanExpression;
}

bool BooleanExpression::get_value() const {
    return value;
}

void change_value(bool value) {
    this->value = value;
}
