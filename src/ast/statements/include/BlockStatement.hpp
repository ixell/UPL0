#pragma once
#include <vector>
#include "Statement.hpp"

class BlockStatement : public Statement {
private:
    std::vector<Statement*> statements;
public:
    BlockStatement(const std::vector<Statement*>& statements);
    
	virtual StatementType get_type() const override;
	virtual ~BlockStatement() override;

    const size_t get_count() const;
    const std::vector<Statement*> get_statements() const;
    const Statement* get_statement(size_t index) const;
};
