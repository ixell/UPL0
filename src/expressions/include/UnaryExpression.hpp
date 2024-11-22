#pragma once
#include "operations.hpp"
#include "Expression.hpp"

class UnaryExpression : public Expression {
private:
	Operation operation;
	unique_ptr<Expression> expr;
public:
	UnaryExpression(Operation operation, Expression*&& value);

	virtual ExpressionType get_type() const override;
	virtual ~UnaryExpression() = default;
};
