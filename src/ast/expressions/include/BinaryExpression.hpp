#pragma once
#include "Expression.hpp"
#include "operations.hpp"

class BinaryExpression : public Expression {
private:
	Operation operation;
	Expression* left, *right;
public:
	BinaryExpression(Operation operation, Expression* left, Expression* right);
    BinaryExpression(const BinaryExpression& other);

	virtual ExpressionType get_type() const override;
	virtual ~BinaryExpression() override;
	virtual Expression* copy() const override;

	Operation get_operation() const;
	const Expression* get_left() const;
	const Expression* get_right() const;
    
    virtual Expression* eval(Variables& variables) const override;
};
