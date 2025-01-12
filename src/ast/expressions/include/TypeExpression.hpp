#pragma once
#include <vector>
#include "Expression.hpp"
#include "modificators.hpp"

class TypeExpression : public Expression {
private:
    std::vector<Modificator> modificators;
    std::vector<Expression*> template_;
    std::wstring type;
public:
    TypeExpression(
        const std::wstring& type,
        const std::vector<Modificator>& modificators,
        const std::vector<Expression*>& template_
    );
    TypeExpression(
        const std::wstring& type,
        const std::vector<Modificator>& modificators
    );
    TypeExpression(const std::wstring& type);

	virtual ExpressionType get_type() const override;
    virtual ~TypeExpression();

    const std::vector<Modificator>& get_modificators() const;
    const std::vector<Expression*>& get_template() const;
    const std::wstring& get_type_value() const;
};