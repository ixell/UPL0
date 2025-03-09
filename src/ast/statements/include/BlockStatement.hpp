#pragma once
#include <vector>
#include "Statement.hpp"

class BlockStatement : public Statement {
private:
    std::vector<Statement*> statements;
public:
    BlockStatement(const std::vector<Statement*>& statements);
    BlockStatement(const BlockStatement& other);
    
	virtual StatementType get_type() const override;
	virtual ~BlockStatement() override;
	virtual Statement* copy() const override;

    const size_t get_count() const;
    const std::vector<Statement*> get_statements() const;
    const Statement* get_statement(size_t index) const;

    virtual void exec() override;
};
