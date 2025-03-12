#pragma once
#include "Expression.hpp"

class BooleanExpression : public Expression {
private:
    bool value;
public:
    BooleanExpression(bool value);
    BooleanExpression(const BooleanExpression& other);

    virtual ExpressionType get_type() const override;
    virtual ~BooleanExpression();
	virtual Expression* copy() const override;

    bool get_value() const;
    void change_value(bool value);

    virtual Expression* eval(Variables& variables) const override;
};
