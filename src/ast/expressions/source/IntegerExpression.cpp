#include "IntegerExpression.hpp"

IntegerExpression::IntegerExpression(int64_t value)
	: value(value) {}

IntegerExpression::IntegerExpression()
	: value(0i64) {}

//std::wstring IntegerExpression::to_string() const {
//	return std::to_wstring(value.integer);
//}

ExpressionType IntegerExpression::get_type() const {
	return ExpressionType::IntegerExpression;
}

int64_t IntegerExpression::get_value() const {
	return value;
}

void change_value(int64_t value) {
	this->value = value;
}
