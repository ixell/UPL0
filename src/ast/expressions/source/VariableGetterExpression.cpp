#include "VariableGetterExpression.hpp"

VariableGetterExpression::VariableGetterExpression(
        const std::wstring& variable,
        const std::vector<std::wstring>& path,
        const std::vector<Expression*>& template_)
    : variable(variable), path(path), template_(template_) {}

VariableGetterExpression::VariableGetterExpression(const std::wstring& variable)
    : VariableGetterExpression(variable, {}, {}) {}

VariableGetterExpression::VariableGetterExpression(const std::wstring& variable, const std::vector<std::wstring>& path)
    : VariableGetterExpression(variable, path, {}) {}

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

const std::vector<Expression*>& VariableGetterExpression::get_template() const {
    return template_;
}
