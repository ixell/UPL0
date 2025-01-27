cmake_minimum_required (VERSION 3.13)
project(expressions)

set(header "${PROJECT_SOURCE_DIR}/include")
set(source "${PROJECT_SOURCE_DIR}/source")

add_library (
    expressions
    STATIC
        ${source}/UnaryExpression.cpp
        ${source}/BinaryExpression.cpp
        ${source}/IntegerExpression.cpp
        ${source}/BooleanExpression.cpp
        ${source}/FloatExpression.cpp
        ${source}/StringExpression.cpp
        ${source}/VariableGetterExpression.cpp
        
        ${source}/operations.cpp
)

target_include_directories (
    expressions
    PUBLIC
        ${header}
)

unset(header)
unset(source)
