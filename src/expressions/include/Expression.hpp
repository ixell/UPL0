#pragma once
#include <memory>
#include "expressionTypesList.hpp"
using std::unique_ptr;

class Expression {
public:
	virtual ExpressionType get_type() = 0;
	virtual ~Expression() = default;
};