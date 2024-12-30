#include "BlockStatement.hpp"

BlockStatement::BlockStatement(const std::vector<ptr_t<Statement>>& statements)
    : statements(statements) {}
    
StatementType BlockStatement::get_type() const {
    return StatementType::Unknown;
}

const std::vector<ptr_t<Statement>> BlockStatement::get_statements() const {
    return statements;
}

const ptr_t<Statement> BlockStatement::get_statement(size_t index) const {
    return statements.at(index);
}