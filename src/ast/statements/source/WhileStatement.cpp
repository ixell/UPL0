#include "WhileStatement.hpp"

WhileStatement::WhileStatement(Expression* condition, BlockStatement* code)
    : condition(condition), code(code) {}

StatementType WhileStatement::get_type() const {
    return StatementType::Unknown;
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
