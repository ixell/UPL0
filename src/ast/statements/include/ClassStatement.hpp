#pragma once
#include <string>
#include <vector>
#include "Statement.hpp"
#include "FunctionStatement.hpp"
#include "VariableStatement.hpp"

class ClassStatement : public Statement {
public:
    enum Access {
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
        MethodStatement(const MethodStatement& other);

        virtual StatementType get_type() const override;
        virtual ~MethodStatement();
        virtual Statement* copy() const override;

        Access get_access() const;
        virtual Jump exec(Variables& variables) override;
    };

    class ClassVariableStatement : public VariableStatement {
    private:
        Access access;
    public:
        ClassVariableStatement(Access access, TypeStatement* type, const std::wstring& name);
        ClassVariableStatement(const ClassVariableStatement& other);
        
        virtual StatementType get_type() const override;
        virtual ~ClassVariableStatement();
        virtual Statement* copy() const override;

        Access get_access() const;
        virtual Jump exec(Variables& variables) override;
    };
private:
    std::wstring name;
    //...
    std::vector<ClassVariableStatement*> variables;
    std::vector<MethodStatement*> methods;
    MethodStatement *constructor, *destructor;
public:
    ClassStatement(
        std::wstring name,
        //...,
        std::vector<ClassVariableStatement*> variables,
        std::vector<MethodStatement*> methods,
        MethodStatement* constructor,
        MethodStatement* destructor
    );
    ClassStatement(const ClassStatement& other);

    virtual StatementType get_type() const override;
    virtual ~ClassStatement();
	virtual Statement* copy() const override;

    std::wstring get_name() const;
    const std::vector<ClassVariableStatement*>& get_variables() const;
    const std::vector<MethodStatement*>& get_methods() const;
    MethodStatement* get_constructor() const;
    MethodStatement* get_destructor() const;
    
    virtual Jump exec(Variables& variables) override;
};
