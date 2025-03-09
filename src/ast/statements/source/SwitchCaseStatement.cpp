#include "SwitchCaseStatement.hpp"

SwitchCaseStatement::SwitchCaseStatement(
    Expression* item,
    std::vector<std::pair<Expression*, BlockStatement*>> cases,
    BlockStatement* default_case
) :
    item(item), cases(cases), default_case(default_case) {}

SwitchCaseStatement::SwitchCaseStatement(const SwitchCaseStatement& other)
        : item(other.item->copy()), cases(), default_case(new BlockStatement(*default_case)) {
    cases.reserve(other.cases.size());
    for (const std::pair<Expression*, BlockStatement*>& case_ : other.cases) {
        cases.push_back(std::pair(case_.first->copy(), new BlockStatement(*case_.second)));
    }
}

StatementType SwitchCaseStatement::get_type() const {
    return StatementType::SwitchCaseStatement;
}

SwitchCaseStatement::~SwitchCaseStatement() {
    delete item, default_case;
    for (auto& case_ : cases) {
        delete case_.first, case_.second;
    }
}

Statement* SwitchCaseStatement::copy() const {
    return static_cast<Statement*>(new SwitchCaseStatement(*this));
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
