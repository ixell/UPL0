cmake_minimum_required (VERSION 3.13)
project(statements)

set(header "${PROJECT_SOURCE_DIR}/include")
set(source "${PROJECT_SOURCE_DIR}/source")

add_library (
    statements
    STATIC
        ${source}/BlockStatement.cpp
        ${source}/InitStatement.cpp
        ${source}/FunctionStatement.cpp
        ${source}/ClassStatement.cpp
        ${source}/ConstantVariableStatement.cpp
        ${source}/ForStatement.cpp
        ${source}/IfElseStatement.cpp
        ${source}/SwitchCaseStatement.cpp
        ${source}/VariableStatement.cpp
        ${source}/WhileStatement.cpp
        ${source}/DoStatement.cpp
        ${source}/TypeStatement.cpp
        ${source}/ReturnStatement.cpp
        
        ${header}/statementTypesList.hpp
)

target_include_directories (
    statements
    PUBLIC
        ${header}
)

unset(header)
unset(source)
