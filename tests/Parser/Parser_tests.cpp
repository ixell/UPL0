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
	[[nodiscard]] static Statement* parse_global(Parser& parser)			{ return parser.parse_global(); }
	[[nodiscard]] static Statement* parse_definition(Parser& parser)		{ return parser.parse_definition(); }
	[[nodiscard]] static Statement* parse_function(Parser& parser)			{ return parser.parse_function(); }
	[[nodiscard]] static BlockStatement* parse_code(Parser& parser)			{ return parser.parse_code(); }
	[[nodiscard]] static std::vector<Statement*> parse_args(Parser& parser)	{ return parser.parse_args(); }
	[[nodiscard]] static Statement* parse_statement(Parser& parser)  		{ return parser.parse_statement(); }
	[[nodiscard]] static Statement* parse_type(Parser& parser)				{ return parser.parse_type(); }
	[[nodiscard]] static Expression* parse_expression(Parser& parser)		{ return parser.parse_expression(); }
	[[nodiscard]] static Expression* parse_multiplicative(Parser& parser)	{ return parser.parse_multiplicative(); }
	[[nodiscard]] static Expression* parse_additive(Parser& parser)			{ return parser.parse_additive(); }
	[[nodiscard]] static Expression* parse_unary(Parser& parser)			{ return parser.parse_unary(); }
	[[nodiscard]] static Expression* parse_primary(Parser& parser)			{ return parser.parse_primary(); }

	static bool match(Parser& parser, TokenType type)						{ return parser.match(type); }
	[[nodiscard]] static Token& get(Parser& parser, size_t pos)				{ return parser.get(pos); }
	[[nodiscard]] static Token& get(Parser& parser)							{ return parser.get(); }
	static Token& next(Parser& parser)										{ return parser.next(); }
};

#define ALLOCATE_MEMORY()
#define FREE_OBJECT(OBJECT) delete OBJECT;
#define SET_CODE(CODE) std::wstring code(L##CODE);
#define SET_CORRECT(TYPE, ...) std::vector<TYPE*> correct = {__VA_ARGS__};
#define SET_CORRECT_EXPRESSIONS(...) SET_CORRECT(Expression, __VA_ARGS__);
#define SET_CORRECT_STATEMENTS(...) SET_CORRECT(Statement, __VA_ARGS__);
#define EXPRESSION(TYPE, ...) static_cast<Expression*>(new TYPE(__VA_ARGS__))
#define STATEMENT(TYPE, ...) static_cast<Statement*>(new TYPE(__VA_ARGS__))

#define PREPARE_SEGMENT_PART(SEGMENT, TYPE, COUNT)											\
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
			size_t iteration = 0;															\
			for (size_t i = 0; ParserGetter::get(parser).get_type() != Token::eof; ++i) {	\
				ASSERT_NO_THROW(input.push_back(ParserGetter::SEGMENT(parser)));			\
				++iteration;																\
				if (iteration == COUNT) break;												\
			}																				\
		}																					\
	}

#define PREPARE_SEGMENT(SEGMENT, TYPE) PREPARE_SEGMENT_PART(SEGMENT, TYPE, -1U)
#define PREPARE() PREPARE_SEGMENT(parse_global, Statement)

void check(const Expression* expr, const Expression* correct);

