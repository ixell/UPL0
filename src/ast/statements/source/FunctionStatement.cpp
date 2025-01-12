#include "FunctionStatement.hpp"

FunctionStatement::FunctionStatement(
    ptr_t<TypeExpression> type,
    const std::wstring& name,
    const std::vector<ptr_t<Expression>>& args,
    ptr_t<BlockStatement> code
) :
    type(type), name(name), args(args), code(code) {}

StatementType FunctionStatement::get_type() const {
    return StatementType::Unknown;
}

FunctionStatement::~FunctionStatement() = default;

ptr_t<Expression> FunctionStatement::get_return_type() const {
    return type;
}

const std::wstring& FunctionStatement::get_name() const {
    return name;
}

const std::vector<ptr_t<Expression>>& FunctionStatement::get_args() const {
    return args;
}

ptr_t<BlockStatement> FunctionStatement::get_code() const {
    return code;
}
