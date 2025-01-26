#pragma once
#include <vector>
#include "Statement.hpp"
#include "TypeStatement.hpp"
#include "BlockStatement.hpp"

class FunctionStatement : public Statement {
private:
    TypeStatement* type;
    std::wstring name;
    std::vector<Statement*> args;
    BlockStatement* code;
public:
    FunctionStatement(
        TypeStatement* type,
        const std::wstring& name,
        const std::vector<Statement*>& args,
        BlockStatement* code
    );
    
    virtual StatementType get_type() const override;
    virtual ~FunctionStatement();

    Statement* get_return_type() const;
    const std::wstring& get_name() const;
    const std::vector<Statement*>& get_args() const;
    BlockStatement* get_code() const;
};
