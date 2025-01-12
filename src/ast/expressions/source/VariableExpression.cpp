#include "VariableExpression.hpp"

VariableExpression::VariableExpression(TypeExpression* type, const std::wstring& name)
	: type(type), name(name) {}

ExpressionType VariableExpression::get_type() const {
	return ExpressionType::unknown;
}

VariableExpression::~VariableExpression() {
	delete type;
}

const std::vector<Modificator>& VariableExpression::get_modificators() const {
	return type->get_modificators();
}

const std::vector<Expression*>& VariableExpression::get_template() const {
	return type->get_template();
}

const std::wstring& VariableExpression::get_variable_type() const {
	return type->get_type_value();
}

TypeExpression* VariableExpression::get_type_expression() const {
	return type;
}

const std::wstring& VariableExpression::get_name() const {
	return name;
}
