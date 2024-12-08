#include "InitStatement.hpp"

InitStatement::InitStatement(
        const std::vector<std::wstring>& type,
        const std::wstring& variable,
        const std::vector<ptr_t<Expression>>& args)
    : type(type), variable(variable), args(args) {}

StatementType InitStatement::get_type() const {
    return StatementType::InitStatement;
}

const std::vector<std::wstring>& InitStatement::get_type() {
    return type;
}

const std::wstring& get_variable() {
    return variable;
}

const std::vector<ptr_t<Expression>>& get_args() {
    return args;
}
