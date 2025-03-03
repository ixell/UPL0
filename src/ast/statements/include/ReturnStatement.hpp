#pragma once
#include "Statement.hpp"
#include "Expression.hpp"

class ReturnStatement : public Statement {
private:
    Expression* expression;
public:
    ReturnStatement(Expression* expression);

    virtual StatementType get_type() const override;
    virtual ~ReturnStatement();

    Expression* get_expression() const;
    
    virtual void exec() override;
};
