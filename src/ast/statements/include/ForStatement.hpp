#pragma once
#include "Expression.hpp"
#include "Statement.hpp"
#include "DoStatement.hpp"
#include "BlockStatement.hpp"

class ForStatement : public Statement {
private:
    Expression* initializer;
    Expression* condition;
    Expression* changer;
    BlockStatement* code;
public:
    ForStatement(
        Expression* initializer,
        Expression* condition,
        Expression* changer,
        BlockStatement* code
    );
    
    virtual StatementType get_type() const override;
    virtual ~ForStatement();

    Expression* get_initializer() const;
    Expression* get_condition() const;
    Expression* get_changer() const;
    BlockStatement* get_code() const;
};
