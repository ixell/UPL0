cmake_minimum_required (VERSION 3.13)
project(expressions)

set(header "${PROJECT_SOURCE_DIR}/include")
set(source "${PROJECT_SOURCE_DIR}/source")

add_library (
    expressions
    STATIC
        ${header}/all_expressions.hpp

        ${header}/Expression.hpp
        ${header}/BinaryExpression.hpp
        ${header}/UnaryExpression.hpp
        ${header}/IntegerExpression.hpp
        ${header}/operations.hpp
        ${header}/BooleanExpression.hpp

        ${source}/UnaryExpression.cpp
        ${source}/BinaryExpression.cpp
        ${source}/IntegerExpression.cpp
        ${source}/operations.cpp
        ${source}/BooleanExpression.cpp
)

target_include_directories (
    expressions
    PUBLIC
        ${header}
        ${source}
)

unset(header)
unset(source)
