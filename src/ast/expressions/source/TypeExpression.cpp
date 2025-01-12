#include "TypeExpression.hpp"
#include "modificators.hpp"

TypeExpression::TypeExpression(
	const std::wstring& type,
	const std::vector<Modificator>& modificators,
	const std::vector<Expression*>& template_
) :
	type(type), modificators(modificators), template_(template_) {}

TypeExpression::TypeExpression(
	const std::wstring& type,
	const std::vector<Modificator>& modificators
) :
	type(type), modificators(modificators) {}

TypeExpression::TypeExpression(const std::wstring& type)
	: type(type) {}

ExpressionType TypeExpression::get_type() const {
	return ExpressionType::unknown;
}

TypeExpression::~TypeExpression() {
	for (Expression* expr : template_)
		delete expr;
}

const std::vector<Modificator>& TypeExpression::get_modificators() const {
	return modificators;
}

const std::vector<Expression*>& TypeExpression::get_template() const {
	return template_;
}

const std::wstring& TypeExpression::get_type_value() const {
	return type;
}