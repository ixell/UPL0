#pragma once
#include "string"
#include "token.hpp"

enum OperationType {
	unary_prefix,
	unary_postfix,
	binary,
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
	rightShift						// >>
};

std::wstring to_wstring(Operation operation);
Operation to_operation(Token::Type token, OperationType type);
