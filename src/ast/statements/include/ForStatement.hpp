#pragma once
#include "Expression.hpp"
#include "Statement.hpp"
#include "DoStatement.hpp"
#include "BlockStatement.hpp"

class ForStatement : public Statement {
private:
    DoStatement* initializer;
    Expression* condition;
    DoStatement* changer;
    BlockStatement* code;
public:
    ForStatement(
        DoStatement* initializer,
        Expression* condition,
        DoStatement* changer,
        BlockStatement* code
    );
    
    virtual StatementType get_type() const override;
    virtual ~ForStatement();

    DoStatement* get_initializer() const;
    Expression* get_condition() const;
    DoStatement* get_changer() const;
    BlockStatement* get_code() const;
};
