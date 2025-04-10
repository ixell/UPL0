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
    VariableGetterExpression(const VariableGetterExpression& other);
    
    virtual ExpressionType get_type() const override;
    virtual ~VariableGetterExpression();
	virtual Expression* copy() const override;

    const std::wstring& get_name() const;
    const std::vector<std::wstring>& get_path() const;
    const std::vector<Expression*>& get_template() const;
    
    Space::Variable& get_variable(Variables& variables) const;
    virtual Expression* eval(Variables& variables) const override;
};
