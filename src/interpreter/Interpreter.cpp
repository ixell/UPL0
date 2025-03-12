#include "Interpreter.hpp"
#include "all_statements.hpp"
#include "VariableGetterExpression.hpp"
#include "ArgumentedExpression.hpp"

Interpreter::Interpreter(const std::vector<Statement*>& ast)
        : variables() {
    for (Statement* statement : ast) {
        switch (statement->get_type()) {
        case StatementType::ClassStatement:
            variables.global()[static_cast<ClassStatement*>(statement)->get_name()]
                = Space::Variable(statement);
            break;
        case StatementType::FunctionStatement:
            variables.global()[static_cast<FunctionStatement*>(statement)->get_name()]
                = Space::Variable(statement);
            break;
        case StatementType::VariableStatement:
            variables.global()[static_cast<VariableStatement*>(statement)->get_name()]
                = Space::Variable(statement);
            break;
        case StatementType::InitStatement: {
            InitStatement* init = static_cast<InitStatement*>(statement);
            variables.global()[init->get_variable()->get_name()]
                = Space::Variable(statement, init->get_args()[0]);
            }
        }
    }
}

void Interpreter::run() {
    if (variables.global().find(L"main") == variables.global().end())
        throw;
    ArgumentedExpression(Operation::call, new VariableGetterExpression(L"main"), {}).eval(variables);
}
