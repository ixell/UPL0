#pragma once
#include "VariableExpression.hpp"

class ConstantVariableExpression : public VariableExpression {
private:
    ptr_t<Expression> value;
public:
    ConstantVariableExpression(ptr_t<TypeExpression> type, const std::wstring& name, ptr_t<Expression> value);

	virtual ExpressionType get_type() const override;

    const ptr_t<Expression> get_value() const;
};
