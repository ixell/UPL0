#include "IfElseStatement.hpp"

IfElseStatement::IfElseStatement(Expression* condition, BlockStatement* if_, Statement* else_)
    : condition(condition), condition_met(if_), condition_not_met(else_) {}

IfElseStatement::IfElseStatement(Expression* condition, BlockStatement* if_)
    : IfElseStatement(condition, if_, nullptr) {}

IfElseStatement::IfElseStatement(const IfElseStatement& other)
    : IfElseStatement(
        other.condition->copy(),
        new BlockStatement(*other.condition_met),
        other.condition_not_met->copy()
    ) {}

StatementType IfElseStatement::get_type() const {
    return StatementType::IfElseStatement;
}

IfElseStatement::~IfElseStatement() {
    delete condition, condition_met, condition_not_met;
}

Statement* IfElseStatement::copy() const {
    return static_cast<Statement*>(new IfElseStatement(*this));
}

Expression* IfElseStatement::get_condition() const {
    return condition;
}

BlockStatement* IfElseStatement::get_if_code() const {
    return condition_met;
}

Statement* IfElseStatement::get_else_code() const {
    return condition_not_met;
}
