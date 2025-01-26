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

    virtual StatementType get_type() const override;
    virtual ~InitStatement();

    const VariableStatement* get_variable();
    const std::vector<Expression*>& get_args();
};
