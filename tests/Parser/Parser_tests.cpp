#define DEBUG
#include <string>
#include <vector>
#include <iostream>
#include "pch.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"
#include "all.hpp"

#define ALLOCATE_MEMORY()
#define FREE_OBJECT(OBJECT) OBJECT.reset();
#define SET_CODE(CODE) std::wstring code(L##CODE);
#define SET_CORRECT(...) std::vector<ptr_t<Expression>> correct = {__VA_ARGS__};
#define Expr(TYPE, ...) ptr_t<Expression>(static_cast<Expression*>(new TYPE(__VA_ARGS__)))

#define PREPARE()												   		\
	std::vector<ptr_t<Expression>> expressions;							\
	{																	\
		std::vector<Token> tokens;										\
		{																\
			std::wistringstream is(code);								\
			Lexer lexer(&is);											\
			lexer.tokenize(&tokens);									\
		}																\
		{																\
			Parser parser(tokens);										\
			parser.parse(expressions);									\
		}																\
	}

void check(ptr_t<Expression> expr, ptr_t<Expression> correct) {
	ExpressionType type = expr->get_type();
	ASSERT_EQ(type, correct->get_type());
	switch (type) {
	case ExpressionType::BinaryExpression: {
		BinaryExpression* expression = static_cast<BinaryExpression*>(expr.get());
		BinaryExpression* c = static_cast<BinaryExpression*>(correct.get());
		check(expression->get_left(), c->get_left());
		check(expression->get_right(), c->get_right());
		return;
	}
	case ExpressionType::UnaryExpression:
		check(
			static_cast<UnaryExpression*>(expr.get())->get_value(),
			static_cast<UnaryExpression*>(correct.get())->get_value()
		);
	case ExpressionType::IntegerExpression:
		ASSERT_EQ(
			static_cast<IntegerExpression*>(expr.get())->get_value(),
			static_cast<IntegerExpression*>(correct.get())->get_value()
		);
	}
}

#define CHECK_ALL() {													\
	ASSERT_EQ(expressions.size(), correct.size());						\
		for (size_t i = correct.size() - 1; i != 0; --i) {				\
		check(expressions[i], correct[i]);								\
		FREE_OBJECT(expressions[i]);									\
		FREE_OBJECT(correct[i]);										\
	}																	\
}

TEST(Work, IntgerExpression) {
	SET_CODE("1;");
	SET_CORRECT(
		Expr(IntegerExpression, 1),
	);
	PREPARE();
	CHECK_ALL();
}

TEST(Work, UnaryExpression) {
	SET_CODE("++1;");
	SET_CORRECT(
		Expr(UnaryExpression,
			Operation::prefix_increment,
				Expr(IntegerExpression, 1)
		)
	);
	PREPARE();
	CHECK_ALL();
}

TEST(Work, BinaryExpression) {
	SET_CODE("1+2;");
	SET_CORRECT(
		Expr(BinaryExpression,
			Operation::plus,
				Expr(IntegerExpression, 1),
				Expr(IntegerExpression, 2)
		)
	);
	PREPARE();
	CHECK_ALL();
}

TEST(Work, BooleanExpression) {
	SET_CODE("true; false");
	SET_CORRECT(
		Expr(BooleanExpression, true),
		Expr(BooleanExpression, false)
	);
	PREPARE();
	CHECK_ALL();
}
