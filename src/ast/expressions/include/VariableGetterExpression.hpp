#pragma once
#include <vector>
#include <string>
#include "Expression.hpp"

class VariableGetterExpression : public Expression {
private:
    std::vector<std::wstring> path;
    std::wstring variable;
    std::vector<Expression*> template_;
public:
    VariableGetterExpression(const std::wstring& variable);
    VariableGetterExpression(const std::wstring& variable, const std::vector<std::wstring>& path);
    VariableGetterExpression(
        const std::wstring& variable,
        const std::vector<std::wstring>& path,
        const std::vector<Expression*>& template_
    );
    
    virtual ExpressionType get_type() const override;
    virtual ~VariableGetterExpression();

    const std::wstring& get_variable() const;
    const std::vector<std::wstring>& get_path() const;
    const std::vector<Expression*>& get_template() const;
    
    virtual Expression* eval() const override;
};
