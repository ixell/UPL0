#include "token.hpp"

extern TokenType conversation_array[0x80];

Token::Token()
	: type(none), value() {}

constexpr Token::Token(Token::Type type)
	: type(type), value() {}

constexpr Token::Token(Type type, const wstring& value)
	: type(type), value(value) {}

constexpr Token::Token(Type type, wstring&& value)
	: type(type), value(value) {}

Token::Token(wchar_t ch)
	: type(ch >= 0x80 ? variable : conversation_array[ch]), value(&ch, &ch) {}

[[nodiscard]] constexpr Token::Type Token::get_type() const {
	return type;
}

[[nodiscard]] constexpr const wstring& Token::get_value() const {
	return value;
}

void Token::set_type(Type type) {
	this->type = type;
}

void Token::set_value(const wstring& value) {
	this->value = value;
}

void Token::set_value(wstring&& value) {
	this->value = value;
}

void Token::from_char(wchar_t ch) {
	type = ch >= 0x80 ? variable : conversation_array[ch];
	value = wstring(&ch, &ch);
}

TokenType char_to_token(wchar_t ch) {
	return ch >= 0x80 ? Token::variable : conversation_array[ch];
}

constexpr TokenType getGroup(TokenType token) {
	return (TokenType)(token & 0xf0000000);
}
constexpr TokenType getSubgroup(TokenType token) {
	return (TokenType)(token & 0xff000000);
}


#define BEGIN_CONVERSATION switch (this->type) {
#define END_CONVERSATION }
#define DEFAULT
#define GROUP(NAME, ID)
#define SUBGROUP(NAME, GROUP_ID, ID)
#define SUBGROUP_(NAME, ID)

#define _WORD(NAME, PREFIX, STRING)	\
case PREFIX##NAME:					\
	return std::wstring(STRING);	\

#define WORD(NAME) _WORD(NAME,, L#NAME)
#define WORD_(NAME, STRING) _WORD(NAME,, L#NAME " ( " #STRING " ) ")
#define SPECIAL(NAME, VALUE) _WORD(NAME,, std::wstring(L#NAME ": ") + VALUE)
#define OPERATOR(NAME, STRING) _WORD(NAME, operator_, L"operator: " #NAME " ( " #STRING " )")
#define KEYWORD(NAME) _WORD(NAME, keyword_, L"keyword: " #NAME)
#define ERROR(NAME) _WORD(NAME, error_, L"error: " #NAME)