void check(const Statement* statement, const Statement* correct) {
	StatementType type = statement->get_type();
	ASSERT_EQ(type, correct->get_type()) << "Different statements";
	switch (type) {
	case StatementType::DoStatement:
		check(
			static_cast<const DoStatement*>(statement)->get_expression(),
			static_cast<const DoStatement*>(correct)->get_expression()
		);
		return;
	case StatementType::BlockStatement:	{
		const BlockStatement* block0 { static_cast<const BlockStatement*>(statement) };
		const BlockStatement* block1 { static_cast<const BlockStatement*>(correct) };
		ASSERT_EQ(block0->get_count(), block1->get_count());
		for (size_t i = 0; i != block0->get_count(); ++i)
			check(block0->get_statement(i), block1->get_statement(i));
		return;
	}
	case StatementType::TypeStatement: {
		const TypeStatement* type0 { static_cast<const TypeStatement*>(statement) };
		const TypeStatement* type1 { static_cast<const TypeStatement*>(correct) };
		ASSERT_EQ(type0->get_type_value(), type1->get_type_value());
		{
			const std::vector<Modificator>& mod0 = type0->get_modificators();
			const std::vector<Modificator>& mod1 = type1->get_modificators();
			ASSERT_EQ(mod0.size(), mod1.size());
			for (size_t i = 0; i != mod0.size(); ++i)
				ASSERT_EQ(mod0.at(i), mod1.at(i));
		}
		{
			const std::vector<Statement*> templates0 = type0->get_template();
			const std::vector<Statement*> templates1 = type1->get_template();
			ASSERT_EQ(templates0.size(), templates1.size());
			for (size_t i = 0; i != templates0.size(); ++i)
				check(templates0.at(i), templates1.at(i));
		}
		return;
	}
	case StatementType::ClassVariableStatement:
		ASSERT_EQ(
			static_cast<const ClassStatement::ClassVariableStatement*>(statement)->get_access(),
			static_cast<const ClassStatement::ClassVariableStatement*>(correct)->get_access()
		);
		[[fallthrough]];
	case StatementType::VariableStatement: {
		const VariableStatement* var0 = static_cast<const VariableStatement*>(statement);
		const VariableStatement* var1 = static_cast<const VariableStatement*>(correct);
		ASSERT_EQ(var0->get_name(), var1->get_name());
		check(static_cast<Statement*>(var0->get_type_expression()),
			static_cast<Statement*>(var1->get_type_expression()));
		return;
	}
	case StatementType::InitStatement: {
		const InitStatement* init0 = static_cast<const InitStatement*>(statement);
		const InitStatement* init1 = static_cast<const InitStatement*>(correct);
		check(static_cast<const Statement*>(init0->get_variable()),
			static_cast<const Statement*>(init1->get_variable()));
		const std::vector<Expression*> args0 = init0->get_args();
		const std::vector<Expression*> args1 = init1->get_args();
		ASSERT_EQ(args0.size(), args1.size());
		for (size_t i = 0; i != args0.size(); ++i)
			check(args0.at(i), args1.at(i));
		return;
	}
	case StatementType::IfElseStatement: {
		const IfElseStatement* statement0 = static_cast<const IfElseStatement*>(statement);
		const IfElseStatement* statement1 = static_cast<const IfElseStatement*>(correct);
		check(static_cast<const Expression*>(statement0->get_condition()),
			static_cast<const Expression*>(statement1->get_condition()));
		check(static_cast<const Statement*>(statement0->get_if_code()),
			static_cast<const Statement*>(statement1->get_if_code()));
		if (statement0->get_else_code() == nullptr)
			ASSERT_EQ(statement1->get_else_code(), nullptr);
		else {
			ASSERT_NE(statement1->get_else_code(), nullptr);
			check(static_cast<const Statement*>(statement0->get_else_code()),
				static_cast<const Statement*>(statement1->get_else_code()));
		}
		return;
	}
	case StatementType::SwitchCaseStatement: {
		const SwitchCaseStatement* statement0 = static_cast<const SwitchCaseStatement*>(statement);
		const SwitchCaseStatement* statement1 = static_cast<const SwitchCaseStatement*>(correct);
		check(static_cast<const Expression*>(statement0->get_item()),
			static_cast<const Expression*>(statement1->get_item()));
		ASSERT_EQ(statement0->get_cases().size(), statement1->get_cases().size());
		for (size_t i = 0; i != statement0->get_cases().size(); ++i) {
			check(static_cast<const Expression*>(statement0->get_case(i).first),
				static_cast<const Expression*>(statement1->get_case(i).first));
			check(static_cast<const Statement*>(statement0->get_case(i).second),
				static_cast<const Statement*>(statement1->get_case(i).second));
		}
		return;
	}
	case StatementType::WhileStatement:
	case StatementType::DoWhileStatement:
		{
			const WhileStatement* statement0 = static_cast<const WhileStatement*>(statement);
			const WhileStatement* statement1 = static_cast<const WhileStatement*>(correct);
			check(static_cast<const Expression*>(statement0->get_condition()),
				static_cast<const Expression*>(statement1->get_condition()));
			check(static_cast<const Statement*>(statement0->get_code()),
				static_cast<const Statement*>(statement1->get_code()));
			return;
		}
	case StatementType::ForStatement: {
		const ForStatement* statement0 = static_cast<const ForStatement*>(statement);
		const ForStatement* statement1 = static_cast<const ForStatement*>(correct);
		check(static_cast<const Statement*>(statement0->get_initializer()),
			static_cast<const Statement*>(statement1->get_initializer()));
		check(static_cast<const Expression*>(statement0->get_condition()),
			static_cast<const Expression*>(statement1->get_condition()));
		check(static_cast<const Statement*>(statement0->get_changer()),
			static_cast<const Statement*>(statement1->get_changer()));
		check(static_cast<const Statement*>(statement0->get_code()),
			static_cast<const Statement*>(statement1->get_code()));
		return;
	}
	case StatementType::MethodStatement:
		ASSERT_EQ(
			static_cast<const ClassStatement::MethodStatement*>(statement)->get_access(),
			static_cast<const ClassStatement::MethodStatement*>(correct)->get_access()
		);
		[[fallthrough]];
	case StatementType::FunctionStatement: {
		const FunctionStatement* func0 { static_cast<const FunctionStatement*>(statement) };
		const FunctionStatement* func1 { static_cast<const FunctionStatement*>(correct) };
		ASSERT_EQ(func0->get_name(), func1->get_name());
		check(static_cast<const Statement*>(func0->get_return_type()),
			static_cast<const Statement*>(func1->get_return_type()));
		{
			const std::vector<Statement*> args0 = func0->get_args();
			const std::vector<Statement*> args1 = func1->get_args();
			ASSERT_EQ(args0.size(), args1.size());
			for (size_t i = 0; i != args0.size(); ++i)
				check(args0.at(i), args1.at(i));
		}
		check(static_cast<Statement*>(func0->get_code()),
			static_cast<Statement*>(func1->get_code()));
		return;
	}
	case StatementType::ClassStatement: {
		const ClassStatement* cls0 = static_cast<const ClassStatement*>(statement);
		const ClassStatement* cls1 = static_cast<const ClassStatement*>(correct);
		ASSERT_EQ(cls0->get_name(), cls1->get_name());
		//...=
		{
			const std::vector<ClassStatement::ClassVariableStatement*>& vars0 { cls0->get_variables() };
			const std::vector<ClassStatement::ClassVariableStatement*>& vars1 { cls1->get_variables() };
			ASSERT_EQ(vars0.size(), vars1.size());
			for (size_t i = 0; i != vars0.size(); ++i)
				check(static_cast<Statement*>(vars0.at(i)), static_cast<Statement*>(vars1.at(i)));
		}
		{
			const std::vector<ClassStatement::MethodStatement*>& methods0 { cls0->get_methods() };
			const std::vector<ClassStatement::MethodStatement*>& methods1 { cls1->get_methods() };
			ASSERT_EQ(methods0.size(), methods1.size());
			for (size_t i = 0; i != methods0.size(); ++i)
				check(static_cast<Statement*>(methods0.at(i)), static_cast<Statement*>(methods1.at(i)));
		}
		check(static_cast<Statement*>(cls0->get_constructor()), static_cast<Statement*>(cls1->get_constructor()));
		check(static_cast<Statement*>(cls0->get_destructor()), static_cast<Statement*>(cls1->get_destructor()));
		return;
	}
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
		return;
	case ExpressionType::IntegerExpression:
		ASSERT_EQ(
			static_cast<const IntegerExpression*>(expr)->get_value(),
			static_cast<const IntegerExpression*>(correct)->get_value()
		) << "Integers are not equal";
		return;
	case ExpressionType::FloatExpression:
		ASSERT_FLOAT_EQ(
			static_cast<const FloatExpression*>(expr)->get_value(),
			static_cast<const FloatExpression*>(correct)->get_value()
		) << "Floats are not equal";
		return;
	case ExpressionType::BooleanExpression:
		ASSERT_EQ(
			static_cast<const BooleanExpression*>(expr)->get_value(),
			static_cast<const BooleanExpression*>(correct)->get_value()
		) << "Booleans are not equal";
		return;
	case ExpressionType::StringExpression:
		ASSERT_EQ(
			static_cast<const StringExpression*>(expr)->get_value(),
			static_cast<const StringExpression*>(correct)->get_value()
		) << "Strings are not equal";
		return;
	case ExpressionType::VariableGetterExpression:
		ASSERT_EQ(
			static_cast<const VariableGetterExpression*>(expr)->get_variable(),
			static_cast<const VariableGetterExpression*>(correct)->get_variable(),
		) << "Types of variables are different";
		ASSERT_EQ(
			static_cast<const VariableGetterExpression*>(expr)->get_path(),
			static_cast<const VariableGetterExpression*>(correct)->get_path(),
		) << "Paths of variables are different";
		return;
	default:
		EXPECT_TRUE(false) << "Unknown expression.";
		return;
	}
}

