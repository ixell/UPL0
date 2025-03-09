#include "VariableStatement.hpp"

VariableStatement::VariableStatement(TypeStatement* type, const std::wstring& name)
	: type(type), name(name) {}

VariableStatement::VariableStatement(const VariableStatement& other)
	: type(other.type), name(name) {}

StatementType VariableStatement::get_type() const {
	return StatementType::VariableStatement;
}

VariableStatement::~VariableStatement() {
	delete type;
}

Statement* VariableStatement::copy() const {
    return static_cast<Statement*>(new VariableStatement(*this));
}

TypeStatement* VariableStatement::get_variable_type() const {
	return type;
}

const std::wstring& VariableStatement::get_name() const {
	return name;
}
