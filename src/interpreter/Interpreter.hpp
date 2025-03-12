#pragma once
#include <map>
#include <vector>
#include "Statement.hpp"
#include "Expression.hpp"

class Interpreter {
private:
    Variables variables;
public:
    Interpreter(const std::vector<Statement*>& ast);

    void run();
};
