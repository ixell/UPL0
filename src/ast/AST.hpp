#pragma once
#include <string>
#include <map>
#include <vector>
#include <stack>

class Statement;
class Expression;

class Space {
public:
    struct Variable {
        Statement* var;
        Expression* value;

        Variable(Statement* statement, Expression* expression);
        Variable(Statement* statement);
        Variable();
    };
private:
    std::vector<std::map<std::wstring, Variable>> variables;
    Expression* return_{nullptr};
public:
    Space(std::vector<std::map<std::wstring, Variable>>&& variables);
    Space(const std::vector<std::map<std::wstring, Variable>>& variables);
    Space();

    std::reverse_iterator<std::vector<std::map<std::wstring, Variable>>::iterator> begin();
    std::reverse_iterator<std::vector<std::map<std::wstring, Variable>>::iterator> end();
    std::reverse_iterator<std::vector<std::map<std::wstring, Variable>>::const_iterator> begin() const;
    std::reverse_iterator<std::vector<std::map<std::wstring, Variable>>::const_iterator> end() const;
    std::map<std::wstring, Variable>& top();
    const std::map<std::wstring, Variable>& top() const;
    Variable& operator[](const std::wstring& variable);
    Variable& find_variable(const std::wstring& name) const;
    void add_subspace(std::map<std::wstring, Variable>&& variables);
    void add_subspace();
    void pop_subspace();

    Expression* get_return() const;
    void set_return(Expression* expr);
};

class Variables {
private:
    std::map<std::wstring, Space::Variable> _global;
    std::stack<Space> _locals;
public:
    Variables();
    std::map<std::wstring, Space::Variable>& global();
    Space& local();

    void add_local();
    void pop_local();

    Space::Variable& find_variable(const std::wstring& name);
};
