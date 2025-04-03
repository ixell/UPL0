#include <list>
#include <stack>
#include "Parser.hpp"
#include "all_expressions.hpp"
#include "all_statements.hpp"

Operation to_operation(Token::Type token, OperationType type);

using ExprPtr = Expression*;

Parser::Parser(std::vector<Token>& tokens)
	: tokens(tokens), this_token(0), pos(0) {
	if (!tokens.empty())
		this_token = &tokens[0];
}

void Parser::parse(std::vector<Statement*>& statements) {
	if (tokens.empty()) throw;
	for (size_t i = 0; get().get_type() != Token::eof; ++i) {
		statements.push_back(parse_global());
	}
}

Statement* Parser::parse_global() {
	Statement* result;
	switch (get().get_type()) {
	case Token::variable:
	case Token::keyword_type:
		result = parse_definition(true);
		if (get().get_type() == Token::endline || get().get_type() == Token::endcommand)
			next();
		return result;
	case Token::keyword_class:
		return parse_class();
	default:
		switch (getSubgroup(get().get_type())) {
		case Token::keyword_modificators:
			result = parse_definition(true);
			if (get().get_type() == Token::endline || get().get_type() == Token::endcommand)
				next();
			return result;
		default:
			throw;
		}
	}
}

Statement* Parser::parse_class() {
	using Access = ClassStatement::Access;
    std::wstring class_name;
    //...;
    std::vector<ClassStatement::ClassVariableStatement*> variables;
    std::vector<ClassStatement::MethodStatement*> methods;
    ClassStatement::MethodStatement* constructor = nullptr;
    ClassStatement::MethodStatement* destructor = nullptr;

	consume(Token::keyword_class);
	if (!match(Token::variable))
		throw;
	class_name = get().get_value();
	next();
	if (match(Token::leftParenthesis)) {
		//...
	}
	consume(Token::colon);
	consume(Token::endline);
	consume(Token::tab);
	while (!match(Token::untab)) {
		if (getSubgroup(get().get_type()) == Token::keyword_accesses) {
			Access access = Access(get().get_type() - Token::keyword_public + 1);
			next();
			if (match(Token::operator_binary_not)) {
				next();
				if (!match(Token::variable))
					throw;
				if (get().get_value() == L"construct") {
					next();
					constructor = 
						static_cast<ClassStatement::MethodStatement*>(parse_function(nullptr, L"", access));
				}
				else if (get().get_value() == L"destruct") {
					next();
					destructor = 
						static_cast<ClassStatement::MethodStatement*>(parse_function(nullptr, L"", access));
				}
				else
					throw;
				continue;
			}
			if (!match(Token::variable) && !match(Token::keyword_type)
					&& getSubgroup(get().get_type()) != Token::keyword_modificators)
				throw;
			TypeStatement* type = static_cast<TypeStatement*>(parse_type());
			if (!match(Token::variable))
				throw;
			std::wstring name = get().get_value();
			next();
			switch (get().get_type()) {
			case Token::leftParenthesis: {
				methods.push_back(static_cast<ClassStatement::MethodStatement*>(
					parse_function(type, name, access)));
				break;
			}
			case Token::endcommand:
			case Token::endline:
				next();
				variables.push_back(new ClassStatement::ClassVariableStatement(access, type, name));
				break;
			default:
				throw;
			}
		}
		else {
			//...
			throw;
		}
	}
	next();
	return new ClassStatement(
		class_name,
		//...,
		variables,
		methods,
		constructor,
		destructor
	);
}

Statement* Parser::parse_definition(bool is_global) {
	TypeStatement* type = static_cast<TypeStatement*>(parse_type());
	if (!match(Token::variable))
		throw;
	std::wstring name = get().get_value();
	next();
	switch (get().get_type()) {
	case Token::leftParenthesis:
		return parse_function(type, name);
	case Token::operator_assign: {
		next();
		std::vector<ExprPtr> arg{ parse_expression() };
		return static_cast<Statement*>(new InitStatement(new VariableStatement(type, name), arg));
	}
	case Token::endcommand:
	case Token::endline: {
		std::vector<ExprPtr> arg{ nullptr };
		return static_cast<Statement*>(new InitStatement(new VariableStatement(type, name), arg));
	}
	default:
		throw;
	}
}

