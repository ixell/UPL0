#include "ContinueStatement.hpp"

ContinueStatement::ContinueStatement() = default;

ContinueStatement::ContinueStatement(const ContinueStatement& other)
    : ContinueStatement() {}

StatementType ContinueStatement::get_type() const {
    return StatementType::ContinueStatement;
}

ContinueStatement::~ContinueStatement() = default;

Statement* ContinueStatement::copy() const {
    return static_cast<Statement*>(new ContinueStatement());
}
