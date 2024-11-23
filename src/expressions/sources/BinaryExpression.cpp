#include "BinaryExpression.hpp"

BinaryExpression::BinaryExpression(Operation operation, ptr_t<Expression> left, ptr_t<Expression> right)
	: operation(operation), left(left), right(right) {}

//std::wstring BinaryExpression::to_string() const {
//	return	L'(' + left->to_string() +
//			L' ' + to_wstring(operation) +
//			L' ' + right->to_string() + L')';
//}

ExpressionType BinaryExpression::get_type() const {
	return ExpressionType::BinaryExpression;
}

const ptr_t<Expression> BinaryExpression::get_left() const {
	return left;
}

const ptr_t<Expression> BinaryExpression::get_right() const {
	return right;
}

OperationType BinaryExpression::get_operation() const {
	return operation;
}
