#include "WhileStatement.hpp"

WhileStatement::WhileStatement(Expression* condition, BlockStatement* code)
    : condition(condition), code(code) {}

WhileStatement::WhileStatement(const WhileStatement& other)
    : condition(other.condition->copy()), code(new BlockStatement(*other.code)) {}

StatementType WhileStatement::get_type() const {
    return StatementType::WhileStatement;
}

WhileStatement::~WhileStatement() {
    delete condition, code;
}

Statement* WhileStatement::copy() const {
    return static_cast<Statement*>(new WhileStatement(*this));
}

Expression* WhileStatement::get_condition() const {
    return condition;
}

BlockStatement* WhileStatement::get_code() const {
    return code;
}

DoWhileStatement::DoWhileStatement(Expression* condition, BlockStatement* code)
    : WhileStatement(condition, code) {}

StatementType DoWhileStatement::get_type() const {
    return StatementType::DoWhileStatement;
}
