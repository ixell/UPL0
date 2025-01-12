#pragma once
#include <string>
#include <vector>
#include "VariableExpression.hpp"
#include "Statement.hpp"

class InitStatement : public Statement {
private:
    ptr_t<VariableExpression> variable;
    std::vector<ptr_t<Expression>> args;
public:
    InitStatement(
        ptr_t<VariableExpression> variable,
        const std::vector<ptr_t<Expression>>& args
    );

    virtual StatementType get_type() const override;
    virtual ~InitStatement() = default;

    const ptr_t<VariableExpression> get_variable();
    const std::vector<ptr_t<Expression>>& get_args();
};
