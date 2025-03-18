#include "SpecialStatement.hpp"

SpecialStatement::SpecialStatement(const std::wstring& message)
    : message(message) {}

SpecialStatement::SpecialStatement(const SpecialStatement& other)
    : message(other.message) {}

StatementType SpecialStatement::get_type() const {
    return StatementType::SpecialStatement;
}

SpecialStatement::~SpecialStatement() = default;

Statement* SpecialStatement::copy() const {
    return static_cast<Statement*>(new SpecialStatement(message));
}

const std::wstring& SpecialStatement::get_messgae() {
    return message;
}
