#include <string>
#include <vector>
#include <iostream>
#include "pch.hpp"
#include "Lexer.hpp"

#define SET_CODE(CODE) std::wstring code(L##CODE);
#define SET_CORRECT(...) std::vector<Token> correct = {__VA_ARGS__};

#define PREPARE()												   	\
	std::wistringstream is(code);									\
	Lexer lexer(&is);												\
	std::vector<Token> tokens;										\
	lexer.tokenize(&tokens);										\

#define CHECK_ALL() {												\
	ASSERT_EQ(tokens.size(), correct.size());						\
	for (int i = 0; i != correct.size(); ++i) {						\
		ASSERT_EQ(tokens[i].get_type(), correct[i].get_type());		\
		ASSERT_EQ(tokens[i].get_value(), correct[i].get_value());	\
	}																\
}																	\

TEST(Operators, SimpleOperators) {
	SET_CODE("+ - * / = > < & | ^ ~ % ! , .");
	SET_CORRECT(
		Token(Token::operator_plus),
		Token(Token::operator_minus),
		Token(Token::operator_star),
		Token(Token::operator_slash),
		Token(Token::operator_assign),
		Token(Token::operator_greaterThan),
		Token(Token::operator_lessThan),
		Token(Token::operator_binary_and),
		Token(Token::operator_binary_or),
		Token(Token::operator_binary_xor),
		Token(Token::operator_binary_not),
		Token(Token::operator_procent),
		Token(Token::operator_not),
		Token(Token::operator_comma),
		Token(Token::operator_dot),
		Token(Token::eof)
	);
	PREPARE();
	CHECK_ALL();
}

TEST(Operators, AssignedOperators) {	
	SET_CODE("+= -= *= /= == >= <= &= |= ^= %= !=");
	SET_CORRECT(
		Token(Token::operator_assign_plus, L""),
		Token(Token::operator_assign_minus, L""),
		Token(Token::operator_assign_star, L""),
		Token(Token::operator_assign_slash, L""),
		Token(Token::operator_equal, L""),
		Token(Token::operator_greaterThanEqual, L""),
		Token(Token::operator_lessThanEqual, L""),
		Token(Token::operator_assign_binary_and, L""),
		Token(Token::operator_assign_binary_or, L""),
		Token(Token::operator_assign_binary_xor, L""),
		Token(Token::operator_assign_procent, L""),
		Token(Token::operator_notEqual, L""),
		Token(Token::eof, L"")
	);
	PREPARE();
	CHECK_ALL();
}

TEST(Operators, SpecialOperators) {
	SET_CODE("++ -- && || << >> <<= >>= ->");
	SET_CORRECT(
		Token(Token::operator_increment, L""),
		Token(Token::operator_decrement, L""),
		Token(Token::operator_and, L""),
		Token(Token::operator_or, L""),
		Token(Token::operator_binary_leftShift, L""),
		Token(Token::operator_binary_rightShift, L""),
		Token(Token::operator_assign_binary_leftShift, L""),
		Token(Token::operator_assign_binary_rightShift, L""),
		Token(Token::operator_arrow, L""),
		Token(Token::eof, L""),
	);
	PREPARE();
	CHECK_ALL();
}

TEST(Operators, Groups) {
	SET_CODE("+++++ ----- *&");
	SET_CORRECT(
		Token(Token::operator_increment, L""),
		Token(Token::operator_plus, L""),
		Token(Token::operator_increment, L""),
		Token(Token::operator_decrement, L""),
		Token(Token::operator_minus, L""),
		Token(Token::operator_decrement, L""),
		Token(Token::operator_star, L""),
		Token(Token::operator_binary_and, L""),
		Token(Token::eof, L""),
	);
	PREPARE();
	CHECK_ALL();
}
