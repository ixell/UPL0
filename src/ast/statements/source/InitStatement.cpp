#include "InitStatement.hpp"

InitStatement::InitStatement(
        VariableExpression* variable,
        const std::vector<Expression*>& args)
    : variable(variable), args(args) {}

StatementType InitStatement::get_type() const {
    return StatementType::InitStatement;
}

InitStatement::~InitStatement() {
    delete variable;
    for (Expression* expr : args)
        delete expr;
}

const VariableExpression* InitStatement::get_variable() {
    return variable;
}

const std::vector<Expression*>& InitStatement::get_args() {
    return args;
}
