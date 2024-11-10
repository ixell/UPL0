#define DEBUG
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

#define T(...) Token(Token::##__VA_ARGS__)

TEST(Operators, SimpleOperators) {
	SET_CODE("+ - * / = > < & | ^ ~ % ! , .");
	SET_CORRECT(
		T(operator_plus),
		T(operator_minus),
		T(operator_star),
		T(operator_slash),
		T(operator_assign),
		T(operator_greaterThan),
		T(operator_lessThan),
		T(operator_binary_and),
		T(operator_binary_or),
		T(operator_binary_xor),
		T(operator_binary_not),
		T(operator_procent),
		T(operator_not),
		T(operator_comma),
		T(operator_dot),
		T(eof)
	);
	PREPARE();
	CHECK_ALL();
}

TEST(Operators, AssignedOperators) {	
	SET_CODE("+= -= *= /= == >= <= &= |= ^= %= !=");
	SET_CORRECT(
		T(operator_assign_plus),
		T(operator_assign_minus),
		T(operator_assign_star),
		T(operator_assign_slash),
		T(operator_equal),
		T(operator_greaterThanEqual),
		T(operator_lessThanEqual),
		T(operator_assign_binary_and),
		T(operator_assign_binary_or),
		T(operator_assign_binary_xor),
		T(operator_assign_procent),
		T(operator_notEqual),
		T(eof)
	);
	PREPARE();
	CHECK_ALL();
}

TEST(Operators, SpecialOperators) {
	SET_CODE("++ -- && || << >> <<= >>= ->");
	SET_CORRECT(
		T(operator_increment),
		T(operator_decrement),
		T(operator_and),
		T(operator_or),
		T(operator_binary_leftShift),
		T(operator_binary_rightShift),
		T(operator_assign_binary_leftShift),
		T(operator_assign_binary_rightShift),
		T(operator_arrow),
		T(eof),
	);
	PREPARE();
	CHECK_ALL();
}

TEST(Operators, Groups) {
	SET_CODE("+++++ -----");
	SET_CORRECT(
		T(operator_increment),
		T(operator_plus),
		T(operator_increment),
		T(operator_decrement),
		T(operator_minus),
		T(operator_decrement),
		T(eof)
	);
	PREPARE();
	CHECK_ALL();
}

TEST(Words, Variables) {
	SET_CODE("a abcdefghijklmopqrstuvwxyz _ d_0 _0123456789");
	SET_CORRECT(
		T(variable, L"a"),
		T(variable, L"abcdefghijklmnopqrstuvwxyz"),
		T(variable, L"_"),
		T(variable, L"d_0"),
		T(variable, L"_0123456789"),
		T(eof)
	);
	PREPARE();
	CHECK_ALL();
}

TEST(Words, Keywords) {
	SET_CODE("if else switch case while for do class enum union import int float string bool auto const friend true false");
	SET_CORRECT(
		T(keyword_if),
		T(keyword_else),
		T(keyword_switch),
		T(keyword_case),
		T(keyword_while),
		T(keyword_for),
		T(keyword_do),
		T(keyword_class),
		T(keyword_enum),
		T(keyword_union),
		T(keyword_import),
		T(keyword_int),
		T(keyword_float),
		T(keyword_string),
		T(keyword_bool),
		T(keyword_auto),
		T(keyword_const),
		T(keyword_friend),
		T(keyword_true),
		T(keyword_false),
		T(eof)
	);
	PREPARE();
	CHECK_ALL();
}

TEST(Numbers, DecimalIntegers) {
	SET_CODE("1 2 3 4 5 6 7 8 9 0 1234567890 1'000'000");
	SET_CORRECT(
		T(integer, L"1"),
		T(integer, L"2"),
		T(integer, L"3"),
		T(integer, L"4"),
		T(integer, L"5"),
		T(integer, L"6"),
		T(integer, L"7"),
		T(integer, L"8"),
		T(integer, L"9"),
		T(integer, L"0"),
		T(integer, L"1234567890"),
		T(integer, L"1000000"),
		T(eof)
	);
	PREPARE();
	CHECK_ALL();
}

TEST(Numbers, HexadecimalIntegers) {
	SET_CODE("0x1 0x2 0x3 0x4 0x5 0x6 0x7 0x8 0x9 0xa 0xb 0xc 0xd 0xe 0xf 0xA 0xB 0xC 0xD 0xE 0xF 0x0 0X123 0x1234567890abcdef 0x10'00'00'00");
	SET_CORRECT(
		T(integer, L"x1"),
		T(integer, L"x2"),
		T(integer, L"x3"),
		T(integer, L"x4"),
		T(integer, L"x5"),
		T(integer, L"x6"),
		T(integer, L"x7"),
		T(integer, L"x8"),
		T(integer, L"x9"),
		T(integer, L"xa"),
		T(integer, L"xb"),
		T(integer, L"xc"),
		T(integer, L"xd"),
		T(integer, L"xe"),
		T(integer, L"xf"),
		T(integer, L"xa"),
		T(integer, L"xb"),
		T(integer, L"xc"),
		T(integer, L"xd"),
		T(integer, L"xe"),
		T(integer, L"xf"),
		T(integer, L"x0"),
		T(integer, L"x123"),
		T(integer, L"x1234567890abcdef"),
		T(integer, L"x10000000"),
		T(eof)
	);
	PREPARE();
	CHECK_ALL();
}

TEST(Numbers, BinaryIntegers) {
	SET_CODE("0b0 0b1 0B0 0B1 0b01 0b00011011 0b10000000'00000000");
	SET_CORRECT(
		T(integer, L"b0"),
		T(integer, L"b1"),
		T(integer, L"b0"),
		T(integer, L"b1"),
		T(integer, L"b01"),
		T(integer, L"b00011011"),
		T(integer, L"b1000000000000000"),
		T(eof)
	);
	PREPARE();
	CHECK_ALL();
}

TEST(Numbers, Float) {
	SET_CODE("0.0 1.0 1.1 123456789.123456789 .123456789");
	SET_CORRECT(
		T(float_, L"0.0"),
		T(float_, L"1.0"),
		T(float_, L"1.1"),
		T(float_, L"123456789.123456789"),
		T(float_, L"0.123456789"),
		T(eof)
	);
	PREPARE();
	CHECK_ALL();
}
