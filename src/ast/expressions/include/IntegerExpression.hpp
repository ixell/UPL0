#pragma once
#include "Expression.hpp"

class IntegerExpression : public Expression {
private:
	int64_t value;
public:
	IntegerExpression(int64_t value);
	IntegerExpression();

	virtual ExpressionType get_type() const override;
	virtual ~IntegerExpression();

	int64_t get_value() const;
	void change_value(int64_t value);

	virtual Expression* eval() const override;
};