Statement* Parser::parse_function(Statement* type, const std::wstring& name, ClassStatement::Access access) {
	std::vector<Statement*> args = parse_args();
	BlockStatement* code;
	if (match(Token::colon))
		code = parse_code();
	else if (match(Token::endline) || match(Token::endcommand))
		code = nullptr;
	else
		throw;
	if (access != ClassStatement::Access::UNKNOWN)
		return static_cast<Statement*>(new ClassStatement::MethodStatement(
			access, static_cast<TypeStatement*>(type), name, args, code));
	return static_cast<Statement*>(new FunctionStatement(
		static_cast<TypeStatement*>(type), name, args, code));
}

std::vector<Statement*> Parser::parse_args() {
	TokenType opener = get().get_type();
	TokenType closer;
	if (opener == Token::operator_lessThan)
		closer = Token::operator_greaterThan;
	else closer = TokenType(opener + 1);
	next();
	std::vector<Statement*> args;
	while (match(Token::endline) || match(Token::tab) || match(Token::untab))
		next(); // ???
	if (get().get_type() == closer) {
		next();
		return args;
	}
	while (true) {
		TypeStatement* type = static_cast<TypeStatement*>(this->parse_type());
		Statement* arg = type;
		if (match(Token::variable)) {
			arg = static_cast<Statement*>(new VariableStatement(type, get().get_value()));
			next();
			if (match(Token::operator_assign)) {
				std::vector<Expression*> value = { parse_expression() };
				arg = static_cast<Statement*>(
					new InitStatement(static_cast<VariableStatement*>(arg), value));
				next();
			}
		}
		args.push_back(arg);
		if (!match(Token::operator_comma)) {
			if (match(closer)) {
				next();
				return args;
			}
			throw;
		}
		next();
	}
}

Statement* Parser::parse_type() {
	TypeStatement* statement;
	bool is_const = false;
	{
		std::vector<Modificator> modificators;
		while (getSubgroup(get().get_type()) == Token::keyword_modificators) {
			Modificator mod = Modificator::nothing;
			switch (get().get_type()) {
			// ...
			default:
				break;
			}
			modificators.push_back(mod);
			next();
		}
		if (!match(Token::variable) && !match(Token::keyword_type))
			throw;
		std::wstring type = get().get_value();
		next();
		std::vector<Statement*> template_;
		if (match(Token::operator_lessThan))
			template_ = parse_args();
		statement = new TypeStatement(type, modificators, template_);
	}
	while (!match(Token::variable)) {
		std::vector<Modificator> modificators;
		if (match(Token::keyword_const)) {
			modificators.push_back(Modificator::const_);
			next();
		}
		if (match(Token::operator_binary_and)) {
			std::vector<Statement*> template_ = {statement};
			statement = new TypeStatement(L"&", modificators, template_);
		}
		else
			throw;
		next();
	}
	return statement;
}

BlockStatement* Parser::parse_code() {
	std::vector<Statement*> code;
	ended_line = false;
	if (match(Token::endcommand) || match(Token::endline))
		return nullptr;
	consume(Token::colon);
	if (!match(Token::endline)) {
		while (true) {
			code.push_back(parse_statement());
			if (match(Token::endline) || ended_line)
				break;
			if (!match(Token::endcommand))
				throw;
		}
		next();
		ended_line = true;
		return new BlockStatement(std::move(code));
	}
	next();
	consume(Token::tab);
	while (!match(Token::untab)) {
		Statement* statement = this->parse_statement();
		if (statement != nullptr)
			code.push_back(statement);
		if (!ended_line) {
			if (!match(Token::endcommand) && !match(Token::endline))
				throw;
			next();
		}
	}
	next();
	ended_line = true;
	return new BlockStatement(std::move(code));
}

