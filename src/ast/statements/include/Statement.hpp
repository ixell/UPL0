#pragma once
#include "Expression.hpp"
#include "statementTypesList.hpp"

class Statement {
public:
	virtual StatementType get_type() const = 0;
	virtual ~Statement() = default;
};

class InternalStatement : public Statement {};
class ExternalStatement : public Statement {};
