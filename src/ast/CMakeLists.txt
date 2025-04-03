cmake_minimum_required(VERSION 3.13)
project( AST )

set (expression ${PROJECT_SOURCE_DIR}/expressions/source)
set (statement ${PROJECT_SOURCE_DIR}/statements/source)

add_library(
    ast
    STATIC
        ${PROJECT_SOURCE_DIR}/AST.cpp

        ${expression}/UnaryExpression.cpp
        ${expression}/BinaryExpression.cpp
        ${expression}/IntegerExpression.cpp
        ${expression}/BooleanExpression.cpp
        ${expression}/FloatExpression.cpp
        ${expression}/StringExpression.cpp
        ${expression}/VariableGetterExpression.cpp
        ${expression}/ArgumentedExpression.cpp

        ${expression}/Evaluate.cpp
        ${expression}/operations.cpp
        
        ${statement}/BlockStatement.cpp
        ${statement}/InitStatement.cpp
        ${statement}/FunctionStatement.cpp
        ${statement}/ClassStatement.cpp
        ${statement}/ConstantVariableStatement.cpp
        ${statement}/ForStatement.cpp
        ${statement}/IfElseStatement.cpp
        ${statement}/SwitchCaseStatement.cpp
        ${statement}/VariableStatement.cpp
        ${statement}/WhileStatement.cpp
        ${statement}/DoStatement.cpp
        ${statement}/TypeStatement.cpp
        ${statement}/ReturnStatement.cpp
        ${statement}/SystemFunctionStatement.cpp
        ${statement}/SpecialStatement.cpp
        ${statement}/ContinueStatement.cpp
        ${statement}/BreakStatement.cpp

        ${statement}/Execute.cpp
)

target_include_directories(ast PUBLIC .)
target_include_directories(ast PUBLIC ${PROJECT_SOURCE_DIR}/expressions/include)
target_include_directories(ast PUBLIC ${PROJECT_SOURCE_DIR}/statements/include)

unset(expression)
unset(statement)
