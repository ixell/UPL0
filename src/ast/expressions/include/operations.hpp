#pragma once
#include "string"
#include "token.hpp"

enum OperationType {
	unary_prefix,
	unary_postfix,
	binary,
	argumented,
	other,
};

enum class Operation {
	none,
	dot,							// .
	arrow,							// ->
	comma,							// ,
	new_,							// new
	new_array,						// new[]
	delete_,						// delete
	delete_array,					// delete[]
	scope_resolution,				// ::
	prefix_increment,				// ++
	postfix_increment,				// ++
	prefix_decrement,				// --
	postfix_decrement,				// --
	logical_and,					// && // and
	logical_or,						// || // or
	logical_not,					// ! // not
	equal,							// ==
	notEqual,						// !=
	lessThan,						// <
	lessThanEq,						// <=
	greaterThan,					// >
	greaterThanEq,					// >=
	addressOf,						// &
	indirection,					// *
	call,							// ()
	subscript,						// []
	assign,							// =
	plus,							// +
	minus,							// -
	multiply,						// *
	divide,							// /
	modulus,						// %
	binary_and,						// &
	binary_or,						// |
	binary_not,						// ~
	binary_xor,						// ^
	leftShift,						// <<
	rightShift,						// >>
	plus_assign,					// +=
	minus_assign,					// -=
	multiply_assign,				// *=
	divide_assign,					// /=
	modulus_assign,					// %=
	leftShift_assign,				// <<=
	rightShift_assign,				// >>=
	binary_and_assign,				// &=
	binary_or_assign,				// |=
	binary_xor_assign				// ^=
};

std::wstring to_wstring(Operation operation);
Operation to_operation(Token::Type token, OperationType type);
