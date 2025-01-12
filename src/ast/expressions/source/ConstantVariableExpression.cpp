#include "ConstantVariableExpression.hpp"

ConstantVariableExpression::ConstantVariableExpression(TypeExpression* type, const std::wstring& name, Expression* value)
    : VariableExpression(type, name), value(value) {}

ExpressionType ConstantVariableExpression::get_type() const {
    return ExpressionType::unknown;
}

ConstantVariableExpression::~ConstantVariableExpression() {
    delete value;
}

const Expression* ConstantVariableExpression::get_value() const {
    return value;
}
