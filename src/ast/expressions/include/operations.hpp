#pragma once
#include "string"

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
	binary_not,						// ~
	assign,							// =
	plus,							// +
	plus_assign,					// +=
	minus,							// -
	minus_assign,					// -=
	multiply,						// *
	multiply_assign,				// *=
	divide,							// /
	divide_assign,					// /=
	modulus,						// %
	modulus_assign,					// %=
	binary_and,						// &
	binary_and_assign,				// &=
	binary_or,						// |
	binary_or_assign,				// |=
	binary_xor,						// ^
	binary_xor_assign,				// ^=
	leftShift,						// <<
	leftShift_assign,				// <<=
	rightShift,						// >>
	rightShift_assign				// >>=
};

std::wstring to_wstring(Operation operation);
