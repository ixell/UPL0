#include "ConstantVariableStatement.hpp"

ConstantVariableStatement::ConstantVariableStatement(TypeStatement* type, const std::wstring& name, Expression* value)
    : VariableStatement(type, name), value(value) {}

ConstantVariableStatement::ConstantVariableStatement(const ConstantVariableStatement& other)
    : value(other.value), VariableStatement(*static_cast<const ConstantVariableStatement*>(&other)) {}

StatementType ConstantVariableStatement::get_type() const {
    return StatementType::ConstantVariableStatement;
}

ConstantVariableStatement::~ConstantVariableStatement() {
    delete value;
}

Statement* ConstantVariableStatement::copy() const {
    return static_cast<Statement*>(new ConstantVariableStatement(*this));
}

const Expression* ConstantVariableStatement::get_value() const {
    return value;
}
