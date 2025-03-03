#include "ArgumentedExpression.hpp"

ArgumentedExpression::ArgumentedExpression(
        Operation operation, Expression* main,
        const std::vector<Expression*>& args)
    : operation(operation), main(main), args(args) {}

ExpressionType ArgumentedExpression::get_type() const {
    return ExpressionType::ArgumentedExpression;
}

ArgumentedExpression::~ArgumentedExpression() {
    delete main;
    for (Expression* expr : args) {
        delete expr;
    }
}

Operation ArgumentedExpression::get_operation() const {
    return operation;
}

Expression* ArgumentedExpression::get_main() const {
    return main;
}

const std::vector<Expression*>& ArgumentedExpression::get_args() const {
    return args;
}
    
Expression* ArgumentedExpression::eval() const {
    //...
}

