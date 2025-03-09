#pragma once
#include "VariableStatement.hpp"

class ConstantVariableStatement : public VariableStatement {
private:
    Expression* value;
public:
    ConstantVariableStatement(TypeStatement* type, const std::wstring& name, Expression* value);
    ConstantVariableStatement(const ConstantVariableStatement& other);

	virtual StatementType get_type() const override;
    virtual ~ConstantVariableStatement();
	virtual Statement* copy() const override;

    const Expression* get_value() const;
    
    virtual void exec() override;
};
