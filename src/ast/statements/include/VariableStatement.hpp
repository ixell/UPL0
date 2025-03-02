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

	virtual StatementType get_type() const override;
    virtual ~VariableStatement();

    TypeStatement* get_variable_type() const;
    const std::wstring& get_name() const;
};
