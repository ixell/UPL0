#pragma once
#include "Expression.hpp"

class IntegerExpression : public Expression {
private:
	int64_t value;
public:
	IntegerExpression(int64_t value);
	IntegerExpression();
    IntegerExpression(const IntegerExpression& other);

	virtual ExpressionType get_type() const override;
	virtual ~IntegerExpression();
	virtual Expression* copy() const override;

	int64_t get_value() const;
	void change_value(int64_t value);

	virtual Expression* eval() const override;
};
