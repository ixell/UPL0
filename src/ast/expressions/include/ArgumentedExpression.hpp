#pragma once
#include <vector>
#include "Expression.hpp"
#include "operations.hpp"

class ArgumentedExpression : public Expression {
private:
    Operation operation;
    Expression* main;
    std::vector<Expression*> args;
public:
    ArgumentedExpression(Operation operation, Expression* main, const std::vector<Expression*>& args);
    
    virtual ExpressionType get_type() const override;
    virtual ~ArgumentedExpression();

    Operation get_operation() const;
    Expression* get_main() const;
    const std::vector<Expression*>& get_args() const;
    
    virtual Expression* eval() const override;
};
