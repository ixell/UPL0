#pragma once
#include <vector>
#include "Statement.hpp"

class BlockStatement : public ExternalStatement {
private:
    std::vector<ptr_t<Statement>> statements;
public:
    BlockStatement(const std::vector<ptr_t<Statement>>& statements);
    
	virtual StatementType get_type() const override;
	virtual ~BlockStatement() override = default;

    const std::vector<ptr_t<Statement>> get_statements() const;
    const ptr_t<Statement> get_statement(size_t index) const;
};
