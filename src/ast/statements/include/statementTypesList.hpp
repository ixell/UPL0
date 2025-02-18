#pragma once

enum class StatementType {
    unknown,
    TypeStatement,
    VariableStatement,
    ConstantVariableStatement,
    InitStatement,
    DoStatement,
    BlockStatement,
    FunctionStatement,
    ClassStatement,
    ClassVariableStatement,
    MethodStatement,
    IfElseStatement,
    SwitchCaseStatement,
    WhileStatement,
    DoWhileStatement,
    ForStatement,
    EnumStatement,
    UnionStatement
};