#define CHECK_ALL() {										\
	ASSERT_EQ(input.size(), correct.size());				\
	for (size_t i = 0; i != correct.size(); ++i) {			\
		ASSERT_NO_THROW(check(input[i], correct[i]));		\
		FREE_OBJECT(input[i]);								\
		FREE_OBJECT(correct[i]);							\
	}														\
}

#define CHECK_BEGIN() {										\
	{														\
		ASSERT_LE(correct.size(), input.size());			\
		size_t i = 0;										\
		for (; i != correct.size(); ++i) {					\
			ASSERT_NO_THROW(check(input[i], correct[i]));	\
			FREE_OBJECT(input[i]);							\
			FREE_OBJECT(correct[i]);						\
		}													\
		for (; i != input.size(); ++i)						\
			FREE_OBJECT(input[i]);							\
	}														\
}

TEST(Expressions, IntgerExpression) {
	SET_CODE("1");
	SET_CORRECT_EXPRESSIONS(
		EXPRESSION(IntegerExpression, 1),
	);
	PREPARE_SEGMENT_PART(parse_expression, Expression, 1)
	CHECK_ALL();
}

TEST(Expressions, BooleanExpression) {
	SET_CODE("true false");
	SET_CORRECT_EXPRESSIONS(
		EXPRESSION(BooleanExpression, true),
		EXPRESSION(BooleanExpression, false)
	);
	PREPARE_SEGMENT_PART(parse_expression, Expression, 2);
	CHECK_ALL();
}

