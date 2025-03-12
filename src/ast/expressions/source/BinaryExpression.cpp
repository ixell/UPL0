#include "all_expressions.hpp"
#include "BinaryExpression.hpp"

BinaryExpression::BinaryExpression(Operation operation, Expression* left, Expression* right)
	: operation(operation), left(left), right(right) {}

BinaryExpression::BinaryExpression(const BinaryExpression& other)
	: BinaryExpression(other.operation, other.left->copy(), other.right->copy()) {}

//std::wstring BinaryExpression::to_string() const {
//	return	L'(' + left->to_string() +
//			L' ' + to_wstring(operation) +
//			L' ' + right->to_string() + L')';
//}

ExpressionType BinaryExpression::get_type() const {
	return ExpressionType::BinaryExpression;
}

BinaryExpression::~BinaryExpression() {
	delete left, right;
}

Expression* BinaryExpression::copy() const {
    return static_cast<Expression*>(new BinaryExpression(*this));
};

const Expression* BinaryExpression::get_left() const {
	return left;
}

const Expression* BinaryExpression::get_right() const {
	return right;
}

Operation BinaryExpression::get_operation() const {
	return operation;
}
