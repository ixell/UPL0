#pragma once
#include "Expression.hpp"
#include "Statement.hpp"
#include "BlockStatement.hpp"

class IfElseStatement : public Statement {
private:
    Expression* condition;
    BlockStatement* condition_met;
    BlockStatement* condition_not_met;
public:
    IfElseStatement(Expression* condition, BlockStatement* if_);
    IfElseStatement(Expression* condition, BlockStatement* if_, BlockStatement* else_);

    virtual StatementType get_type() const override;
    virtual ~IfElseStatement();

    Expression* get_condition() const;
    BlockStatement* get_if_code() const;
    BlockStatement* get_else_code() const;
};

using IfStatement = IfElseStatement;