constexpr std::wstring Token::to_string() const {
	BEGIN_CONVERSATION
		DEFAULT
			DEFAULT
				WORD(eof)
				WORD(none)
				SPECIAL(variable, value)
				SPECIAL(int_, value)
				SPECIAL(float_, value)
				SPECIAL(string, value)
			SUBGROUP_(endword, 1)
				WORD(endline)
		GROUP(operator_, 1)
			DEFAULT
				OPERATOR(dot, ".")					// .
				OPERATOR(comma, ",")				// ,
			SUBGROUP(assignable, operator_, 1)
				OPERATOR(assign, "=")				// =
				OPERATOR(not, "!")					// ! // not
				OPERATOR(lessThan, "<")				// <
				OPERATOR(greaterThan, ">")			// >
				OPERATOR(plus, "+")					// +
				OPERATOR(minus, "-")				// -
				OPERATOR(star, "*")					// *
				OPERATOR(slash, "/")				// /
				OPERATOR(procent, "%")				// %
				OPERATOR(binary_and, "&")			// &
				OPERATOR(binary_or, "|")			// |
				OPERATOR(binary_not, "~")			// ~
				OPERATOR(binary_xor, "^")			// ^
			SUBGROUP(assignment, operator_, 2)
				OPERATOR(equal, "==")				// ==
				OPERATOR(notEqual, "!=")			// !=
				OPERATOR(lessThanEqual, "<=")		// <=
				OPERATOR(greaterThanEqual, ">=")	// >=
				OPERATOR(assign_plus, "+=")			// +=
				OPERATOR(assign_minus, "-=")		// -=
				OPERATOR(assign_star, "*=")			// *=
				OPERATOR(assign_slash, "/=")		// /=
				OPERATOR(assign_procent, "%=")		// %=
				OPERATOR(assign_binary_and, "&=")	// &=
				OPERATOR(assign_binary_or, "|="	)	// |=
				OPERATOR(assign_binary_not, "~=")	// ~=
				OPERATOR(assign_binary_xor, "^=")	// ^=
			SUBGROUP(special, operator_, 3)
				OPERATOR(increment, "++")			// ++
				OPERATOR(decrement, "--")			// --
				OPERATOR(arrow, "->")				// ->
				OPERATOR(and, "&&")					// && // and
				OPERATOR(or, "||")					// || // or
		GROUP(parantheses, 3)
			DEFAULT
				WORD_(leftParenthesis, "(")			// (
				WORD_(rightParenthesis, ")")		// )
				WORD_(leftSquareBracket, "[")		// [
				WORD_(rightSquareBracket, "]")		// ]
				WORD_(leftBrace, "{")				// {
				WORD_(rightBrace, "}")				// }
				WORD_(quote, "'")					// '
				WORD_(double_quotes, "\"")			// "
		GROUP(keyword, 4)
			SUBGROUP(statements, keyword, 0)
				KEYWORD(if)
				KEYWORD(else)
				KEYWORD(switch)
				KEYWORD(case)
				KEYWORD(while)
				KEYWORD(do)
				KEYWORD(for)
				KEYWORD(class)
			SUBGROUP(types, keyword, 1)
				KEYWORD(int)
				KEYWORD(float)
				KEYWORD(string)
				KEYWORD(bool)
				KEYWORD(auto)
			SUBGROUP(modificators, keyword, 2)
				KEYWORD(const)
				KEYWORD(friend)
			SUBGROUP(values, keyword, 3)
				KEYWORD(true)
				KEYWORD(false)
		GROUP(special, 5)
			DEFAULT
				WORD_(comment, "( // )")			// //
		default:
			throw;
	END_CONVERSATION
}


#undef BEGIN_CONVERSATION
#undef END_CONVERSATION
#undef DEFAULT
#undef GROUP
#undef SUBGROUP
#undef _WORD
#undef WORD
#undef SPECIAL
#undef OPERATOR
#undef KEYWORD
#undef ERROR

#define T Token::

TokenType conversation_array[0x80] = {
	T eof,					T none,					T none,					T eof,
	T eof,					T none,					T none,					T none,
	T none,					T endword,				T endline,				T endword,
	T none,					T none,					T none,					T none,
	T eof,					T none,					T none,					T none,
	T none,					T none,					T none,					T none,
	T none,					T eof,					T eof,					T eof,
	T none,					T none,					T none,					T none,
	T endword,				T operator_not,			T double_quotes,		T sharp,
	T word,					T operator_procent,		T operator_binary_and,	T quote,
	T leftParenthesis,		T rightParenthesis,		T operator_star,		T operator_plus,
	T operator_comma,		T operator_minus,		T operator_dot,			T operator_slash,
	T number,				T number,				T number,				T number,
	T number,				T number,				T number,				T number,
	T number,				T number,				T colon,				T endcommand,
	T operator_lessThan,	T operator_equal,		T operator_greaterThan,	T operator_questionMark,
	T at,					T word,					T word,					T word,
	T word,					T word,					T word,					T word,
	T word,					T word,					T word,					T word,
	T word,					T word,					T word,					T word,
	T word,					T word,					T word,					T word,
	T word,					T word,					T word,					T word,
	T word,					T word,					T word,					T leftSquareBracket,
	T backslash,			T rightSquareBracket,	T operator_binary_xor,	T word,
	T backtick,				T word,					T word,					T word,
	T word,					T word,					T word,					T word,
	T word,					T word,					T word,					T word,
	T word,					T word,					T word,					T word,
	T word,					T word,					T word,					T word,
	T word,					T word,					T word,					T word,
	T word,					T word,					T word,					T leftBrace,
	T operator_binary_or,	T rightBrace,			T operator_binary_not,	T none
};

#undef T