TEST(Expressions, FloatExpression) {
	SET_CODE("0.1 123.123");
	SET_CORRECT_EXPRESSIONS(
		EXPRESSION(FloatExpression, 0.1f),
		EXPRESSION(FloatExpression, 123.123f)
	);
	PREPARE_SEGMENT_PART(parse_expression, Expression, 2);
	CHECK_ALL();
}

TEST(Expressions, StringExpression) {
	SET_CODE("\"abc\"");
	SET_CORRECT_EXPRESSIONS(
		EXPRESSION(StringExpression, L"abc")
	);
	PREPARE_SEGMENT_PART(parse_expression, Expression, 1);
	CHECK_ALL();
}

TEST(Expressions, CombinatedString) {
	SET_CODE(R"("abc" "def"\n"123")");
	SET_CORRECT_EXPRESSIONS(
		EXPRESSION(StringExpression, L"abcdef123")
	);
	PREPARE_SEGMENT_PART(parse_expression, Expression, 1);
	CHECK_ALL();
}

TEST(Expressions, VariableGetterExpression) {
	SET_CODE("a sp1::_b sp1::sp2::c0");
	SET_CORRECT_EXPRESSIONS(
		EXPRESSION(VariableGetterExpression, L"a"),
		EXPRESSION(VariableGetterExpression, L"_b", {L"sp1"}),
		EXPRESSION(VariableGetterExpression, L"c0", {L"sp1", L"sp2"})
	);
	PREPARE_SEGMENT_PART(parse_expression, Expression, 3);
	CHECK_ALL();
}

