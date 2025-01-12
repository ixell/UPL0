#pragma once
#include "VariableExpression.hpp"

class ConstantVariableExpression : public VariableExpression {
private:
    Expression* value;
public:
    ConstantVariableExpression(TypeExpression* type, const std::wstring& name, Expression* value);

	virtual ExpressionType get_type() const override;
    virtual ~ConstantVariableExpression();

    const Expression* get_value() const;
};
