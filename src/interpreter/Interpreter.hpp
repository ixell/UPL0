#pragma once
#include <map>
#include "all_expressions.hpp"
#include "all_statements.hpp"

class Interpreter {
private:
    std::map<std::wstring, Statement*> structs{};
    std::map<std::wstring, Statement*> variables{};
    FunctionStatement* main;
public:
    Interpreter(const std::vector<Statement*>& ast);

    void run();
};
