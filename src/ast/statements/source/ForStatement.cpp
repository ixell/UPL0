#include "ForStatement.hpp"

ForStatement::ForStatement(
    DoStatement* initializer,
    Expression* condition,
    DoStatement* changer,
    BlockStatement* code
) :
    initializer(initializer),
    condition(condition),
    changer(changer),
    code(code) {}

StatementType ForStatement::get_type() const {
    return StatementType::Unknown;
}

ForStatement::~ForStatement() {
    delete initializer, condition, changer, code;
}

DoStatement* ForStatement::get_initializer() const {
    return initializer;
}

Expression* ForStatement::get_condition() const {
    return condition;
}

DoStatement* ForStatement::get_changer() const {
    return changer;
}

BlockStatement* ForStatement::get_code() const {
    return code;
}
