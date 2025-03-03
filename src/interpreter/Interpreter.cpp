#include "Interpreter.hpp"

Interpreter::Interpreter(const std::vector<Statement*>& ast) {
    for (Statement* statement : ast) {
        StatementType type = statement->get_type();
        switch (type) {
        case StatementType::ClassStatement:
            structs[static_cast<ClassStatement*>(statement)->get_name()]
                = statement;
            continue;
        case StatementType::FunctionStatement:
            structs[static_cast<FunctionStatement*>(statement)->get_name()]
                = statement;
            continue;
        case StatementType::VariableStatement:
            structs[static_cast<VariableStatement*>(statement)->get_name()]
                = statement;
            continue;
        }
    }
}

void Interpreter::run() {
    
}
