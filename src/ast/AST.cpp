#include "AST.hpp"

Space::Variable::Variable(Statement* variable, Expression* value)
    : var(variable), value(value) {}

Space::Variable::Variable(Statement* variable)
    : Variable(variable, nullptr) {}

Space::Variable::Variable() : Variable(nullptr, nullptr) {}

Space::Space(std::vector<std::map<std::wstring, Variable>>&& variables)
    : variables(variables), return_(nullptr) {}

Space::Space(const std::vector<std::map<std::wstring, Variable>>& variables)
    : variables(variables), return_(nullptr) {}

Space::Space()
    : variables(), return_(nullptr) {}

std::reverse_iterator<std::vector<std::map<std::wstring, Space::Variable>>::iterator> Space::begin() {
    return variables.rbegin();
}

std::reverse_iterator<std::vector<std::map<std::wstring, Space::Variable>>::iterator> Space::end() {
    return variables.rend();
}

std::reverse_iterator<std::vector<std::map<std::wstring, Space::Variable>>::const_iterator> Space::begin() const {
    return variables.crbegin();
}

std::reverse_iterator<std::vector<std::map<std::wstring, Space::Variable>>::const_iterator> Space::end() const {
    return variables.crend();
}

const std::map<std::wstring, Space::Variable>& Space::top() const {
    return variables.back();
}

std::map<std::wstring, Space::Variable>& Space::top() {
    return variables.back();
}

Space::Variable& Space::operator[](const std::wstring& variable) {
    return top()[variable];
}

Space::Variable* Space::find_variable(const std::wstring& name) {
    for (auto& subspace : variables) {
        if (subspace.find(name) != subspace.end()) {
            return &subspace[name];
        }
    }
    return nullptr;
}

const Space::Variable* Space::find_variable(const std::wstring& name) const {
    for (auto& subspace : variables) {
        if (subspace.find(name) != subspace.end()) {
            return &subspace.at(name);
        }
    }
    return nullptr;
}

void Space::add_subspace(std::map<std::wstring, Variable>&& variables) {
    this->variables.push_back(variables);
}

void Space::add_subspace() {
    variables.push_back({});
}

void Space::pop_subspace() {
    variables.erase(variables.end()-1);
}

Expression* Space::get_return() const {
    return return_;
}

void Space::set_return(Expression* expr) {
    return_ = expr;
}

Variables::Variables()
    : _global(), _locals() {}

std::map<std::wstring, Space::Variable>& Variables::global() {
    return _global;
}

Space& Variables::local() {
    return _locals.top();
}

std::map<std::wstring, Space::Variable>& Variables::top() {
    if (locals_empty())
        return global();
    return local().top();
}

bool Variables::locals_empty() {
    return _locals.empty();
}

void Variables::add_local() {
    _locals.push({});
}

void Variables::pop_local() {
    _locals.pop();
}

Space::Variable* Variables::find_variable(const std::wstring& name) {
    Space::Variable* var = _locals.empty() ? nullptr : local().find_variable(name);
    if (var != nullptr) return var;
    if (global().find(name) != global().end())
        return &global()[name];
    return nullptr;
}

