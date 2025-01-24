#pragma once
#include "Statement.hpp"
#include "Expression.hpp"

class DoStatement : public Statement {
private:
    Expression* expr;
public:
    DoStatement(Expression* expr);

    virtual StatementType get_type() const override;
    virtual ~DoStatement();

    Expression* get_expression() const;
};
