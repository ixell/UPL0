#include "ConstantVariableExpression.hpp"

ConstantVariableExpression::ConstantVariableExpression(ptr_t<TypeExpression> type, const std::wstring& name, ptr_t<Expression> value)
    : VariableExpression(type, name), value(value) {}

ExpressionType ConstantVariableExpression::get_type() const {
    return ExpressionType::unknown;
}

const ptr_t<Expression> ConstantVariableExpression::get_value() const {
    return value;
}
