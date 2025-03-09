#pragma once
#include "Expression.hpp"
#include "statementTypesList.hpp"

class Statement {
public:
	virtual StatementType get_type() const = 0;
	virtual ~Statement() = default;
	virtual Statement* copy() const = 0;

	virtual void exec() = 0;
};
