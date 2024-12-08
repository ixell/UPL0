#pragma once
#include "Expression.hpp"

class Statement {
public:
	virtual StatementType get_type() const = 0;
	virtual ~Statement() = default;
};