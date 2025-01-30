#include "VariableGetterExpression.hpp"

VariableGetterExpression::VariableGetterExpression(std::wstring variable)
    : variable(variable), path() {}

VariableGetterExpression::VariableGetterExpression(std::wstring variable, std::vector<std::wstring> path)
    : variable(variable), path(path) {}

ExpressionType VariableGetterExpression::get_type() const {
    return ExpressionType::VariableGetterExpression;
}

VariableGetterExpression::~VariableGetterExpression() = default;

const std::wstring& VariableGetterExpression::get_variable() const {
    return variable;
}

const std::vector<std::wstring>& VariableGetterExpression::get_path() const {
    return path;
}
