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

VariableGetterExpression::VariableGetterExpression(const VariableGetterExpression& other)
        : variable(variable), path(path), template_() {
    template_.reserve(other.template_.size());
    for (Expression* arg : other.template_) {
        template_.push_back(arg->copy());
    }
}

ExpressionType VariableGetterExpression::get_type() const {
    return ExpressionType::VariableGetterExpression;
}

VariableGetterExpression::~VariableGetterExpression() = default;

Expression* VariableGetterExpression::copy() const {
    return static_cast<Expression*>(new VariableGetterExpression(*this));
};

const std::wstring& VariableGetterExpression::get_variable() const {
    return variable;
}

const std::vector<std::wstring>& VariableGetterExpression::get_path() const {
    return path;
}

const std::vector<Expression*>& VariableGetterExpression::get_template() const {
    return template_;
}

Expression* VariableGetterExpression::eval() const {
    //...
}
