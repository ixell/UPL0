#include "VariableStatement.hpp"

VariableStatement::VariableStatement(TypeStatement* type, const std::wstring& name)
	: type(type), name(name) {}

StatementType VariableStatement::get_type() const {
	return StatementType::Unknown;
}

VariableStatement::~VariableStatement() {
	delete type;
}

const std::vector<Modificator>& VariableStatement::get_modificators() const {
	return type->get_modificators();
}

const std::vector<Statement*>& VariableStatement::get_template() const {
	return type->get_template();
}

const std::wstring& VariableStatement::get_variable_type() const {
	return type->get_type_value();
}

TypeStatement* VariableStatement::get_type_expression() const {
	return type;
}

const std::wstring& VariableStatement::get_name() const {
	return name;
}
