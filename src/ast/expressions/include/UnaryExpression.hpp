#pragma once
#include "operations.hpp"
#include "Expression.hpp"

class UnaryExpression : public Expression {
private:
	Operation operation;
	Expression* expr;
public:
	UnaryExpression(Operation operation, Expression* value);
    UnaryExpression(const UnaryExpression& other);

	virtual ExpressionType get_type() const override;
	virtual ~UnaryExpression();
	virtual Expression* copy() const override;

	const Expression* get_value() const;
	Operation get_operation() const;
    
    virtual Expression* eval() const override;
};
