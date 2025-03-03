#include "BooleanExpression.hpp"

BooleanExpression::BooleanExpression(bool value)
    : value(value) {}

ExpressionType BooleanExpression::get_type() const {
    return ExpressionType::BooleanExpression;
}

BooleanExpression::~BooleanExpression() = default;

bool BooleanExpression::get_value() const {
    return value;
}

void BooleanExpression::change_value(bool value) {
    this->value = value;
}
    
Expression* BooleanExpression::eval() const {
    return new BooleanExpression(*this);
}
