#include <list>
#include "Parser.hpp"
#include "all_expressions.hpp"
#include "all_statements.hpp"

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
	switch (get().get_type()) {
	case Token::variable:
	case Token::keyword_type:
		return parse_definition(true);
	default:
		switch (getSubgroup(get().get_type())) {
		case Token::keyword_modificators:
			return parse_definition(true);
		default:
			throw;
		}
	}
}

Statement* Parser::parse_definition(bool is_global) {
	TypeStatement* type = static_cast<TypeStatement*>(parse_type());
	if (!match(Token::variable))
		throw;
	std::wstring name = get().get_value();
	next();
	switch (get().get_type()) {
	case Token::leftParenthesis: {
		if (!is_global)
			throw;
		std::vector<Statement*> args = parse_args();
		BlockStatement* code;
		if (match(Token::colon))
			code = parse_code();
		else if (match(Token::endline) || match(Token::endcommand))
			code = nullptr;
		else
			throw;
		return static_cast<Statement*>(new FunctionStatement(type, name, args, code));
	}
	case Token::operator_assign: {
		next();
		std::vector<ExprPtr> arg{ parse_expression() };
		consume(Token::endline);
		return static_cast<Statement*>(new InitStatement(new VariableStatement(type, name), arg));
	}
	case Token::endcommand:
	case Token::endline: {
		next();
		std::vector<ExprPtr> arg{ nullptr };
		return static_cast<Statement*>(new InitStatement(new VariableStatement(type, name), arg));
	}
	default:
		throw;
	}
}

std::vector<Statement*> Parser::parse_args() {
	TokenType opener = get().get_type();
	TokenType closer = TokenType(opener + 1);
	next();
	std::vector<Statement*> args;
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
	if (match(Token::endcommand) || match(Token::endline))
		return nullptr;
	consume(Token::colon);
	if (!match(Token::endline)) {
		while (true) {
			code.push_back(parse_statement());
			if (match(Token::endline))
				break;
			if (!match(Token::endcommand))
				throw;
		}
		return new BlockStatement(code);
	}
	next();
	consume(Token::tab);
	while (!match(Token::untab)) {
		Statement* statement = this->parse_statement();
		if (statement != nullptr)
			code.push_back(statement);
		if (!match(Token::endcommand) && !match(Token::endline))
			throw;
		next();
	}
	next();
	return new BlockStatement(code);
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
	case Token::endcommand:
		next();
		[[fallthrough]];
	case Token::endline:
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
	BlockStatement* else_code = nullptr;
	if (match(Token::keyword_else)) {
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
	Expression* initializer = parse_expression();
	consume(Token::endcommand);
	Expression* condition = parse_expression();
	consume(Token::endcommand);
	Expression* changer = parse_expression();
	consume(Token::rightParenthesis);
	BlockStatement* code = parse_code();
	return static_cast<Statement*>(new ForStatement(initializer, condition, changer, code));
}


ExprPtr Parser::parse_expression() {
	return parse_logical();
}

ExprPtr Parser::parse_logical() {
	ExprPtr result = parse_additive();
	#ifdef DEBUG
		for (int COUNT = 0; COUNT != 10'000; ++COUNT)
	#else
		while (true)
	#endif
	{
		TokenType token = get().get_type();
		switch (token) {
		case Token::operator_equal:
			next();
			result = ExprPtr(new BinaryExpression(
				to_operation(token, binary),
				result, parse_additive()
			));
			continue;
		case Token::operator_lessThan:
		case Token::operator_greaterThan:
		case Token::operator_lessThanEqual:
		case Token::operator_greaterThanEqual:
			//...
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
	#ifdef DEBUG
		for (int COUNT = 0; COUNT != 10'000; ++COUNT)
	#else
		while (true)
	#endif
	{
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
	#ifdef DEBUG
		for (int COUNT = 0; COUNT != 10'000; ++COUNT)
	#else
		while (true)
	#endif
	{
		TokenType token = get().get_type();
		switch (token) {
		case Token::operator_star:
		case Token::operator_slash:
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
	if (getGroup(token) == (Token::operator_)) {
		Operation operation = to_operation(token, unary_prefix);
		if (operation != Operation::none) {
			next();
			return ExprPtr(new UnaryExpression(operation, parse_primary()));
		}
	}
	ExprPtr expr = parse_primary();
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
	case Token::variable: {
		next();
		std::list<std::wstring> path;
		path.push_back(token.get_value());
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
		return ExprPtr(new VariableGetterExpression(
			variable,
			std::vector<std::wstring>(std::move_iterator(path.begin()), std::move_iterator(path.end()))
		));
	}
	case Token::leftParenthesis: {
		next();
		ExprPtr expr = parse_expression();
		consume(Token::rightParenthesis);
		return expr;
	}
	}
	throw;
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
