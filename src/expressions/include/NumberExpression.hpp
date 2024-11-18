#pragma once
#include "Expression.hpp"

class NumberExpression : public Expression {
public:
	enum class Type {
		integer,
		float_
	};
	union Value {
		int64_t integer;
		double float_;

		Value(int64_t integer);
		Value(double float_);
	};
private:
	Type type;
	Value value;
public:
	NumberExpression(Type, Value);
	NumberExpression(int64_t integer);
	NumberExpression(double float_);
	NumberExpression();

	virtual std::wstring to_string() const override;
	virtual ~NumberExpression() = default;
};
