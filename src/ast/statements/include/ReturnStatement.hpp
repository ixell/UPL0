#pragma once
#include "Statement.hpp"
#include "Expression.hpp"

class ReturnStatement : public Statement {
private:
    Expression* expression;
public:
    ReturnStatement(Expression* expression);
    ReturnStatement(const ReturnStatement& other);

    virtual StatementType get_type() const override;
    virtual ~ReturnStatement();
	virtual Statement* copy() const override;

    Expression* get_expression() const;
    
    virtual Jump exec(Variables& variables) override;
};
