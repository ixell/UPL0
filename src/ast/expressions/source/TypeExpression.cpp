#include "TypeExpressiuon.hpp"
#include "modificators.hpp"

TypeExpression::TypeExpression(
	const std::wstring& type,
	const std::vector<Modificators>& modificators,
	const std::vector<ptr_t<TypeExpression>>& template_
) :
	type(type), modificators(modificators), template_(template_) {}

TypeExpression::TypeExpression(
	const std::wstring& type,
	const std::vector<Modificators>& modificators
) :
	type(type), modificators(modificators) {}

TypeExpression::TypeExpression(const std::wstring& type)
	: type(type) {}

ExpressionType TypeExpression::get_type() const {
	return ExpressionType::unknown;
}

const std::vector<Modificator>& TypeExpression::get_modificators() const {
	return modificators;
}

const std::vector<ptr_t<TypeExpression>>& TypeExpression::get_template() const {
	return template_;
}

const std::wstring& TypeExpression::get_variable_type() const {
	return type;
}