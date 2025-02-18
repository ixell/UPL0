#include "WhileStatement.hpp"

WhileStatement::WhileStatement(Expression* condition, BlockStatement* code)
    : condition(condition), code(code) {}

StatementType WhileStatement::get_type() const {
    return StatementType::WhileStatement;
}

WhileStatement::~WhileStatement() {
    delete condition, code;
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
