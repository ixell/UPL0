#include "ConstantVariableStatement.hpp"

ConstantVariableStatement::ConstantVariableStatement(TypeStatement* type, const std::wstring& name, Expression* value)
    : VariableStatement(type, name), value(value) {}

StatementType ConstantVariableStatement::get_type() const {
    return StatementType::Unknown;
}

ConstantVariableStatement::~ConstantVariableStatement() {
    delete value;
}

const Expression* ConstantVariableStatement::get_value() const {
    return value;
}
