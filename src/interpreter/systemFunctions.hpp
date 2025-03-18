#pragma once
#include <iostream>
#include <string>
#include "all_expressions.hpp"
#include "SystemFunctionStatement.hpp"

namespace systemFunctions {
    Expression* print(Variables& variables, std::vector<Expression*> args);

    extern std::vector<SystemFunctionStatement*> system_functions;
}
