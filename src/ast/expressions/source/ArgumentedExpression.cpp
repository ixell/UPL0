#include "ArgumentedExpression.hpp"

ArgumentedExpression::ArgumentedExpression(
        Operation operation, Expression* main,
        const std::vector<Expression*>& args)
    : operation(operation), main(main), args(args) {}

ArgumentedExpression::ArgumentedExpression(const ArgumentedExpression& other)
        : operation(other.operation), main(main->copy()), args() {
    args.reserve(other.args.size());
    for (Expression* arg : other.args) {
        args.push_back(arg->copy());
    }
}

ExpressionType ArgumentedExpression::get_type() const {
    return ExpressionType::ArgumentedExpression;
}

ArgumentedExpression::~ArgumentedExpression() {
    delete main;
    for (Expression* expr : args) {
        delete expr;
    }
}

Expression* ArgumentedExpression::copy() const {
    return static_cast<Expression*>(new ArgumentedExpression(*this));
};

Operation ArgumentedExpression::get_operation() const {
    return operation;
}

Expression* ArgumentedExpression::get_main() const {
    return main;
}

const std::vector<Expression*>& ArgumentedExpression::get_args() const {
    return args;
}
