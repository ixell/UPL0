#include "StringExpression.hpp"

StringExpression::StringExpression(const std::wstring& value)
    : value(value) {}

ExpressionType StringExpression::get_type() const {
    return ExpressionType::StringExpression;
}

StringExpression::~StringExpression() = default;

const std::wstring& StringExpression::get_value() const {
    return value;
}
    
Expression* StringExpression::eval() const {
    return new StringExpression(*this);
}
