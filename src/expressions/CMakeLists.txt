cmake_minimum_required (VERSION 3.13)

set(header "${PROJECT_SOURCE_DIR}/expressions/include")
set(source "${PROJECT_SOURCE_DIR}/expressions/sources")

add_library (
    expressions
    STATIC
        ${header}/all.hpp

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
