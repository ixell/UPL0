#pragma once
#include "Statement.hpp"

class BreakStatement : public Statement {
public:
    BreakStatement();
    BreakStatement(const BreakStatement& other);

    virtual StatementType get_type() const override;
    virtual ~BreakStatement();
	virtual Statement* copy() const override;

    virtual Jump exec(Variables& variables) override;
};
