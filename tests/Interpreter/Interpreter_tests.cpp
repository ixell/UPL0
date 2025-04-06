#include "pch.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"
#include "Interpreter.hpp"
#include "all_expressions.hpp"
#include "all_statements.hpp"

#define ALLOCATE_MEMORY()
#define NEW(OBJECT) new OBJECT;
#define FREE(OBJECT) delete OBJECT;
#define EXPRESSION(TYPE, ...) static_cast<Expression*>(NEW(TYPE(__VA_ARGS__)))
#define STATEMENT(TYPE, ...) static_cast<Statement*>(NEW(TYPE(__VA_ARGS__)))
#define END() interpreter->delete_variables(); delete interpreter;

#define SET_CODE(CODE) std::wstring code(CODE);

#define RUN()             		        			\
Interpreter* interpreter;							\
{													\
	std::vector<Statement*> ast;            		\
	{                                       		\
		std::vector<Token> tokens;          		\
		{                                   		\
			std::wistringstream is(code);   		\
			Lexer lexer(&is);               		\
			lexer.tokenize(&tokens);        		\
			code.clear();							\
		}                                   		\
		{                                   		\
			Parser parser(tokens);          		\
			parser.parse(ast);              		\
		}                                   		\
	}                                       		\
	interpreter = new Interpreter(std::move(ast)); 	\
	ASSERT_NO_THROW(interpreter->debug_run());		\
}

Expression* to_expression(int value) {
    return static_cast<Expression*>(new IntegerExpression(value));
}

Expression* to_expression(float value) {
    return static_cast<Expression*>(new FloatExpression(value));
}

Expression* to_expression(bool value) {
    return static_cast<Expression*>(new BooleanExpression(value));
}

Expression* to_expression(const std::wstring& value) {
    return static_cast<Expression*>(new StringExpression(value));
}

Expression* to_expression(const wchar_t* value) {
    return static_cast<Expression*>(new StringExpression(value));
}

void check(const Expression* expr, const Expression* correct);

