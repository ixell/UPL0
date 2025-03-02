#include "ReturnStatement.hpp"

ReturnStatement::ReturnStatement(Expression* expression)
    : expression(expression) {}

StatementType ReturnStatement::get_type() const {
    return StatementType::ReturnStatement;
}

ReturnStatement::~ReturnStatement() {
    delete expression;
}

Expression* ReturnStatement::get_expression() const {
    return expression;
}

