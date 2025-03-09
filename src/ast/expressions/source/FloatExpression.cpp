#include "FloatExpression.hpp"

FloatExpression::FloatExpression(float value)
    : value(value) {}

FloatExpression::FloatExpression(const FloatExpression& other) = default;

ExpressionType FloatExpression::get_type() const {
    return ExpressionType::FloatExpression;
}

FloatExpression::~FloatExpression() = default;

Expression* FloatExpression::copy() const {
    return static_cast<Expression*>(new FloatExpression(*this));
};

float FloatExpression::get_value() const {
    return value;
}
    
Expression* FloatExpression::eval() const {
    return new FloatExpression(*this);
}
