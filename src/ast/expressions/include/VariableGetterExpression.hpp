#pragma once
#include <vector>
#include <string>
#include "Expression.hpp"

class VariableGetterExpression : public Expression {
private:
    std::vector<std::wstring> path;
    std::wstring variable;
public:
    VariableGetterExpression(std::wstring variable);
    VariableGetterExpression(std::wstring variable, std::vector<std::wstring> path);
    
    virtual ExpressionType get_type() const override;
    virtual ~VariableGetterExpression();

    const std::wstring& get_variable() const;
    const std::vector<std::wstring>& get_path() const;
};
