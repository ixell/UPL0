#pragma once
#include "Expression.hpp"

class IntegerExpression : public Expression {
private:
	int64_t integer;
public:
	IntegerExpression(int64_t integer);
	IntegerExpression();

	virtual ExpressionType get_type() const override;
	virtual ~IntegerExpression() = default;
};
