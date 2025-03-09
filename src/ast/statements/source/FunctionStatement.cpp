#include "FunctionStatement.hpp"

FunctionStatement::FunctionStatement(
    TypeStatement* type,
    const std::wstring& name,
    const std::vector<Statement*>& args,
    BlockStatement* code,
    const std::vector<Statement*>& template_
) :
    type(type), name(name), args(args), code(code), template_(template_) {}

FunctionStatement::FunctionStatement(
    TypeStatement* type,
    const std::wstring& name,
    const std::vector<Statement*>& args,
    BlockStatement* code
) : FunctionStatement(type, name, args, code, {}) {}

FunctionStatement::FunctionStatement(const FunctionStatement& other)
	    : type(new TypeStatement(*other.type)), name(other.name),
            args(), code(new BlockStatement(*other.code)), template_() {
    args.reserve(other.args.size());
    template_.reserve(other.template_.size());
    for (Statement* statement : other.args) {
        args.push_back(statement->copy());
    }
    for (Statement* statement : other.template_) {
        template_.push_back(statement->copy());
    }
}

StatementType FunctionStatement::get_type() const {
    return StatementType::FunctionStatement;
}

FunctionStatement::~FunctionStatement() {
    delete type;
    for (Statement* expr : args)
        delete expr;
    delete code;
}

Statement* FunctionStatement::copy() const {
    return static_cast<Statement*>(new FunctionStatement(*this));
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

const std::vector<Statement*>& FunctionStatement::get_template() const {
    return template_;
}