Statement* Parser::parse_statement() {
	switch (get().get_type()) {
	case Token::variable:
		switch (get(1).get_type()) {
		case Token::variable:
			return parse_definition(false);
		default:
			return static_cast<Statement*>(new DoStatement(parse_expression()));
		}
		return nullptr; //...
	case Token::integer:
	case Token::keyword_true:
	case Token::keyword_false:
	case Token::float_:
	case Token::string:
		return static_cast<Statement*>(new DoStatement(parse_expression()));
	case Token::keyword_type:
		if (get(1).get_type() == Token::leftParenthesis)
			return static_cast<Statement*>(new DoStatement(parse_expression()));
		return parse_definition(false);
	case Token::keyword_if:
		return parse_if_statement();
	case Token::keyword_switch:
		return parse_switch_statement();
	case Token::keyword_while:
	case Token::keyword_do:
		return parse_while_statement();
	case Token::keyword_for:
		return parse_for_statement();
	case Token::keyword_enum:
		next();
		return nullptr; //...
	case Token::keyword_return:
		next();
		return new ReturnStatement(parse_expression());
	case Token::endcommand:
	case Token::endline:
		next();
		ended_line = true;
		return nullptr;
	default:
		switch (getSubgroup(get().get_type())) {
		case Token::keyword_modificators:
			return parse_definition(false);
		default:
			throw; // syntax error
		}
	}
}

Statement* Parser::parse_if_statement() {
	next();
	Expression* condition = parse_expression();
	BlockStatement* if_code = parse_code();
	Statement* else_code = nullptr;
	if (match(Token::keyword_elif)) {
		else_code = parse_if_statement();
	} else if (match(Token::keyword_else)) {
		next();
		else_code = parse_code();
	}
	return static_cast<Statement*>(new IfElseStatement(condition, if_code, else_code));
}

Statement* Parser::parse_switch_statement() {
	next();
	Expression* item = parse_expression();
	if (match(Token::endcommand) || match(Token::endline))
		return static_cast<Statement*>(new SwitchCaseStatement(item, {}, nullptr));
	consume(Token::colon);
	consume(Token::endline);
	consume(Token::tab);
	std::vector<std::pair<Expression*, BlockStatement*>> cases;
	BlockStatement* default_case { nullptr };
	while (!match(Token::untab)) {
		consume(Token::keyword_case);
		//if (match(Token::...))
		Expression* item2 = parse_expression();
		BlockStatement* code = this->parse_code();
		cases.push_back(std::pair(item2, code));
	}
	next();
	return static_cast<Statement*>(new SwitchCaseStatement(item, cases, default_case));
}

Statement* Parser::parse_while_statement() {
	if (match(Token::keyword_while)) {
		next();
		Expression* condition = parse_expression();
		BlockStatement* code = this->parse_code();
		return static_cast<Statement*>(new WhileStatement(condition, code));
	}
	if (match(Token::keyword_do)) {
		next();
		BlockStatement* code = this->parse_code();
		consume(Token::keyword_while);
		Expression* condition = parse_expression();
		consume(Token::endline);
		return static_cast<Statement*>(new DoWhileStatement(condition, code));
	}
	throw;
}

Statement* Parser::parse_for_statement() {
	next();
	consume(Token::leftParenthesis);
	Statement* initializer = parse_statement();
	consume(Token::endcommand);
	Expression* condition = parse_expression();
	consume(Token::endcommand);
	Expression* changer = parse_expression();
	consume(Token::rightParenthesis);
	BlockStatement* code = parse_code();
	return static_cast<Statement*>(new ForStatement(initializer, condition, changer, code));
}


ExprPtr Parser::parse_expression() {
	return parse_assignation();
}

