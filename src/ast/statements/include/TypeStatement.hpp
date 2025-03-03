#pragma once
#include <vector>
#include <string>
#include "Statement.hpp"
#include "typeModificators.hpp"

class TypeStatement : public Statement {
private:
    std::vector<Modificator> modificators;
    std::vector<Statement*> template_;
    std::wstring type;
public:
    TypeStatement(
        const std::wstring& type,
        const std::vector<Modificator>& modificators,
        const std::vector<Statement*>& template_
    );
    TypeStatement(
        const std::wstring& type,
        const std::vector<Modificator>& modificators
    );
    TypeStatement(const std::wstring& type);

	virtual StatementType get_type() const override;
    virtual ~TypeStatement();

    const std::vector<Modificator>& get_modificators() const;
    const std::vector<Statement*>& get_template() const;
    const std::wstring& get_type_value() const;
    
    virtual void exec() override;
};