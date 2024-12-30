#pragma once
#include "Expression.hpp"
#include "operations.hpp"

class BinaryExpression : public Expression {
private:
	Operation operation;
	ptr_t<Expression> left, right;
public:
	BinaryExpression(Operation operation, ptr_t<Expression> left, ptr_t<Expression> right);

	virtual ExpressionType get_type() const override;
	virtual ~BinaryExpression() override = default;

	Operation get_operation() const;
	const ptr_t<Expression> get_left() const;
	const ptr_t<Expression> get_right() const;
};
