#pragma once
#include <vector>
#include "TypeExpression.hpp"

class VariableExpression : public Expression {
private:
    TypeExpression* type;
    std::wstring name;
public:
    VariableExpression(TypeExpression* type, const std::wstring& name);

	virtual ExpressionType get_type() const override;
    virtual ~VariableExpression();

    const std::vector<Modificator>& get_modificators() const;
    const std::vector<Expression*>& get_template() const;
    const std::wstring& get_variable_type() const;
    TypeExpression* get_type_expression() const;
    const std::wstring& get_name() const;
};
