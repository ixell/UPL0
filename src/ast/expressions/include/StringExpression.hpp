#pragma once
#include <string>
#include "Expression.hpp"

class StringExpression : public Expression {
private:
    std::wstring value;
public:
    StringExpression(const std::wstring& value);
    StringExpression(const StringExpression& other);

    virtual ExpressionType get_type() const override;
    virtual ~StringExpression();
	virtual Expression* copy() const override;

    const std::wstring& get_value() const;
    
    virtual Expression* eval(Variables& variables) const override;
};
