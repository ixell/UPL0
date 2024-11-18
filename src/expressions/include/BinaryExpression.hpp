#pragma once
#include "Expression.hpp"
#include "operations.hpp"

class BinaryExpression : public Expression {
private:
	Operation operation;
	unique_ptr<Expression> expr1, expr2;
public:
	BinaryExpression(Operation operation, Expression*&& expr1, Expression*&& expr2);

	virtual std::wstring to_string() const override;
	virtual ~BinaryExpression() override = default;
};