#include "UnaryExpression.hpp"

UnaryExpression::UnaryExpression(Operation operation, Expression*&& expr)
	: operation(operation), expr(expr) {}

std::wstring UnaryExpression::to_string() const {
	switch (operation) {
	case Operation::postfix_decrement:
	case Operation::postfix_increment:
		return expr->to_string() + to_wstring(operation);
	}
	return to_wstring(operation) + expr->to_string();
}
