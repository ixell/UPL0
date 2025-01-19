#define DEBUG 1
#define TESTING 1
#include <string>
#include <vector>
#include <iostream>
#include "pch.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"
#include "all_expressions.hpp"
#include "all_statements.hpp"

class ParserGetter {
public:
	[[nodiscard]] static Statement* global(Parser& parser)				{ return parser.global(); }
	[[nodiscard]] static Statement* define_variable(Parser& parser)		{ return parser.define_variable(); }
	[[nodiscard]] static Statement* function(Parser& parser)			{ return parser.function(); }
	[[nodiscard]] static BlockStatement* code(Parser& parser)			{ return parser.code(); }
	[[nodiscard]] static std::vector<Expression*> args(Parser& parser)	{ return parser.args(); }
	[[nodiscard]] static Expression* type(Parser& parser)				{ return parser.type(); }
	[[nodiscard]] static Expression* expression(Parser& parser)			{ return parser.expression(); }
	[[nodiscard]] static Expression* multiplicative(Parser& parser)		{ return parser.multiplicative(); }
	[[nodiscard]] static Expression* additive(Parser& parser)			{ return parser.additive(); }
	[[nodiscard]] static Expression* unary(Parser& parser)				{ return parser.unary(); }
	[[nodiscard]] static Expression* primary(Parser& parser)			{ return parser.primary(); }

	static bool match(Parser& parser, TokenType type)					{ return parser.match(type); }
	[[nodiscard]] static Token& get(Parser& parser, size_t pos)			{ return parser.get(pos); }
	[[nodiscard]] static Token& get(Parser& parser)						{ return parser.get(); }
	static Token& next(Parser& parser)									{ return parser.next(); }
};

#define ALLOCATE_MEMORY()
#define FREE_OBJECT(OBJECT) delete OBJECT;
#define SET_CODE(CODE) std::wstring code(L##CODE);
#define SET_CORRECT(...) std::vector<Expression*> correct = {__VA_ARGS__};
#define EXPRESSION(TYPE, ...) static_cast<Expression*>(new TYPE(__VA_ARGS__))
#define STATEMENT(TYPE, ...) static_cast<Statement*>(new TYPE(__VA_ARGS__))

#define PREPARE_SEGMENT(SEGMENT, TYPE)														\
	std::vector<TYPE*> input;																\
	{																						\
		std::vector<Token> tokens;															\
		{																					\
			std::wistringstream is(code);													\
			Lexer lexer(&is);																\
			lexer.tokenize(&tokens);														\
		}																					\
		{																					\
			Parser parser(tokens);															\
			if (tokens.empty()) EXPECT_TRUE(false) << "The tokens are empty.";				\
			for (size_t i = 0; ParserGetter::get(parser).get_type() != Token::eof; ++i) {	\
				input.push_back(ParserGetter::SEGMENT(parser));								\
			}																				\
		}																					\
	}

#define PREPARE() PREPARE_SEGMENT(global, statement)

void check(const Statement* expr, const Statement* correct) {
	StatementType type = expr->get_type();
	ASSERT_EQ(type, correct->get_type()) << "Different statements";
	switch (type) {
	default:
		EXPECT_TRUE(false) << "Unknown statement.";
	}
}

void check(const Expression* expr, const Expression* correct) {
	ExpressionType type = expr->get_type();
	ASSERT_EQ(type, correct->get_type()) << "Different expressions";
	switch (type) {
	case ExpressionType::BinaryExpression: {
		const BinaryExpression* expression = static_cast<const BinaryExpression*>(expr);
		const BinaryExpression* c = static_cast<const BinaryExpression*>(correct);
		check(expression->get_left(), c->get_left());
		check(expression->get_right(), c->get_right());
		return;
	}
	case ExpressionType::UnaryExpression:
		check(
			static_cast<const UnaryExpression*>(expr)->get_value(),
			static_cast<const UnaryExpression*>(correct)->get_value()
		);
	case ExpressionType::IntegerExpression:
		ASSERT_EQ(
			static_cast<const IntegerExpression*>(expr)->get_value(),
			static_cast<const IntegerExpression*>(correct)->get_value()
		) << "Integers are not equal";
	default:
		EXPECT_TRUE(false) << "Unknown expression.";S
	}
}

#define CHECK_ALL() {									\
	ASSERT_EQ(input.size(), correct.size());			\
	for (size_t i = correct.size() - 1; i != 0; --i) {	\
		ASSERT_NO_THROW(check(input[i], correct[i]));	\
		FREE_OBJECT(input[i]);							\
		FREE_OBJECT(correct[i]);						\
	}													\
}

TEST(Expressions, IntgerExpression) {
	SET_CODE("1");
	SET_CORRECT(
		EXPRESSION(IntegerExpression, 1),
	);
	PREPARE_SEGMENT(expression, Expression)
	CHECK_ALL();
}

TEST(Expressions, BooleanExpression) {
	SET_CODE("true false");
	SET_CORRECT(
		EXPRESSION(BooleanExpression, true),
		EXPRESSION(BooleanExpression, false)
	);
	PREPARE_SEGMENT(expression, Expression);
	CHECK_ALL();
}

TEST(Expressions, UnaryExpression) {
	SET_CODE("++1");
	SET_CORRECT(
		EXPRESSION(UnaryExpression,
			Operation::prefix_increment,
			EXPRESSION(IntegerExpression, 1)
		)
	);
	PREPARE_SEGMENT(expression, Expression);
	CHECK_ALL();
}

TEST(Expressions, BinaryExpression) {
	SET_CODE("1+2");
	SET_CORRECT(
		EXPRESSION(BinaryExpression,
			Operation::plus,
			EXPRESSION(IntegerExpression, 1),
			EXPRESSION(IntegerExpression, 2)
		)
	);
	PREPARE_SEGMENT(expression, Expression);
	CHECK_ALL();
}
