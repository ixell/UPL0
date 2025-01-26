#pragma once
#include <vector>
#include "Expression.hpp"
#include "Statement.hpp"
#include "BlockStatement.hpp"

class SwitchCaseStatement : public Statement {
private:
    Expression* item;
    std::vector<std::pair<Expression*, BlockStatement*>> cases;
    BlockStatement* default_case;
public:
    SwitchCaseStatement(
        Expression* item,
        std::vector<std::pair<Expression*, BlockStatement*>> cases,
        BlockStatement* default_case = nullptr
    );
    
    virtual StatementType get_type() const override;
    virtual ~SwitchCaseStatement();

    Expression* get_item() const;
    std::pair<Expression*, BlockStatement*> get_case(size_t index) const;
    std::vector<std::pair<Expression*, BlockStatement*>>::const_iterator get_cases() const;
    BlockStatement* get_default_case();
};
