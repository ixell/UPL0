#pragma once
#include "ClassStatement.hpp"

ClassStatement::MethodStatement::MethodStatement(
    ClassStatement::Access access,
    TypeStatement* type,
    const std::wstring& name,
    const std::vector<Statement*>& args,
    BlockStatement* code
) :
    access(access),
    FunctionStatement(type, name, args, code) {}

ClassStatement::MethodStatement::MethodStatement(const MethodStatement& other)
    : access(other.access), FunctionStatement(*static_cast<const FunctionStatement*>(&other)) {}

StatementType ClassStatement::MethodStatement::get_type() const {
    return StatementType::MethodStatement;
}

ClassStatement::MethodStatement::~MethodStatement() = default;

ClassStatement::Access ClassStatement::MethodStatement::get_access() const {
    return access;
}

ClassStatement::ClassVariableStatement::ClassVariableStatement(
    ClassStatement::Access access,
    TypeStatement* type,
    const std::wstring& name
) :
    access(access), VariableStatement(type, name) {}

ClassStatement::ClassVariableStatement::ClassVariableStatement(const ClassVariableStatement& other)
    : access(other.access), VariableStatement(*static_cast<const VariableStatement*>(&other)) {}

StatementType ClassStatement::ClassVariableStatement::get_type() const {
    return StatementType::ClassVariableStatement;
}

ClassStatement::ClassVariableStatement::~ClassVariableStatement() = default;

ClassStatement::Access ClassStatement::ClassVariableStatement::get_access() const {
    return access;
}
    
ClassStatement::ClassStatement(
    std::wstring name,
    //...,
    std::vector<ClassVariableStatement*> variables,
    std::vector<MethodStatement*> methods,
    MethodStatement* constructor,
    MethodStatement* destructor
) :
    name(name),
    //...,
    variables(variables),
    methods(methods),
    constructor(constructor),
    destructor(destructor) {}

ClassStatement::ClassStatement(const ClassStatement& other)
        : name(other.name), variables(), methods(), constructor(new MethodStatement(*other.constructor)),
            destructor(new MethodStatement(*other.destructor)) {
    variables.reserve(other.variables.size());
    methods.reserve(other.methods.size());
    for (ClassVariableStatement* var : other.variables) {
        variables.push_back(new ClassVariableStatement(*var));
    }
    for (MethodStatement* method : other.methods) {
        methods.push_back(new MethodStatement(*method));
    }
}

StatementType ClassStatement::get_type() const {
    return StatementType::ClassStatement;
}

ClassStatement::~ClassStatement() {
    for (ClassVariableStatement* var : variables)
        delete var;
    for (MethodStatement* method : methods)
        delete method;
    delete constructor, destructor;
}

Statement* ClassStatement::copy() const {
    return static_cast<Statement*>(new ClassStatement(*this));
}

std::wstring ClassStatement::get_name() const {
    return name;
}

const std::vector<ClassStatement::ClassVariableStatement*>& ClassStatement::get_variables() const {
    return variables;
}

const std::vector<ClassStatement::MethodStatement*>& ClassStatement::get_methods() const {
    return methods;
}

ClassStatement::MethodStatement* ClassStatement::get_constructor() const {
    return constructor;
}

ClassStatement::MethodStatement* ClassStatement::get_destructor() const {
    return destructor;
}
