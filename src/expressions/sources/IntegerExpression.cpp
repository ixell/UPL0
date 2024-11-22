#include "IntegerExpression.hpp"

IntegerExpression::IntegerExpression(int64_t integer)
	: type(Type::integer), value(integer) {}

IntegerExpression::IntegerExpression()
	: type(Type::integer), value(0i64) {}

//std::wstring IntegerExpression::to_string() const {
//	return std::to_wstring(value.integer);
//}

ExpressionType IntegerExpression::get_value() const {
	return ExpressionType::IntegerExpression;
}
