#include "StringExpression.hpp"

StringExpression::StringExpression(const std::wstring& value)
    : value(value) {}

StringExpression::StringExpression(const StringExpression& other) = default;

ExpressionType StringExpression::get_type() const {
    return ExpressionType::StringExpression;
}

StringExpression::~StringExpression() = default;

Expression* StringExpression::copy() const {
    return static_cast<Expression*>(new StringExpression(*this));
};

const std::wstring& StringExpression::get_value() const {
    return value;
}
