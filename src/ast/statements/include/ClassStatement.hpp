#pragma once
#include <string>
#include <vector>
#include "Statement.hpp"
#include "FunctionStatement.hpp"
#include "VariableStatement.hpp"

class ClassStatement : public Statement {
public:
    enum class Access {
        UNKNOWN,
        PUBLIC,
        PROTECTED,
        PRIVATE
    };

    class MethodStatement : public FunctionStatement {
    private:
        Access access;
    public:
        MethodStatement(
            Access access,
            TypeStatement* type,
            const std::wstring& name,
            const std::vector<Statement*>& args,
            BlockStatement* code
        );

        virtual StatementType get_type() const override;
        virtual ~MethodStatement();

        Access get_access() const;
    };

    class ClassVariableStatement : public VariableStatement {
    private:
        Access access;
    public:
        ClassVariableStatement(Access access, TypeStatement* type, const std::wstring& name);
        
        virtual StatementType get_type() const override;
        virtual ~ClassVariableStatement();

        Access get_access() const;
    };
private:
    std::wstring name;
    //...
    std::vector<ClassVariableStatement*> variables;
    std::vector<MethodStatement*> methods;
public:
    ClassStatement(
        std::wstring name,
        //...,
        std::vector<ClassVariableStatement*> variables,
        std::vector<MethodStatement*> methods
    );

    virtual StatementType get_type() const override;
    virtual ~ClassStatement();

    std::wstring get_name() const;
    const std::vector<ClassVariableStatement*>& get_variables() const;
    const std::vector<MethodStatement*>& get_methods() const;
};
