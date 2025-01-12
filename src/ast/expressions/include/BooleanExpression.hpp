#pragma once
#include "Expression.hpp"

class BooleanExpression : public Expression {
private:
    bool value;
public:
    BooleanExpression(bool value);

    virtual ExpressionType get_type() const override;
    virtual ~BooleanExpression();

    bool get_value() const;
    void change_value(bool value);
};
