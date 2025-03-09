#pragma once
#include <vector>
#include <string>
#include "Statement.hpp"
#include "TypeStatement.hpp"

class VariableStatement : public Statement {
private:
    TypeStatement* type;
    std::wstring name;
public:
    VariableStatement(TypeStatement* type, const std::wstring& name);
    VariableStatement(const VariableStatement& other);

	virtual StatementType get_type() const override;
    virtual ~VariableStatement();
	virtual Statement* copy() const override;

    TypeStatement* get_variable_type() const;
    const std::wstring& get_name() const;
    
    virtual void exec() override;
};