TEST(Expressions, UnaryExpression) {
	SET_CODE("++a a++");
	SET_CORRECT_EXPRESSIONS(
		EXPRESSION(UnaryExpression,
			Operation::prefix_increment,
			EXPRESSION(VariableGetterExpression, L"a")
		),
		EXPRESSION(UnaryExpression,
			Operation::postfix_increment,
			EXPRESSION(VariableGetterExpression, L"a")
		)
	);
	PREPARE_SEGMENT_PART(parse_expression, Expression, 2);
	CHECK_ALL();
}

TEST(Expressions, BinaryExpression) {
	SET_CODE("1+2 1==2");
	SET_CORRECT_EXPRESSIONS(
		EXPRESSION(BinaryExpression,
			Operation::plus,
			EXPRESSION(IntegerExpression, 1),
			EXPRESSION(IntegerExpression, 2)
		),
		
		EXPRESSION(BinaryExpression,
			Operation::equal,
			EXPRESSION(IntegerExpression, 1),
			EXPRESSION(IntegerExpression, 2)
		)
	);
	PREPARE_SEGMENT_PART(parse_expression, Expression, 2);
	CHECK_ALL();
}

TEST(Statements, DoStatement) {
	SET_CODE("1 + 2");
	SET_CORRECT_STATEMENTS(
		STATEMENT(DoStatement, EXPRESSION(BinaryExpression,
			Operation::plus,
			EXPRESSION(IntegerExpression, 1),
			EXPRESSION(IntegerExpression, 2)
		))
	);
	PREPARE_SEGMENT_PART(parse_statement, Statement, 1);
	CHECK_ALL();
}

TEST(CodeStatements, BlockStatement) {
	SET_CODE(":\n\t1\n\t2\n");
	SET_CORRECT_STATEMENTS(
		STATEMENT(BlockStatement, {
			STATEMENT(DoStatement, EXPRESSION(IntegerExpression, 1)),
			STATEMENT(DoStatement, EXPRESSION(IntegerExpression, 2))
		})
	);
	PREPARE_SEGMENT(parse_code, Statement);
	CHECK_ALL();
}

TEST(CodeStatements, EmptyBlock) {
	SET_CODE(":\n\t;;;;\n");
	SET_CORRECT_STATEMENTS(
		STATEMENT(BlockStatement, {})
	);
	PREPARE_SEGMENT(parse_code, Statement);
	CHECK_ALL();
}
	
TEST(CodeStatements, IfElseStatement) {
	SET_CODE("if x == 1:\n\t1\nelse:\n\t2\n");
	SET_CORRECT_STATEMENTS(
		STATEMENT(IfElseStatement,
			new BinaryExpression(
				Operation::equal,
				EXPRESSION(VariableGetterExpression, L"x"),
				EXPRESSION(IntegerExpression, 1)
			),
			new BlockStatement({
				STATEMENT(DoStatement, EXPRESSION(IntegerExpression, 1))
			}),
			new BlockStatement({
				STATEMENT(DoStatement, EXPRESSION(IntegerExpression, 2))
			})
		)
	);
	PREPARE_SEGMENT_PART(parse_statement, Statement, 1);
	CHECK_ALL();
}

TEST(CodeStatements, SwitchCaseStatement) {
	SET_CODE("switch x:\n\tcase 1:\n\t\t1\n\tcase 2:\n\t\t2\n" /*"..."*/);
	SET_CORRECT_STATEMENTS(
		STATEMENT(SwitchCaseStatement,
			new VariableGetterExpression(L"x"),
			{
				std::pair<Expression*, BlockStatement*>(
					EXPRESSION(IntegerExpression, 1),
					new BlockStatement({
						STATEMENT(DoStatement, EXPRESSION(IntegerExpression, 1))
					})
				),
				std::pair<Expression*, BlockStatement*>(
					EXPRESSION(IntegerExpression, 2),
					new BlockStatement({
						STATEMENT(DoStatement, EXPRESSION(IntegerExpression, 2))
					})
				)
			}//,
			//new BlockStatement({
			//	STATEMENT(DoStatement, EXPRESSION(IntegerExpression, 3))
			//})
		)
	);
	PREPARE_SEGMENT_PART(parse_statement, Statement, 1);
	CHECK_ALL();
}

