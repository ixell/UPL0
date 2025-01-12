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
        ${header}/BooleanExpression.hpp
        ${header}/TypeExpression.hpp
        ${header}/VariableExpression.hpp
        ${header}/ConstantVariableExpression.hpp

        ${source}/UnaryExpression.cpp
        ${source}/BinaryExpression.cpp
        ${source}/IntegerExpression.cpp
        ${source}/BooleanExpression.cpp
        ${source}/TypeExpression.cpp
        ${source}/VariableExpression.cpp
        ${source}/ConstantVariableExpression.cpp

        ${header}/operations.hpp
        ${header}/expressionTypesList.hpp
        ${header}/modificators.hpp
        
        ${source}/operations.cpp
)

target_include_directories (
    expressions
    PUBLIC
        ${header}
        ${source}
)

unset(header)
unset(source)
