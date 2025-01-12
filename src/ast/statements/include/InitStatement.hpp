#pragma once
#include <string>
#include <vector>
#include "VariableExpression.hpp"
#include "Statement.hpp"

class InitStatement : public Statement {
private:
    VariableExpression* variable;
    std::vector<Expression*> args;
public:
    InitStatement(
        VariableExpression* variable,
        const std::vector<Expression*>& args
    );

    virtual StatementType get_type() const override;
    virtual ~InitStatement();

    const VariableExpression* get_variable();
    const std::vector<Expression*>& get_args();
};
