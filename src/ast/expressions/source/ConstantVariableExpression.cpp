#include "ConstantVariableExpression.hpp"

ConstantVariableExpression::ConstantVariableExpression(
    const std::wstring& type,
    const std::wstring& name,
    const std::vector<Modificator>& modificators,
    const std::vector<ptr_t<VariableExpression>>& template_,
    ptr_t<Expression> value;
) :
    VariableExpression(type, name, modificators, template_), value(value) {}

ConstantVariableExpression::ConstantVariableExpression(
    const std::wstring& type,
    const std::wstring& name,
    const std::vector<Modificator>& modificators,
    ptr_t<Expression> value
) :
    VariableExpression(type, name, modificators), value(value) {}

ConstantVariableExpression::ConstantVariableExpression(
    const std::wstring& type,
    const std::wstring& name,
    ptr_t<Expression> value
) :
    VariableExpression(type, name), value(value) {}

virtual ExpressionType ConstantVariableExpression::get_type() const override {
    return ExpressionType::unknown;
}

const ptr_t<Expression> ConstantVariableExpression::get_value() const {
    return value;
}
