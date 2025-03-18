#include "Interpreter.hpp"
#include "systemFunctions.hpp"
#include "all_statements.hpp"
#include "VariableGetterExpression.hpp"
#include "ArgumentedExpression.hpp"

Interpreter::Interpreter(std::vector<Statement*>&& ast)
        : variables() {
    for (SystemFunctionStatement* func : systemFunctions::system_functions) {
        variables.global()[static_cast<SystemFunctionStatement*>(func)->get_name()]
            = new SystemFunctionStatement(*func);
    }
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
        case StatementType::InitStatement:
            InitStatement* init = static_cast<InitStatement*>(statement);
            init->exec(variables);
        }
    }
    ast.clear();
}

void Interpreter::run() {
    if (variables.global().find(L"main") == variables.global().end())
        throw;
    ArgumentedExpression(Operation::call, new VariableGetterExpression(L"main"), {}).eval(variables);
    for (std::pair<const std::wstring, Space::Variable>& var : variables.global()) {
        delete var.second.var;
        if (var.second.value != nullptr)
            delete var.second.value;
    }
}

#ifdef DEBUG

Variables& Interpreter::get_variables() {
    return variables;
}

void Interpreter::debug_run() {
    if (variables.global().find(L"main") == variables.global().end())
        throw;
    ArgumentedExpression(Operation::call, new VariableGetterExpression(L"main"), {}).eval(variables);
}

void Interpreter::delete_variables() {
    while (!variables.locals_empty()) {
        for (auto& subspace : variables.local()) {
            for (std::pair<const std::wstring, Space::Variable>& var : subspace) {//...
                delete var.second.var;
                if (var.second.value != nullptr)
                    delete var.second.value;
            }
        }
        variables.pop_local();
    }
    for (std::pair<const std::wstring, Space::Variable>& var : variables.global()) {
        delete var.second.var;
        if (var.second.value != nullptr)
            delete var.second.value;
    }
}

#endif // DEBUG
