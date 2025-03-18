#include "SystemFunctionStatement.hpp"

SystemFunctionStatement::SystemFunctionStatement(
    TypeStatement* type,
    const std::wstring& name,
    const std::vector<Statement*>& args,
    Expression*(*code)(std::vector<Expression*>)
) : type(type), name(name), args(args), code(code) {}

SystemFunctionStatement::SystemFunctionStatement(const SystemFunctionStatement& other)
    :
        type(other.type != nullptr ? new TypeStatement(*other.type) : nullptr),
        name(other.name),
        args(),
        code(other.code) {
    args.reserve(other.args.size());
    for (const Statement* arg : other.args) {
        args.push_back(arg->copy());
    }
}


StatementType SystemFunctionStatement::get_type() const {
    return StatementType::SystemFunctionStatement;
}

SystemFunctionStatement::~SystemFunctionStatement() {
    delete type;
    for (Statement* arg : args) {
        delete arg;
    }
}

Statement* SystemFunctionStatement::copy() const {
    return static_cast<Statement*>(new SystemFunctionStatement(*this));
}

const Statement* SystemFunctionStatement::get_return_type() const {
    return type;
}

const std::wstring& SystemFunctionStatement::get_name() const {
    return name;
}

const std::vector<Statement*>& SystemFunctionStatement::get_args() const {
    return args;
}
