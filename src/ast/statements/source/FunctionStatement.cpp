#include "FunctionStatement.hpp"

FunctionStatement::FunctionStatement(
    TypeStatement* type,
    const std::wstring& name,
    const std::vector<Statement*>& args,
    BlockStatement* code
) :
    type(type), name(name), args(args), code(code) {}

StatementType FunctionStatement::get_type() const {
    return StatementType::FunctionStatement;
}

FunctionStatement::~FunctionStatement() {
    delete type;
    for (Statement* expr : args)
        delete expr;
}

Statement* FunctionStatement::get_return_type() const {
    return type;
}

const std::wstring& FunctionStatement::get_name() const {
    return name;
}

const std::vector<Statement*>& FunctionStatement::get_args() const {
    return args;
}

BlockStatement* FunctionStatement::get_code() const {
    return code;
}
