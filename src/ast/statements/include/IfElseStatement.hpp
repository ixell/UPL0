#pragma once
#include "Expression.hpp"
#include "Statement.hpp"
#include "BlockStatement.hpp"

class IfElseStatement : public Statement {
private:
    Expression* condition;
    BlockStatement* condition_met;
    Statement* condition_not_met;
public:
    IfElseStatement(Expression* condition, BlockStatement* if_);
    IfElseStatement(Expression* condition, BlockStatement* if_, Statement* else_);
    IfElseStatement(const IfElseStatement& other);

    virtual StatementType get_type() const override;
    virtual ~IfElseStatement();
	virtual Statement* copy() const override;

    Expression* get_condition() const;
    BlockStatement* get_if_code() const;
    Statement* get_else_code() const;
    
    virtual Jump exec(Variables& variables) override;
};

using IfStatement = IfElseStatement;
