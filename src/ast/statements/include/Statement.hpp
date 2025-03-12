#pragma once
#include "AST.hpp"
#include "Expression.hpp"
#include "statementTypesList.hpp"
#include "jumpControl.hpp"

class Statement {
public:
	virtual StatementType get_type() const = 0;
	virtual ~Statement() = default;
	virtual Statement* copy() const = 0;

	virtual Jump exec(Variables& variables) = 0;
};
