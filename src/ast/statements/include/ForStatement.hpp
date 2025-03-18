#pragma once
#include "Expression.hpp"
#include "Statement.hpp"
#include "DoStatement.hpp"
#include "BlockStatement.hpp"

class ForStatement : public Statement {
private:
    Statement* initializer;
    Expression* condition;
    Expression* changer;
    BlockStatement* code;
public:
    ForStatement(
        Statement* initializer,
        Expression* condition,
        Expression* changer,
        BlockStatement* code
    );
    ForStatement(const ForStatement& other);
    
    virtual StatementType get_type() const override;
    virtual ~ForStatement();
	virtual Statement* copy() const override;

    Statement* get_initializer() const;
    Expression* get_condition() const;
    Expression* get_changer() const;
    BlockStatement* get_code() const;
    
    virtual Jump exec(Variables& variables) override;
};
