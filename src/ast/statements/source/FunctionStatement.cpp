#include "FunctionStatement.hpp"

FunctionStatement(
    ptr_t<TypeExpression> type,
    const std::wstring& name,
    const std::vector<ptr_t<Expression>>& args,
    ptr_t<BlockStatement> code;
) :
    type(type), name(name), args(args), code(code) {}

virtual get_type() const override {
    return StatementType::unknown;
}

virtual ~FunctionStatement() = default;

ptr_t<Expression> get_return_type() const {
    return type;
}

const std::wstring& get_name() const {
    return name;
}

const std::vector<ptr_t<Expression>>& get_args() const {
    return args;
}

ptr_t<BlockStatement> get_code() const {
    return code;
}
