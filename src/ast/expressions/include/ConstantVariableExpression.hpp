#include "VariableExpression.hpp"

class ConstantVariableExpression : public VariableExpression {
private:
    ptr_t<Expression> value;
public:
    ConstntVariableExpression(
        const std::wstring& type,
        const std::wstring& name,
        const std::vector<Modificator>& modificators,
        const std::vector<ptr_t<VariableExpression>>& template_,
        ptr_t<Expression> value;
    );
    ConstntVariableExpression(
        const std::wstring& type,
        const std::wstring& name,
        const std::vector<Modificator>& modificators,
        ptr_t<Expression> value
    );
    ConstntVariableExpression(const std::wstring& type, const std::wstring& name, ptr_t<Expression> value);

	virtual ExpressionType get_type() const override;

    const ptr_t<Expression> get_value() const;
}
