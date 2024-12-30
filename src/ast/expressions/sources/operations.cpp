#include "operations.hpp"

std::wstring to_wstring(Operation operation) {
	switch (operation) {
	case Operation::none:				return L"";
	case Operation::dot:				return L".";
	case Operation::comma:				return L",";
	case Operation::new_:				return L"new";
	case Operation::delete_:			return L"delete";
	case Operation::scope_resolution:	return L"::";
	case Operation::prefix_increment:	return L"++";
	case Operation::postfix_increment:	return L"++";
	case Operation::prefix_decrement:	return L"--";
	case Operation::postfix_decrement:	return L"--";
	case Operation::logical_and:		return L"&&";
	case Operation::logical_or:			return L"||";
	case Operation::logical_not:		return L"!";
	case Operation::equal:				return L"==";
	case Operation::notEqual:			return L"!=";
	case Operation::lessThan:			return L"<";
	case Operation::lessThanEq:			return L"<=";
	case Operation::greaterThan:		return L">";
	case Operation::greaterThanEq:		return L">=";
	case Operation::addressOf:			return L"&";
	case Operation::indirection:		return L"*";
	case Operation::plus:				return L"+";
	case Operation::minus:				return L"-";
	case Operation::multiply:			return L"*";
	case Operation::divide:				return L"/";
	case Operation::modulus:			return L"%";
	case Operation::binary_and:			return L"&";
	case Operation::binary_or:			return L"|";
	case Operation::binary_not:			return L"~";
	case Operation::binary_xor:			return L"^";
	case Operation::leftShift:			return L"<<";
	case Operation::rightShift:			return L">>";
	case Operation::assign:				return L"=";
	}
	return L"";
}

Operation to_operation(Token::Type token, OperationType type) {
	if (!(token & (Token::operator_ | Token::parentheses))) throw;
	switch (type) {
	case unary_prefix:
		switch (token) {
		case Token::operator_increment:			return Operation::prefix_increment;
		case Token::operator_decrement:			return Operation::prefix_decrement;
		case Token::operator_plus:				return Operation::plus;
		case Token::operator_minus:				return Operation::minus;
		case Token::operator_star:				return Operation::indirection;
		case Token::operator_binary_not:		return Operation::binary_not;
		case Token::operator_binary_and:		return Operation::addressOf;
		}
		break;
	case unary_postfix:
		switch (token) {
		case Token::operator_increment:			return Operation::postfix_increment;
		case Token::operator_decrement:			return Operation::postfix_decrement;
		}
		break;
	case binary:
		switch (token) {
		case Token::operator_equal:				return Operation::equal;
		case Token::operator_notEqual:			return Operation::notEqual;
		case Token::operator_greaterThan:		return Operation::greaterThan;
		case Token::operator_greaterThanEqual:	return Operation::greaterThanEq;
		case Token::operator_lessThan:			return Operation::lessThan;
		case Token::operator_lessThanEqual:		return Operation::lessThanEq;
		case Token::operator_and:				return Operation::logical_and;
		case Token::operator_or:				return Operation::logical_or;
		case Token::operator_plus:				return Operation::plus;
		case Token::operator_minus:				return Operation::minus;
		case Token::operator_star:				return Operation::multiply;
		case Token::operator_slash:				return Operation::divide;
		case Token::operator_binary_leftShift:	return Operation::leftShift;
		case Token::operator_binary_rightShift:	return Operation::rightShift;
		case Token::operator_binary_xor:		return Operation::binary_xor;
		case Token::operator_binary_or:			return Operation::binary_or;
		case Token::operator_binary_and:		return Operation::binary_and;
		case Token::operator_assign:			return Operation::assign;
		}
	}
	return Operation::none;
}