ExprPtr Parser::parse_assignation() {
	ExprPtr result = parse_logical_or();
	while (true) {
		TokenType token = get().get_type();
		switch (token) {
		case Token::operator_assign:
		case Token::operator_assign_binary_and:
		case Token::operator_assign_binary_leftShift:
		case Token::operator_assign_binary_not:
		case Token::operator_assign_binary_or:
		case Token::operator_assign_binary_rightShift:
		case Token::operator_assign_binary_xor:
		case Token::operator_assign_minus:
		case Token::operator_assign_plus:
		case Token::operator_assign_procent:
		case Token::operator_assign_slash:
		case Token::operator_assign_star:
			next();
			result = ExprPtr(new BinaryExpression(
				to_operation(token, binary),
				result, parse_logical_or()
			));
			continue;
		}
		return result;
	}
}

ExprPtr Parser::parse_logical_or() {
	ExprPtr result = parse_logical_and();
	while (match(Token::operator_or)) {
		next();
		result = ExprPtr(new BinaryExpression(
			Operation::logical_or,
			result, parse_logical_and()
		));
	}
	return result;
}

ExprPtr Parser::parse_logical_and() {
	ExprPtr result = parse_binary_or();
	while (match(Token::operator_and)) {
		next();
		result = ExprPtr(new BinaryExpression(
			Operation::logical_and,
			result, parse_binary_or()
		));
	}
	return result;
}

ExprPtr Parser::parse_binary_or() {
	ExprPtr result = parse_binary_xor();
	while (match(Token::operator_binary_or)) {
		next();
		result = ExprPtr(new BinaryExpression(
			Operation::binary_or,
			result, parse_binary_xor()
		));
	}
	return result;
}

ExprPtr Parser::parse_binary_xor() {
	ExprPtr result = parse_binary_and();
	while (match(Token::operator_binary_xor)) {
		next();
		result = ExprPtr(new BinaryExpression(
			Operation::binary_xor,
			result, parse_binary_and()
		));
	}
	return result;
}

ExprPtr Parser::parse_binary_and() {
	ExprPtr result = parse_comparison();
	while (match(Token::operator_binary_and)) {
		next();
		result = ExprPtr(new BinaryExpression(
			Operation::binary_and,
			result, parse_comparison()
		));
	}
	return result;
}


ExprPtr Parser::parse_comparison() {
	ExprPtr result = parse_shift();
	while (true) {
		TokenType token = get().get_type();
		switch (token) {
		case Token::operator_equal:
		case Token::operator_notEqual:
		case Token::operator_lessThan:
		case Token::operator_greaterThan:
		case Token::operator_lessThanEqual:
		case Token::operator_greaterThanEqual:
			next();
			result = ExprPtr(new BinaryExpression(
				to_operation(token, binary),
				result, parse_shift()
			));
			continue;
		//...
		}
		return result;
	}
}

Expression* Parser::parse_shift() {
	ExprPtr result = parse_additive();
	while (true) {
		TokenType token = get().get_type();
		switch (token) {
		case Token::operator_binary_leftShift:
		case Token::operator_binary_rightShift:
			next();
			result = ExprPtr(new BinaryExpression(
				to_operation(token, binary),
				result, parse_additive()
			));
			continue;
		}
		return result;
	}
}

ExprPtr Parser::parse_additive() {
	ExprPtr result = parse_multiplicative();
	while (true) {
		TokenType token = get().get_type();
		switch (token) {
		case Token::operator_plus:
		case Token::operator_minus:
			next();
			result = ExprPtr(new BinaryExpression(
				to_operation(token, binary),
				result, parse_multiplicative()
			));
			continue;
		}
		return result;
	}
}

ExprPtr Parser::parse_multiplicative() {
	ExprPtr result = parse_unary();
	while (true) {
		TokenType token = get().get_type();
		switch (token) {
		case Token::operator_star:
		case Token::operator_slash:
		case Token::operator_procent:
			next();
			result = ExprPtr(new BinaryExpression(
				to_operation(token, binary),
				result, parse_unary()
			));
			continue;
		}
		return result;
	}
}

