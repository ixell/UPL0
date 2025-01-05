#include "Expression.hpp"
#include "modificators.hpp"

class TypeExpression : public Expression {
private:
    std::vector<Modificator> modificators;
    std::vector<ptr_t<TypeExpression>> template_;
    std::wstring type;
public:
    TypeExpression(
        const std::wstring& type,
        const std::vector<Modificator>& modificators,
        const std::vector<ptr_t<TypeExpression>>& template_
    );
    TypeExpression(
        const std::wstring& type,
        const std::vector<Modificator>& modificators
    );
    TypeExpression(const std::wstring& type);

	virtual ExpressionType get_type() const override;

    const std::vector<Modificator>& get_modificators() const;
    const std::vector<ptr_t<TypeExpression>>& get_template() const;
    const std::wstring& get_variable_type() const;
};