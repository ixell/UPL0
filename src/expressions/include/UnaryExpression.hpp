#pragma once
#include "operations.hpp"
#include "Expression.hpp"

class UnaryExpression : public Expression {
private:
	Operation operation;
	ptr_t<Expression> expr;
public:
	UnaryExpression(Operation operation, ptr_t<Expression> value);

	virtual ExpressionType get_type() const override;
	virtual ~UnaryExpression() = default;

	const ptr_t<Expression> get_value() const;
};
