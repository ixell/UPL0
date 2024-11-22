#include "NumberExpression.hpp"

NumberExpression::NumberExpression(int64_t integer)
	: type(Type::integer), value(integer) {}

NumberExpression::NumberExpression()
	: type(Type::integer), value(0i64) {}

std::wstring NumberExpression::to_string() const {
	return std::to_wstring(value.integer);
}
