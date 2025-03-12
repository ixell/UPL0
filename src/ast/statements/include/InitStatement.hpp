#pragma once
#include <string>
#include <vector>
#include "VariableStatement.hpp"
#include "Statement.hpp"

class InitStatement : public Statement {
private:
    VariableStatement* variable;
    std::vector<Expression*> args;
public:
    InitStatement(
        VariableStatement* variable,
        const std::vector<Expression*>& args
    );
    InitStatement(const InitStatement& other);

    virtual StatementType get_type() const override;
    virtual ~InitStatement();
	virtual Statement* copy() const override;

    const VariableStatement* get_variable() const;
    const std::vector<Expression*>& get_args() const;
    
    virtual Jump exec(Variables& variables) override;
};