ExprPtr Parser::parse_unary() {
	TokenType token = get().get_type();
	if (getGroup(token) == Token::operator_) {
		Operation operation = to_operation(token, unary_prefix);
		if (operation != Operation::none) {
			next();
			return ExprPtr(new UnaryExpression(operation, parse_argumented_expressions()));
		}
	}
	ExprPtr expr = parse_argumented_expressions();
	token = get().get_type();
	if (getGroup(token) == (Token::operator_)) {
		Operation operation = to_operation(token, unary_postfix);
		if (operation != Operation::none) {
			next();
			return ExprPtr(new UnaryExpression(operation, expr));
		}
	}
	return expr;
}


ExprPtr Parser::parse_argumented_expressions() {
	ExprPtr result = parse_dot();
	while (getGroup(get().get_type()) == Token::brackets) {
		Operation operation = to_operation(get().get_type(), argumented);
		if (operation == Operation::none) break;
		TokenType closer = TokenType(get().get_type() + 1);
		next();
		std::vector<Expression*> args;
		if (get().get_type() != closer)
			while (true) {
				args.push_back(parse_expression());
				if (get().get_type() == closer) break;
				consume(Token::operator_comma);
			}
		next();
		result = new ArgumentedExpression(operation, result, args);
	}
	return result;
}

ExprPtr Parser::parse_dot() {
	ExprPtr result = parse_primary();
	while (get().get_type() == Token::operator_dot) {
		next();
		if (get().get_type() != Token::variable)
			throw;
		result = new BinaryExpression(Operation::dot, result, parse_variable());
	}
	return result;
}

ExprPtr Parser::parse_primary() {
	Token& token = get();
	switch (token.get_type()) {
	case Token::integer:
		next();
		return ExprPtr(new IntegerExpression(_wtoi64(token.get_value().c_str())));
	case Token::keyword_true:
		next();
		return ExprPtr(new BooleanExpression(true));
	case Token::keyword_false:
		next();
		return ExprPtr(new BooleanExpression(false));
	case Token::float_:
		next();
		return ExprPtr(new FloatExpression(std::stof(token.get_value())));
	case Token::string:
		next();
		return ExprPtr(new StringExpression(token.get_value()));
	case Token::variable:
		return parse_variable();
	case Token::leftParenthesis: {
		next();
		ExprPtr expr = parse_expression();
		consume(Token::rightParenthesis);
		return expr;
	}
	}
	throw;
}

// ExprPtr Parser::parse_variable() {
// 	ExprPtr result = _parse_variable();
// 	while (true) {
// 		switch (get().get_type()) {
// 		case Token::operator_dot:
// 			next();
// 			result = static_cast<ExprPtr>(new BinaryExpression(
// 				Operation::dot,
// 				result, _parse_variable()
// 			));
// 			continue;
// 		case Token::leftSquareBracket:
// 			next();
// 			result = static_cast<ExprPtr>(new ArgumentedExpression(
// 				Operation::subscript,
// 				result,	{parse_expression()}
// 			));
// 			consume(Token::rightSquareBracket);
// 			continue;
// 		default:
// 			return result;
// 		}
// 	}
// }

ExprPtr Parser::parse_variable() {
	std::list<std::wstring> path;
	path.push_back(get().get_value());
	next();
	while (match(Token::colon)) {
		if (get(1).get_type() == Token::colon && get(2).get_type() == Token::variable) {
			next();
			next();
			path.push_back(get().get_value());
			next();
			continue;
		}
		break;
	}
	std::wstring variable = path.back();
	path.pop_back();
	return static_cast<ExprPtr>(new VariableGetterExpression(
		variable,
		std::vector<std::wstring>(std::move_iterator(path.begin()), std::move_iterator(path.end()))
	));
}

bool Parser::match(Token::Type type) {
	if (this_token->get_type() != type) return false;
	return true;
}
Token& Parser::get(size_t pos) {
	return tokens.at(this->pos + pos);
}

Token& Parser::get() {
	return *this_token;
}

void Parser::consume(TokenType expected) {
	if (!match(expected))
		throw;
	next();
}

Token& Parser::next() {
	if (++pos >= tokens.size()) throw;
	this_token = &tokens[pos];
	return *this_token;
}