void check(const Statement* statement, const Statement* correct) {
	if (statement == nullptr || correct == nullptr) {
		ASSERT_EQ(statement, correct);
		return;
	}
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
		if (var0 == nullptr || var1 == nullptr) {
			ASSERT_EQ(var0, var1);
			return;
		}
		ASSERT_EQ(var0->get_name(), var1->get_name());
		check(static_cast<Statement*>(var0->get_variable_type()),
			static_cast<Statement*>(var1->get_variable_type()));
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
		check(static_cast<const Expression*>(statement0->get_changer()),
			static_cast<const Expression*>(statement1->get_changer()));
		check(static_cast<const Statement*>(statement0->get_code()),
			static_cast<const Statement*>(statement1->get_code()));
		return;
	}
	case StatementType::ReturnStatement:
		check(static_cast<const ReturnStatement*>(statement)->get_expression(),
			static_cast<const ReturnStatement*>(correct)->get_expression());
		return;
	case StatementType::MethodStatement:
		ASSERT_EQ(
			static_cast<const ClassStatement::MethodStatement*>(statement)->get_access(),
			static_cast<const ClassStatement::MethodStatement*>(correct)->get_access()
		);
		[[fallthrough]];
	case StatementType::FunctionStatement: {
		const FunctionStatement* func0 { static_cast<const FunctionStatement*>(statement) };
		const FunctionStatement* func1 { static_cast<const FunctionStatement*>(correct) };
		if (func0 == nullptr || func1 == nullptr) {
			ASSERT_EQ(func0, func1);
			return;
		}
		ASSERT_EQ(func0->get_name(), func1->get_name());
		check(static_cast<const Statement*>(func0->get_return_type()),
			static_cast<const Statement*>(func1->get_return_type()));
		{
			const std::vector<Statement*>& args0 = func0->get_args();
			const std::vector<Statement*>& args1 = func1->get_args();
			ASSERT_EQ(args0.size(), args1.size());
			for (size_t i = 0; i != args0.size(); ++i)
				check(args0.at(i), args1.at(i));
		}
		{
			const std::vector<Statement*>& template0 = func0->get_template();
			const std::vector<Statement*>& template1 = func1->get_template();
			ASSERT_EQ(template0.size(), template1.size());
			for (size_t i = 0; i != template0.size(); ++i)
				check(template0.at(i), template1.at(i));
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
	if (expr == nullptr || correct == nullptr) {
		ASSERT_EQ(expr, correct);
		return;
	}
	ExpressionType type = expr->get_type();
	ASSERT_EQ(type, correct->get_type()) << "Different expressions";
	switch (type) {
	case ExpressionType::BinaryExpression: {
		const BinaryExpression* expression = static_cast<const BinaryExpression*>(expr);
		const BinaryExpression* c = static_cast<const BinaryExpression*>(correct);
		ASSERT_EQ(expression->get_operation(), c->get_operation());
		check(expression->get_left(), c->get_left());
		check(expression->get_right(), c->get_right());
		return;
	}
	case ExpressionType::UnaryExpression:
		ASSERT_EQ(
			static_cast<const UnaryExpression*>(expr)->get_operation(),
			static_cast<const UnaryExpression*>(correct)->get_operation()
		);
		check(
			static_cast<const UnaryExpression*>(expr)->get_value(),
			static_cast<const UnaryExpression*>(correct)->get_value()
		);
		return;
	case ExpressionType::ArgumentedExpression: {
		const ArgumentedExpression* expression = static_cast<const ArgumentedExpression*>(expr);
		const ArgumentedExpression* c = static_cast<const ArgumentedExpression*>(correct);
		ASSERT_EQ(expression->get_operation(), c->get_operation());
		check(expression->get_main(), c->get_main());
		{
			const std::vector<Expression*>& args0 = expression->get_args();
			const std::vector<Expression*>& args1 = c->get_args();
			ASSERT_EQ(args0.size(), args1.size());
			for (size_t i = 0; i != args0.size(); ++i)
				check(args0.at(i), args1.at(i));
		}
	}
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
	case ExpressionType::VariableGetterExpression: {
		const VariableGetterExpression* var0 = static_cast<const VariableGetterExpression*>(expr);
		const VariableGetterExpression* var1 = static_cast<const VariableGetterExpression*>(correct);
		ASSERT_EQ(var0->get_name(),	var1->get_name());
		ASSERT_EQ(var0->get_path(), var1->get_path());
		{
			const std::vector<Expression*>& template0 = var0->get_template();
			const std::vector<Expression*>& template1 = var1->get_template();
			ASSERT_EQ(template0.size(), template1.size());
			for (size_t i = 0; i != template0.size(); ++i)
				check(template0.at(i), template1.at(i));
		}
		return;
		}
	default:
		EXPECT_TRUE(false) << "Unknown expression.";
		return;
	}
}

#define GET_VAR(VAR_NAME) (interpreter->get_variables().global()[L#VAR_NAME])
#define CHECK_VARIABLE(VAR_NAME, VALUE) check(GET_VAR(VAR_NAME).var, VALUE)
#define CHECK_VALUE(VAR_NAME, VALUE)												\
	ASSERT_EQ(GET_VAR(VAR_NAME).var->get_type(), StatementType::VariableStatement);	\
	check(GET_VAR(VAR_NAME).value, to_expression(VALUE))

TEST(RunTests, OnlyMain) {
	SET_CODE(L"void main():\n\t1");
	RUN();
	END();
}

TEST(EvalTests, ValueExpressions) {
	SET_CODE(
		L"void main():\n"
		"\t1\n"
		"\t1.0\n"
		"\ttrue\n"
		"\t\"123\"");
	RUN();
	END();
}

TEST(ExecTests, Initialization) {
	SET_CODE(L""
		"int a = 1\n"
		"int b = 7\n"
		"float c = 0.1\n"
		"bool d = true || false\n"
		"string e = \"123\"\n"
		"void main():\n"
		"\tint f = 1\n"
		"\tfloat a = 0.0\n"
	);
	RUN();
	CHECK_VALUE(a, 1);
	CHECK_VALUE(b, 7);
	CHECK_VALUE(c, 0.1f);
	CHECK_VALUE(d, true);
	CHECK_VALUE(e, L"123");
	END();
}

TEST(EvalTests, Calculations) {
	SET_CODE(L""
		"int a = 1\n"
		"int b = (a + 1) % 3\n"
		"float c = 1.0 / b\n"
		"float d = c * a + b\n"
		"bool e = true && (false || true)\n"
		"void main():\n"
		"\tfloat a = -1.0\n"
		"\tc = a * (d + b - c)\n"
		"\tb += 4\n"
	);
	RUN();
	CHECK_VALUE(a, 1);
	CHECK_VALUE(b, 6);
	CHECK_VALUE(c, -4.0f);
	CHECK_VALUE(d, 2.5f);
	CHECK_VALUE(e, true);
	END();
}

TEST(ExecTests, IfElseStatement) {
	SET_CODE(L""
		"int a = 0\n"
		"bool b = false\n"
		"bool c = false\n"
		"void main():\n"
		"\tif true:\n\t\ta = 1\n"
		"\telse:\n\t\ta = 2\n"
		"\tif true: b = true\n"
		"\tif false: 1\n"
		"\telse: c = true\n"
	);
	RUN();
	CHECK_VALUE(a, 1);
	CHECK_VALUE(b, true);
	CHECK_VALUE(c, true);
	END();
}

TEST(ExecTests, WhileStatement) {
	SET_CODE(L""
		"int a = 0\n"
		"int b = 0\n"
		"void main():\n"
		"\tint i = 10\n"
		"\twhile i != 0:\n"
		"\t\ta = a + 2\n"
		"\t\ti = i - 1\n"
		"\tdo:\n"
		"\t\tb = b + 3\n"
		"\t\ti = i - 1\n"
		"\twhile i > 0\n"
	);
	RUN();
	CHECK_VALUE(a, 20);
	CHECK_VALUE(b, 3);
	END();
}

TEST(ExecTests, ForStatement) {
	SET_CODE(L""
		"int a = 0\n"
		"void main():\n"
		"\tfor (int i = 0; i != 100; i = i + 5):\n"
		"\t\ta = a + 2\n"
	);
	RUN();
	CHECK_VALUE(a, 40);
	END();
}

TEST(ExecTests, FunctionStatement) {
	SET_CODE(L""
		"int a = 0\n"
		"int f(int a, int b):\n"
		"\treturn a + b\n"
		"void main():\n"
		"\ta = f(2, 5)\n"
	);
	RUN();
	CHECK_VALUE(a, 7);
	END();
}

TEST(ExecTests, SwitchCaseStatement) {
	SET_CODE(L""
		"int a = 0\n"
		"void main():\n"
		"\tfor (int i = 0; i != 3; i += 1):\n"
		"\t\tswitch i:\n"
		"\t\t\tcase 0:\n"
		"\t\t\t\ta += 1\n"
		"\t\t\tcase 2:\n"
		"\t\t\t\ta += 10\n"
		"\t\t\tcase 3:\n"
		"\t\t\t\ta += 100\n"
		"\t\t\tcase 10:\n"
		"\t\t\t\ta += 1000\n"
	);
	RUN();
	CHECK_VALUE(a, 11);
	END();
} 

TEST(ExecTests, JumpStatements) {
	SET_CODE(L""
		"int a = 0\n"
		"void main():\n"
		"\tfor (int i = 0; i != 5; i += 1):\n"
		"\t\ta += 1\n"
		"\t\tswitch i:\n"
		"\t\t\tcase 1:\n"
		"\t\t\t\tcontinue\n"
		"\t\t\tcase 2:\n"
		"\t\t\t\tbreak\n"
		"\t\ta += 10\n"
	);
	RUN();
	CHECK_VALUE(a, 13);
	END();
}

TEST(ExecTests, SpaceUsing) {
	SET_CODE(L""
		"int a = 0\n"
		"void main():\n"
		"\tint b = 2\n"
		"\tif true:\n"
		"\t\tb = 1\n"
		"\tif true:\n"
		"\t\tint b = 3\n"
		"\ta = b\n"
	)
	RUN();
	CHECK_VALUE(a, 1);
	END();
}
