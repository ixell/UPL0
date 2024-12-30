cmake_minimum_required (VERSION 3.13)
project(statements)

set(header "${PROJECT_SOURCE_DIR}/include")
set(source "${PROJECT_SOURCE_DIR}/source")

add_library (
    statements
    STATIC
        ${header}/all_statements.hpp

        ${header}/BlockStatement.hpp
        ${header}/InitStatement.hpp
        ${header}/Statement.hpp
        ${header}/statementTypesList.hpp

        ${source}/BlockStatement.cpp
        ${source}/InitStatement.cpp
)

target_include_directories (
    statements
    PUBLIC
        ${header}
        ${source}
)

unset(header)
unset(source)
