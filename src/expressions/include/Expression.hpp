#pragma once
#include <memory>
#include "expressionTypesList.hpp"
#define ptr_t std::shared_ptr

class Expression {
public:
	virtual ExpressionType get_type() const = 0;
	virtual ~Expression() = default;
};