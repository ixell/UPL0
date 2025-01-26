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

StatementType ClassStatement::MethodStatement::get_type() const {
    return StatementType::Unknown;
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

StatementType ClassStatement::ClassVariableStatement::get_type() const {
    return StatementType::Unknown;
}

ClassStatement::ClassVariableStatement::~ClassVariableStatement() = default;

ClassStatement::Access ClassStatement::ClassVariableStatement::get_access() const {
    return access;
}
    
ClassStatement::ClassStatement(
    std::wstring name,
    //...,
    std::vector<ClassVariableStatement*> variables,
    std::vector<MethodStatement*> methods
) :
    name(name),
    //...,
    variables(variables),
    methods(methods) {}

StatementType ClassStatement::get_type() const {
    return StatementType::Unknown;
}

ClassStatement::~ClassStatement() = default;

std::wstring ClassStatement::get_name() const {
    return name;
}

const std::vector<ClassStatement::ClassVariableStatement*>& ClassStatement::get_variables() const {
    return variables;
}

const std::vector<ClassStatement::MethodStatement*>& ClassStatement::get_methods() const {
    return methods;
}
