#pragma once
#include <vector>
#include <string>
#include "Statement.hpp"
#include "TypeStatement.hpp"
#include "BlockStatement.hpp"

class FunctionStatement : public Statement {
private:
    TypeStatement* type;
    std::wstring name;
    std::vector<Statement*> template_;
    std::vector<Statement*> args;
    BlockStatement* code;
public:
    FunctionStatement(
        TypeStatement* type,
        const std::wstring& name,
        const std::vector<Statement*>& args,
        BlockStatement* code,
        const std::vector<Statement*>& template_
    );
    FunctionStatement(
        TypeStatement* type,
        const std::wstring& name,
        const std::vector<Statement*>& args,
        BlockStatement* code
    );
    FunctionStatement(const FunctionStatement& other);
    
    virtual StatementType get_type() const override;
    virtual ~FunctionStatement();
	virtual Statement* copy() const override;

    TypeStatement* get_return_type() const;
    const std::wstring& get_name() const;
    const std::vector<Statement*>& get_template() const;
    const std::vector<Statement*>& get_args() const;
    BlockStatement* get_code() const;
    
    virtual Jump exec(Variables& variables) override;
    Expression* call(Variables& variables, const std::vector<Expression*>& args);
};
