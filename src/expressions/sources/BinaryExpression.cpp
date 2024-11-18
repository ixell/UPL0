#include "BinaryExpression.hpp"

BinaryExpression::BinaryExpression(Operation operation, Expression*&& expr1, Expression*&& expr2)
	: operation(operation), expr1(expr1), expr2(expr2) {}

std::wstring BinaryExpression::to_string() const {
	return	L'(' + expr1->to_string() +
			L' ' + to_wstring(operation) +
			L' ' + expr2->to_string() + L')';
}
