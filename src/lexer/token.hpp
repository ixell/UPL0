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
	constexpr Token(Type type);
	constexpr Token(Type type, const std::wstring& value);
	constexpr Token(Type type, std::wstring&& value);
	explicit Token(wchar_t ch);

	[[nodiscard]] constexpr Type get_type() const;
	[[nodiscard]] constexpr const std::wstring& get_value() const;

	void set_type(Type type);
	void set_value(const std::wstring& value);
	void set_value(std::wstring&& value);
public:
	void from_char(wchar_t ch);

	[[nodiscard]] constexpr std::wstring to_string() const;
};

using TokenType = Token::Type;

TokenType char_to_token(wchar_t ch);

[[nodiscard]] constexpr TokenType getGroup(TokenType token);
[[nodiscard]] constexpr TokenType getSubgroup(TokenType token);


#define BEGIN_TOKENS enum Token::Type {
#define END_TOKENS };
#define DEFAULT
#define GROUP(NAME, ID) NAME = (ID << 28),
#define SUBGROUP(NAME, GROUP_ID, ID) NAME = (Token::Type::##GROUP_ID + (ID << 24)),
#define SUBGROUP_(NAME, ID) NAME = (ID << 24),

#define WORD(NAME) NAME,
#define OPERATOR(NAME) operator_##NAME,
#define KEYWORD(NAME) keyword_##NAME,

BEGIN_TOKENS
	DEFAULT
		DEFAULT
			WORD(eof)
			WORD(none)
			WORD(variable)
			WORD(string)
			WORD(builtinVariable)
		SUBGROUP_(number, 1)
			WORD(int_)
			WORD(float_)
		SUBGROUP_(endword, 2)
			WORD(endline)
			WORD(endcommand)
	GROUP(operator_, 1)
		DEFAULT
			OPERATOR(dot)							// .
			OPERATOR(comma)							// ,
			OPERATOR(questionMark)					// ?
		SUBGROUP(operator_assignable, operator_, 1)
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
		SUBGROUP(operator_assignment, operator_, 2)
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
		SUBGROUP(operator_special, operator_, 3)
			OPERATOR(increment)						// ++
			OPERATOR(decrement)						// --
			OPERATOR(arrow)							// ->
			OPERATOR(and)							// && // and
			OPERATOR(or)							// || // or
	GROUP(parentheses, 3)
		DEFAULT
			WORD(leftParenthesis)					// (
			WORD(rightParenthesis)					// )
			WORD(leftSquareBracket)					// [
			WORD(rightSquareBracket)				// ]
			WORD(leftBrace)							// {
			WORD(rightBrace)						// }
			WORD(quote)								// '
			WORD(double_quotes)						// "
	GROUP(keyword, 4)
		SUBGROUP(keyword_statements, keyword, 0)
			KEYWORD(if)
			KEYWORD(else)
			KEYWORD(switch)
			KEYWORD(case)
			KEYWORD(while)
			KEYWORD(do)
			KEYWORD(for)
			KEYWORD(class)
		SUBGROUP(keyword_types, keyword, 1)
			KEYWORD(num)
			KEYWORD(string)
			KEYWORD(bool)
			KEYWORD(auto)
		SUBGROUP(keyword_modificators, keyword, 2)
			KEYWORD(const)
			KEYWORD(friend)
			KEYWORD(constexpr)
		SUBGROUP(keyword_values, keyword, 3)
			KEYWORD(true)
			KEYWORD(false)
	GROUP(special, 5)
		DEFAULT
			WORD(comment)							// //
			WORD(sharp)								// #
			WORD(colon)								// :
			WORD(backslash)							// \ 
			WORD(backtick)							// `
	GROUP(groups, 14)
		DEFAULT
			WORD(word)
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
