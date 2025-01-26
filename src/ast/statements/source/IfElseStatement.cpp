#include "IfElseStatement.hpp"

IfElseStatement::IfElseStatement(Expression* condition, BlockStatement* if_, BlockStatement* else_)
    : condition(condition), condition_met(if_), condition_not_met(else_) {}

IfElseStatement::IfElseStatement(Expression* condition, BlockStatement* if_)
    : IfElseStatement(condition, if_, nullptr) {}

StatementType IfElseStatement::get_type() const {
    return StatementType::Unknown;
}

IfElseStatement::~IfElseStatement() {
    delete condition, condition_met, condition_not_met;
}

Expression* IfElseStatement::get_condition() const {
    return condition;
}

BlockStatement* IfElseStatement::get_if_code() const {
    return condition_met;
}

BlockStatement* IfElseStatement::get_else_code() const {
    return condition_not_met;
}
