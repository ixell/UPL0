#pragma once
#include <map>
#include <vector>
#include "Statement.hpp"
#include "Expression.hpp"

class Interpreter {
private:
    Variables variables;
public:
    Interpreter(std::vector<Statement*>&& ast);

    void run();

#ifdef DEBUG
    Variables& get_variables();
    void debug_run();
    void delete_variables();
#endif
};
