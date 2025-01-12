#include "VariableExpression.hpp"

VariableExpression::VariableExpression(ptr_t<TypeExpression> type, const std::wstring& name)
	: type(type), name(name) {}

ExpressionType VariableExpression::get_type() const {
	return ExpressionType::unknown;
}

const std::vector<Modificator>& VariableExpression::get_modificators() const {
	return type->get_modificators();
}

const std::vector<ptr_t<Expression>>& VariableExpression::get_template() const {
	return type->get_template();
}

const std::wstring& VariableExpression::get_variable_type() const {
	return type->get_type_value();
}

ptr_t<TypeExpression> VariableExpression::get_type_expression() const {
	return type;
}

const std::wstring& VariableExpression::get_name() const {
	return name;
}
