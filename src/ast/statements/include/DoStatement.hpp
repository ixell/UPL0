#pragma once
#include "Statement.hpp"
#include "Expression.hpp"

class DoStatement : public Statement {
private:
    Expression* expr;
public:
    DoStatement(Expression* expr);
    DoStatement(const DoStatement& other);

    virtual StatementType get_type() const override;
    virtual ~DoStatement();
	virtual Statement* copy() const override;

    Expression* get_expression() const;
    
    virtual void exec() override;
};
