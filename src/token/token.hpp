#pragma once
#include <string>

using std::wstring, std::operator""s;

class Token {
public:
	enum Type;
private:
	Type type;
	std::wstring value;
public:
	Token();
	Token(Type type);
	Token(Type type, const std::wstring& value);
	Token(Type type, std::wstring&& value);
	explicit Token(wchar_t ch);

	[[nodiscard]] Type get_type() const;
	[[nodiscard]] const std::wstring& get_value() const;

	void set_type(Type type);
	void set_value(const std::wstring& value);
	void set_value(std::wstring&& value);
public:
	void from_char(wchar_t ch);

	[[nodiscard]] std::wstring to_string() const;
};

using TokenType = Token::Type;

TokenType char_to_token(wchar_t ch);

TokenType getGroup(TokenType token);
TokenType getSubgroup(TokenType token);


#define BEGIN_TOKENS enum Token::Type {
#define END_TOKENS };
#define DEFAULT
#define GROUP(NAME, ID) NAME = (ID << 28),
#define SUBGROUP(NAME, GROUP_ID, ID) NAME = ((GROUP_ID << 28) + (ID << 24)),

#define WORD(NAME) NAME,
#define OPERATOR(NAME) operator_##NAME,
#define KEYWORD(NAME) keyword_##NAME,
#define ERROR(NAME) error_##NAME,

BEGIN_TOKENS
	DEFAULT
		DEFAULT
			WORD(eof)
			WORD(none)
			WORD(word)
			WORD(string)
			WORD(variable)
		SUBGROUP(number, 0, 1)
			WORD(integer)
			WORD(float_)
		SUBGROUP(endword, 0, 2)
			WORD(tab)
			WORD(endline)
			WORD(endcommand)
	GROUP(operator_, 1)
		DEFAULT
			OPERATOR(dot)							// .
			OPERATOR(comma)							// ,
			OPERATOR(questionMark)					// ?
		SUBGROUP(operator_assignable, 1, 1)
			OPERATOR(assign)						// =
			OPERATOR(not)							// ! // not
			OPERATOR(lessThan)						// <
			OPERATOR(greaterThan)					// >
			OPERATOR(plus)							// +
			OPERATOR(minus)							// -
			OPERATOR(star)							// *
			OPERATOR(slash)							// /
			OPERATOR(procent)						// %
			OPERATOR(binary_and)					// &
			OPERATOR(binary_or)						// |
			OPERATOR(binary_not)					// ~
			OPERATOR(binary_xor)					// ^
			OPERATOR(binary_leftShift)				// <<
			OPERATOR(binary_rightShift)				// >>
		SUBGROUP(operator_assignment, 1, 2)
			OPERATOR(equal)							// ==
			OPERATOR(notEqual)						// !=
			OPERATOR(lessThanEqual)					// <=
			OPERATOR(greaterThanEqual)				// >=
			OPERATOR(assign_plus)					// +=
			OPERATOR(assign_minus)					// -=
			OPERATOR(assign_star)					// *=
			OPERATOR(assign_slash)					// /=
			OPERATOR(assign_procent)				// %=
			OPERATOR(assign_binary_and)				// &=
			OPERATOR(assign_binary_or)				// |=
			OPERATOR(assign_binary_not)				// ~=
			OPERATOR(assign_binary_xor)				// ^=
			OPERATOR(assign_binary_leftShift)		// <<=
			OPERATOR(assign_binary_rightShift)		// >>=
		SUBGROUP(operator_special, 1, 3)
			OPERATOR(increment)						// ++
			OPERATOR(decrement)						// --
			OPERATOR(arrow)							// ->
			OPERATOR(and)							// && // and
			OPERATOR(or)							// || // or
	GROUP(brackets, 2)
		DEFAULT
			WORD(leftParenthesis)					// (
			WORD(rightParenthesis)					// )
			WORD(leftSquareBracket)					// [
			WORD(rightSquareBracket)				// ]
			WORD(leftBrace)							// {
			WORD(rightBrace)						// }
			WORD(quote)								// '
			WORD(double_quotes)						// "
			//   tab
			WORD(untab)
	GROUP(keyword, 3)
		SUBGROUP(keyword_statements, 3, 0)
			KEYWORD(if)
			KEYWORD(else)
			KEYWORD(switch)
			KEYWORD(case)
			KEYWORD(while)
			KEYWORD(do)
			KEYWORD(for)
			KEYWORD(class)
			KEYWORD(enum)
			KEYWORD(union)
			KEYWORD(import)
			KEYWORD(template)
			KEYWORD(namespace)
			KEYWORD(return)
			KEYWORD(elif)
		SUBGROUP(keyword_types, 3, 1)
			KEYWORD(type)
		SUBGROUP(keyword_modificators, 3, 2)
			KEYWORD(const)
			KEYWORD(friend)
		SUBGROUP(keyword_values, 3, 3)
			KEYWORD(true)
			KEYWORD(false)
		SUBGROUP(keyword_accesses, 3, 4)
			KEYWORD(public)
			KEYWORD(protected)
			KEYWORD(private)
	GROUP(other, 4)
		DEFAULT
			WORD(comment)							// //
			WORD(sharp)								// #
			WORD(colon)								// :
			WORD(backslash)							// \ 
			WORD(backtick)							// `
			WORD(at)								// @
	GROUP(errors, 5)
		SUBGROUP(error, 5, 0)
			ERROR(unknown)
			ERROR(indev)
		SUBGROUP(fatalError, 5, 1)
			ERROR(unknwonFatal)
		SUBGROUP(warning, 5, 2)
			ERROR(unknownWarning)
END_TOKENS

#undef BEGIN_TOKENS
#undef END_TOKENS
#undef DEFAULT
#undef GROUP
#undef SUBGROUP
#undef SUBGROUP_

#undef WORD
#undef OPERATOR
#undef KEYWORD
#undef ERROR
