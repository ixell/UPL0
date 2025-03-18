#include "BlockStatement.hpp"

BlockStatement::BlockStatement(const std::vector<Statement*>& statements)
    : statements(statements) {}

BlockStatement::BlockStatement(std::vector<Statement*>&& statements)
    : statements(statements) {}

BlockStatement::BlockStatement(const BlockStatement& other)
        : statements() {
    statements.reserve(other.get_count());
    for (Statement* statement : other.statements) {
        statements.push_back(statement->copy());
    }
}

StatementType BlockStatement::get_type() const {
    return StatementType::BlockStatement;
}

BlockStatement::~BlockStatement() {
    for (Statement* statement : statements)
        delete statement;
}

Statement* BlockStatement::copy() const {
    return static_cast<Statement*>(new BlockStatement(*this));
}

const size_t BlockStatement::get_count() const {
    return statements.size();
}

const std::vector<Statement*> BlockStatement::get_statements() const {
    return statements;
}

const Statement* BlockStatement::get_statement(size_t index) const {
    return statements.at(index);
}