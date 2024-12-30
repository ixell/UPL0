#include "Expression.hpp"
#include "modificators.hpp"

class VariableExpression : public Expression {
private:
    std::vector<Modificator> modificators;
    std::vector<ptr_t<VariableExpression>> template_;
    std::wstring type, name;
public:
    VariableExpression(
        const std::wstring& type,
        const std::wstring& name,
        const std::vector<Modificator>& modificators,
        const std::vector<ptr_t<VariableExpression>>& template_
    );
    VariableExpression(
        const std::wstring& type,
        const std::wstring& name,
        const std::vector<Modificator>& modificators
    );
    VariableExpression(const std::wstring& type, const std::wstring& name);

	virtual ExpressionType get_type() const override;

    const std::vector<Modificator> get_modificators() const;
    const std::vector<ptr_t<VariableExpression>> get_template() const;
    const std::wstring& get_variable_type() const;
    const std::wstring& get_name() const;
};
