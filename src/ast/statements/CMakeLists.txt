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
        
        ${header}/statementTypesList.hpp
)

target_include_directories (
    statements
    PUBLIC
        ${header}
)

unset(header)
unset(source)
