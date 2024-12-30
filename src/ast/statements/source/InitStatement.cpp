#include "InitStatement.hpp"

InitStatement::InitStatement(
        ptr_t<VariableExpression> variable,
        const std::vector<ptr_t<Expression>>& args)
    : variable(variable), args(args) {}

StatementType InitStatement::get_type() const {
    return StatementType::InitStatement;
}

const ptr_t<VariableExpression> InitStatement::get_variable() {
    return variable;
}

const std::vector<ptr_t<Expression>>& InitStatement::get_args() {
    return args;
}
