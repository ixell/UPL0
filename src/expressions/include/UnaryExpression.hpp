#pragma once
#include "operations.hpp"
#include "Expression.hpp"

class UnaryExpression : public Expression {
private:
	Operation operation;
	unique_ptr<Expression> expr;
public:
	UnaryExpression(Operation operation, Expression*&& value);

	virtual std::wstring to_string() const override;
	virtual ~UnaryExpression() = default;
};
