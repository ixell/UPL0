#pragma once
#include <vector>
#include <string>
#include "Statement.hpp"
#include "TypeStatement.hpp"
#include "BlockStatement.hpp"

class SystemFunctionStatement : public Statement {
private:
    TypeStatement* type;
    std::wstring name;
    std::vector<Statement*> args;
    Expression*(*code)(std::vector<Expression*>&);
public:
    SystemFunctionStatement(
        TypeStatement* type,
        const std::wstring& name,
        const std::vector<Statement*>& args,
        Expression*(*code)(std::vector<Expression*>&)
    );
    SystemFunctionStatement(const SystemFunctionStatement& other);
    
    virtual StatementType get_type() const override;
    virtual ~SystemFunctionStatement();
	virtual Statement* copy() const override;

    const Statement* get_return_type() const;
    const std::wstring& get_name() const;
    const std::vector<Statement*>& get_args() const;
    
    virtual Jump exec(Variables& variables) override;
    Expression* call(Variables& variables, const std::vector<Expression*>& args);
};