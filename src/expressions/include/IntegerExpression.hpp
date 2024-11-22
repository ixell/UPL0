#pragma once
#include "Expression.hpp"

class IntegerExpression : public Expression {
private:
	int64_t integer;
public:
	IntegerExpression(int64_t integer);
	IntegerExpression();

	virtual std::wstring to_string() const override;
	virtual ~IntegerExpression() = default;
};