TEST(CodeStatements, WhileStatement) {
	SET_CODE("while true:\n\t1\n");
	SET_CORRECT_STATEMENTS(
		STATEMENT(WhileStatement,
			EXPRESSION(BooleanExpression, true),
			new BlockStatement({
				STATEMENT(DoStatement, EXPRESSION(IntegerExpression, 1))
			})
		)
	);
	PREPARE_SEGMENT_PART(parse_statement, Statement, 1);
	CHECK_ALL();
}

TEST(CodeStatements, DoWhileStatement) {
	SET_CODE("do:\n\t1\nwhile true\n");
	SET_CORRECT_STATEMENTS(
		STATEMENT(DoWhileStatement,
			EXPRESSION(BooleanExpression, true),
			new BlockStatement({
				STATEMENT(DoStatement, EXPRESSION(IntegerExpression, 1))
			})
		)
	);
	PREPARE_SEGMENT_PART(parse_statement, Statement, 1);
	CHECK_ALL();
}

TEST(TypeStatements, InitStatement) {
	{
		SET_CODE("SomeType var = 4");
		SET_CORRECT_STATEMENTS(
			STATEMENT(InitStatement,
				new VariableStatement(
					new TypeStatement(
						L"SomeType"
					),
					L"var"
				),
				{
					EXPRESSION(IntegerExpression, 4)
				}
			)
		);
		PREPARE_SEGMENT_PART(parse_statement, Statement, 1);
		CHECK_ALL();
	}
}

TEST(TypeStatements, FunctionStatement) {
	SET_CODE("void function(int a):\n\t1\n");
	SET_CORRECT_STATEMENTS(
		STATEMENT(FunctionStatement,
			new TypeStatement(L"void"),
			L"function",
			{
				STATEMENT(VariableStatement,
					new TypeStatement(L"int"),
					L"a"
				)
			},
			//{},
			new BlockStatement({
				STATEMENT(DoStatement, EXPRESSION(IntegerExpression, 1))
			})
		)
	);
	PREPARE();
	CHECK_ALL();
}

TEST(TypeStatements, ClassStatement) {
	SET_CODE(
		"class A:\n"
		"\tprivate int x\n"
		"\tpublic ~construct(int x):\n"
		"\t\tthis.x = x\n"
		"\tprotected void method():\n"
		"\t\t0\n"
	);
	SET_CORRECT_STATEMENTS(
		STATEMENT(ClassStatement,
			L"A",
			//{},
			{
				new ClassStatement::ClassVariableStatement(
					ClassStatement::Access::PRIVATE,
					new TypeStatement(L"int"),
					L"x"
				)
			},
			{
				new ClassStatement::MethodStatement(
					ClassStatement::Access::PROTECTED,
					new TypeStatement(L"void"),
					L"method",
					{},
					new BlockStatement({
						STATEMENT(DoStatement, EXPRESSION(IntegerExpression, 0))
					})
				)
			},
			new ClassStatement::MethodStatement(
				ClassStatement::Access::PUBLIC,
				nullptr,
				L"",
				{
					STATEMENT(VariableStatement,
						new TypeStatement(L"int"),
						L"x"
					)
				},
				new BlockStatement({
					STATEMENT(DoStatement, EXPRESSION(BinaryExpression,
						Operation::assign,
						EXPRESSION(VariableGetterExpression, L"x", {L"this"}),
						EXPRESSION(VariableGetterExpression, L"x")
					))
				})
			),
			nullptr
		)
	);
	PREPARE();
	CHECK_ALL();
}
