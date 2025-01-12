#pragma once
#include <vector>
#include "Statement.hpp"
#include "TypeExpression.hpp"
#include "BlockStatement.hpp"

class FunctionStatement : public Statement {
private:
    TypeExpression* type;
    std::wstring name;
    std::vector<Expression*> args;
    BlockStatement* code;
public:
    FunctionStatement(
        TypeExpression* type,
        const std::wstring& name,
        const std::vector<Expression*>& args,
        BlockStatement* code
    );
    
    virtual StatementType get_type() const override;
    virtual ~FunctionStatement();

    Expression* get_return_type() const;
    const std::wstring& get_name() const;
    const std::vector<Expression*>& get_args() const;
    BlockStatement* get_code() const;
};
