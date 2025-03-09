#pragma once
#include "Expression.hpp"
#include "Statement.hpp"
#include "BlockStatement.hpp"

class WhileStatement : public Statement {
private:
    Expression* condition;
    BlockStatement* code;
public:
    WhileStatement(Expression* condition, BlockStatement* code);
    WhileStatement(const WhileStatement& other);

    virtual StatementType get_type() const override;
    virtual ~WhileStatement();
	virtual Statement* copy() const override;

    Expression* get_condition() const;
    BlockStatement* get_code() const;
    
    virtual void exec() override;
};

class DoWhileStatement : public WhileStatement {
public:
    DoWhileStatement(Expression* condition, BlockStatement* code);

    virtual StatementType get_type() const override;
    virtual ~DoWhileStatement() = default;
    
    virtual void exec() override;
};
