#include "InitStatement.hpp"

InitStatement::InitStatement(
    VariableStatement* variable,
    const std::vector<Expression*>& args
) : variable(variable), args(args) {}

StatementType InitStatement::get_type() const {
    return StatementType::InitStatement;
}

InitStatement::~InitStatement() {
    delete variable;
    for (Expression* expr : args)
        delete expr;
}

const VariableStatement* InitStatement::get_variable() {
    return variable;
}

const std::vector<Expression*>& InitStatement::get_args() {
    return args;
}
