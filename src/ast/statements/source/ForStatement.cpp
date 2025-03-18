#include "ForStatement.hpp"

ForStatement::ForStatement(
    Statement* initializer,
    Expression* condition,
    Expression* changer,
    BlockStatement* code
) :
    initializer(initializer),
    condition(condition),
    changer(changer),
    code(code) {}

ForStatement::ForStatement(const ForStatement& other)
    : ForStatement(
        other.initializer->copy(),
        other.condition->copy(),
        other.changer->copy(),
        new BlockStatement(*other.code)
    ) {}

StatementType ForStatement::get_type() const {
    return StatementType::ForStatement;
}

ForStatement::~ForStatement() {
    delete initializer, condition, changer, code;
}

Statement* ForStatement::copy() const {
    return static_cast<Statement*>(new ForStatement(*this));
}

Statement* ForStatement::get_initializer() const {
    return initializer;
}

Expression* ForStatement::get_condition() const {
    return condition;
}

Expression* ForStatement::get_changer() const {
    return changer;
}

BlockStatement* ForStatement::get_code() const {
    return code;
}
