#pragma once
#include "Expression.hpp"

class FloatExpression : public Expression {
private:
    float value;
public:
    FloatExpression(float value);
    FloatExpression(const FloatExpression& other);

    virtual ExpressionType get_type() const override;
    virtual ~FloatExpression();
	virtual Expression* copy() const override;

    float get_value() const;

    virtual Expression* eval() const override;
};
