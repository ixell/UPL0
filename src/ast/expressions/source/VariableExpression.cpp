#include "VariableExpression.hpp"

VariableExpression::VariableExpression(
	const std::wstring& type,
	const std::wstring& name,
	const std::vector<Modificators>& modificators,
	const std::vector<ptr_t<VariableExpression>>& template_
) :
	type(type), name(name), modificators(modificators), template_(template_) {}

VariableExpression::VariableExpression(
	const std::wstring& type,
	const std::wstring& name,
	const std::vector<Modificators>& modificators
) :
	type(type), name(name), modificators(modificators) {}

VariableExpression::VariableExpression(const std::wstring& type, const std::wstring& name)
	: type(type), name(name) {}

ExpressionType VariableExpression::get_type() const {
	return ExpressionType::unknown;
}

const std::vector<Modificator> VariableExpression::get_modificators() const {
	return modificators;
}

const std::vector<ptr_t<VariableExpression>> VariableExpression::get_template() const {
	return template_;
}

const std::wstring& VariableExpression::get_variable_type() const {
	return type;
}

const std::wstring& VariableExpression::get_name() const {
	return name;
}
