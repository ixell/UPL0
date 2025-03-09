#include "UnaryExpression.hpp"

UnaryExpression::UnaryExpression(Operation operation, Expression* value)
	: operation(operation), expr(value) {}

UnaryExpression::UnaryExpression(const UnaryExpression& other)
	: UnaryExpression(other.operation, other.expr->copy()) {}

//std::wstring UnaryExpression::to_string() const {
//	switch (operation) {
//	case Operation::postfix_decrement:
//	case Operation::postfix_increment:
//		return expr->to_string() + to_wstring(operation);
//	}
//	return to_wstring(operation) + expr->to_string();
//}

ExpressionType UnaryExpression::get_type() const {
	return ExpressionType::UnaryExpression;
}

UnaryExpression::~UnaryExpression() {
	delete expr;
}

Expression* UnaryExpression::copy() const {
    return static_cast<Expression*>(new UnaryExpression(*this));
};

const Expression* UnaryExpression::get_value() const {
	return expr;
}

Operation UnaryExpression::get_operation() const {
	return operation;
}
    
Expression* UnaryExpression::eval() const {
	//...
}
