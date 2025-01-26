#pragma once
#include "VariableStatement.hpp"

class ConstantVariableStatement : public VariableStatement {
private:
    Expression* value;
public:
    ConstantVariableStatement(TypeStatement* type, const std::wstring& name, Expression* value);

	virtual StatementType get_type() const override;
    virtual ~ConstantVariableStatement();

    const Expression* get_value() const;
};
