#include "DoStatement.hpp"

DoStatement::DoStatement(Expression* expr)
    : expr(expr) {}

DoStatement::DoStatement(const DoStatement& other)
    : DoStatement(other.expr->copy()) {}

StatementType DoStatement::get_type() const {
    return StatementType::DoStatement;
}

DoStatement::~DoStatement() {
    delete expr;
}

Statement* DoStatement::copy() const {
    return static_cast<Statement*>(new DoStatement(*this));
}

Expression* DoStatement::get_expression() const {
    return expr;
}
