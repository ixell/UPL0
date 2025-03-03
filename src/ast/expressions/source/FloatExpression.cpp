#include "FloatExpression.hpp"

FloatExpression::FloatExpression(float value)
    : value(value) {}

ExpressionType FloatExpression::get_type() const {
    return ExpressionType::FloatExpression;
}

FloatExpression::~FloatExpression() = default;

float FloatExpression::get_value() const {
    return value;
}
    
Expression* FloatExpression::eval() const {
    return new FloatExpression(*this);
}
