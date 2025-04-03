#include "BreakStatement.hpp"

BreakStatement::BreakStatement() = default;

BreakStatement::BreakStatement(const BreakStatement& other)
    : BreakStatement() {}

StatementType BreakStatement::get_type() const {
    return StatementType::BreakStatement;
}

BreakStatement::~BreakStatement() = default;

Statement* BreakStatement::copy() const {
    return static_cast<Statement*>(new BreakStatement());
}
