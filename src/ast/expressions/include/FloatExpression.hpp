#pragma once
#include "Expression.hpp"

class FloatExpression : public Expression {
private:
    float value;
public:
    FloatExpression(float value);

    virtual ExpressionType get_type() const override;
    virtual ~FloatExpression();

    float get_value() const;
};
