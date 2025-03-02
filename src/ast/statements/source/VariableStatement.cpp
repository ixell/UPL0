#include "VariableStatement.hpp"

VariableStatement::VariableStatement(TypeStatement* type, const std::wstring& name)
	: type(type), name(name) {}

StatementType VariableStatement::get_type() const {
	return StatementType::VariableStatement;
}

VariableStatement::~VariableStatement() {
	delete type;
}

TypeStatement* VariableStatement::get_variable_type() const {
	return type;
}

const std::wstring& VariableStatement::get_name() const {
	return name;
}
