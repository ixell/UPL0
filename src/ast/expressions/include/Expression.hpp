#pragma once
#include <memory>
#include "AST.hpp"
#include "expressionTypesList.hpp"
// #define ptr_t std::shared_ptr

class Expression {
public:
	virtual ExpressionType get_type() const = 0;
	virtual ~Expression() = default;

	virtual Expression* eval(Variables& locals) const = 0;
	virtual Expression* copy() const = 0;
};