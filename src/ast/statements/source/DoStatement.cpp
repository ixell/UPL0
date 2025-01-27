#include "DoStatement.hpp"

DoStatement::DoStatement(Expression* expr)
    : expr(expr) {}

StatementType DoStatement::get_type() const {
    return StatementType::Unknown;
}

DoStatement::~DoStatement() = default;

Expression* DoStatement::get_expression() const {
    return expr;
}
