#pragma once
#include <vector>
#include "TypeExpression.hpp"

class VariableExpression : public Expression {
private:
    ptr_t<TypeExpression> type;
    std::wstring name;
public:
    VariableExpression(ptr_t<TypeExpression> type, const std::wstring& name);

	virtual ExpressionType get_type() const override;

    const std::vector<Modificator>& get_modificators() const;
    const std::vector<ptr_t<Expression>>& get_template() const;
    const std::wstring& get_variable_type() const;
    ptr_t<TypeExpression> get_type_expression() const;
    const std::wstring& get_name() const;
};
