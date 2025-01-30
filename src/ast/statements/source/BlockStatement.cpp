#include "BlockStatement.hpp"

BlockStatement::BlockStatement(const std::vector<Statement*>& statements)
    : statements(statements) {}
    
StatementType BlockStatement::get_type() const {
    return StatementType::BlockStatement;
}

BlockStatement::~BlockStatement() {
    for (Statement* statement : statements)
        delete statement;
}

const std::vector<Statement*> BlockStatement::get_statements() const {
    return statements;
}

const Statement* BlockStatement::get_statement(size_t index) const {
    return statements.at(index);
}