#include "NumberExpression.hpp"

NumberExpression::Value::Value(int64_t integer)
	: integer(integer) {}

NumberExpression::Value::Value(double float_)
	: float_(float_) {}

NumberExpression::NumberExpression(Type type, Value value)
	: type(type), value(value) {}

NumberExpression::NumberExpression(int64_t integer)
	: type(Type::integer), value(integer) {}

NumberExpression::NumberExpression(double float_)
	: type(Type::float_), value(float_) {}

NumberExpression::NumberExpression()
	: type(Type::integer), value(0i64) {}

std::wstring NumberExpression::to_string() const {
	switch (type) {
	case NumberExpression::Type::integer: return std::to_wstring(value.integer);
	case NumberExpression::Type::float_: return std::to_wstring(value.float_);
	}
	throw;
}
