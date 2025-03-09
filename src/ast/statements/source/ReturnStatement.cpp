#include "ReturnStatement.hpp"

ReturnStatement::ReturnStatement(Expression* expression)
    : expression(expression) {}

ReturnStatement::ReturnStatement(const ReturnStatement& other)
    : ReturnStatement(other.expression->copy()) {}

StatementType ReturnStatement::get_type() const {
    return StatementType::ReturnStatement;
}

ReturnStatement::~ReturnStatement() {
    delete expression;
}

Statement* ReturnStatement::copy() const {
    return static_cast<Statement*>(new ReturnStatement(*this));
}

Expression* ReturnStatement::get_expression() const {
    return expression;
}

