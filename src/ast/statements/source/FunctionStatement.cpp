#include "FunctionStatement.hpp"

FunctionStatement::FunctionStatement(
    TypeExpression* type,
    const std::wstring& name,
    const std::vector<Expression*>& args,
    BlockStatement* code
) :
    type(type), name(name), args(args), code(code) {}

StatementType FunctionStatement::get_type() const {
    return StatementType::Unknown;
}

FunctionStatement::~FunctionStatement() {
    delete type;
    for (Expression* expr : args)
        delete expr;
}

Expression* FunctionStatement::get_return_type() const {
    return type;
}

const std::wstring& FunctionStatement::get_name() const {
    return name;
}

const std::vector<Expression*>& FunctionStatement::get_args() const {
    return args;
}

BlockStatement* FunctionStatement::get_code() const {
    return code;
}
