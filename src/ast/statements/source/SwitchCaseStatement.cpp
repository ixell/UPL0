#include "SwitchCaseStatement.hpp"

SwitchCaseStatement::SwitchCaseStatement(
    Expression* item,
    std::vector<std::pair<Expression*, BlockStatement*>> cases,
    BlockStatement* default_case
) :
    item(item), cases(cases), default_case(default_case) {}

StatementType SwitchCaseStatement::get_type() const {
    return StatementType::SwitchCaseStatement;
}

SwitchCaseStatement::~SwitchCaseStatement() {
    delete item, default_case;
    for (auto& case_ : cases) {
        delete case_.first, case_.second;
    }
}

Expression* SwitchCaseStatement::get_item() const {
    return item;
}

std::pair<Expression*, BlockStatement*> SwitchCaseStatement::get_case(size_t index) const {
    return cases.at(index);
}

const std::vector<std::pair<Expression*, BlockStatement*>>& SwitchCaseStatement::get_cases() const {
    return cases;
}

BlockStatement* SwitchCaseStatement::get_default_case() {
    return default_case;
}
