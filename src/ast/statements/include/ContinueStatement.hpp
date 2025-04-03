#pragma once
#include "Statement.hpp"

class ContinueStatement : public Statement {
public:
    ContinueStatement();
    ContinueStatement(const ContinueStatement& other);

    virtual StatementType get_type() const override;
    virtual ~ContinueStatement();
	virtual Statement* copy() const override;

    virtual Jump exec(Variables& variables) override;
};
