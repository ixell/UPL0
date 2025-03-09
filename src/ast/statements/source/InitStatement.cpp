#include "InitStatement.hpp"

InitStatement::InitStatement(
    VariableStatement* variable,
    const std::vector<Expression*>& args
) : variable(variable), args(args) {}

InitStatement::InitStatement(const InitStatement& other)
	    : variable(new VariableStatement(*other.variable)), args() {
    args.reserve(other.args.size());
    for (Expression* expr : other.args) {
        args.push_back(expr->copy());
    }
}

StatementType InitStatement::get_type() const {
    return StatementType::InitStatement;
}

InitStatement::~InitStatement() {
    delete variable;
    for (Expression* expr : args)
        delete expr;
}

Statement* InitStatement::copy() const {
    return static_cast<Statement*>(new InitStatement(*this));
}

const VariableStatement* InitStatement::get_variable() const {
    return variable;
}

const std::vector<Expression*>& InitStatement::get_args() const {
    return args;
}
