#pragma once
#include <string>
#include "Expression.hpp"

class StringExpression : public Expression {
private:
    std::wstring value;
public:
    StringExpression(std::wstring value);

    virtual ExpressionType get_type() const override;
    virtual ~StringExpression();

    const std::wstring& get_value() const;
};
