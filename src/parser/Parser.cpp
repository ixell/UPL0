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
		statements.push_back(global());
	}
}

Statement* Parser::global() {
	switch (get().get_type()) {
	case Token::variable:
	case Token::keyword_type:
		return define_variable(true);
	default:
		switch (getSubgroup(get().get_type())) {
		case Token::keyword_modificators:
			return define_variable(true);
		default:
			throw;
		}
	}
}

Statement* Parser::define_variable(bool is_global) {
	TypeStatement* type = static_cast<TypeStatement*>(this->type());
	if (get().get_type() != Token::variable)
		throw;
	std::wstring name = get().get_value();
	next();
	switch (get().get_type()) {
	case Token::leftParenthesis: {
		if (!is_global)
			throw;
		std::vector<Statement*> args = this->args();
		BlockStatement* code;
		if (get().get_type() == Token::colon)
			code = this->code();
		else if (get().get_type() == Token::endline)
			code = nullptr;
		else
			throw;
		return static_cast<Statement*>(new FunctionStatement(type, name, args, code));
	}
	case Token::operator_assign: {
		next();
		std::vector<ExprPtr> arg{ expression() };
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

std::vector<Statement*> Parser::args() {
	TokenType opener = get().get_type();
	TokenType closer = TokenType(opener + 1);
	next();
	std::vector<Statement*> args;
	while (true) {
		TypeStatement* type = static_cast<TypeStatement*>(this->type());
		Statement* arg = type;
		if (get().get_type() == Token::variable) {
			arg = static_cast<Statement*>(new VariableStatement(type, get().get_value()));
			next();
			if (get().get_type() == Token::operator_assign) {
				std::vector<Expression*> value = {expression()};
				arg = static_cast<Statement*>(
					new InitStatement(static_cast<VariableStatement*>(arg), value));
				next();
			}
		}
		args.push_back(arg);
		if (get().get_type() != Token::operator_comma) {
			if (get().get_type() == closer) {
				next();
				return args;
			}
			throw;
		}
		next();
	}
}

Statement* Parser::type() {
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
		if (get().get_type() != Token::variable && get().get_type() != Token::keyword_type)
			throw;
		std::wstring type = get().get_value();
		next();
		std::vector<Statement*> template_;
		if (get().get_type() == Token::operator_lessThan)
			template_ = args();
		statement = new TypeStatement(type, modificators, template_);
	}
	while (get().get_type() != Token::variable) {
		std::vector<Modificator> modificators;
		if (get().get_type() == Token::keyword_const) {
			modificators.push_back(Modificator::const_);
			next();
		}
		if (get().get_type() == Token::operator_binary_and) {
			std::vector<Statement*> template_ = {statement};
			statement = new TypeStatement(L"&", modificators, template_);
		}
		else
			throw;
		next();
	}
	return statement;
}

BlockStatement* Parser::code() {
	std::vector<Statement*> code;
	if (get().get_type() == Token::endcommand || get().get_type() == Token::endline)
		return nullptr;
	consume(Token::colon);
	if (get().get_type() != Token::endline) {
		while (true) {
			code.push_back(statement());
			if (get().get_type() == Token::endline)
				break;
			if (get().get_type() != Token::endcommand)
				throw;
		}
		return new BlockStatement(code);
	}
	next();
	consume(Token::tab);
	while (get().get_type() != Token::untab) {
		Statement* statement = this->statement();
		if (statement != nullptr)
			code.push_back(statement);
		if (get().get_type() != Token::endcommand && get().get_type() != Token::endline)
			throw;
		next();
	}
	next();
	return new BlockStatement(code);
}

Statement* Parser::statement() {
	switch (get().get_type()) {
	case Token::variable:
		switch (get(1).get_type()) {
		case Token::variable:
			return define_variable(false);
		default:
			return static_cast<Statement*>(new DoStatement(expression()));
		}
		return nullptr; //...
	case Token::integer:
	case Token::keyword_true:
	case Token::keyword_false:
		return static_cast<Statement*>(new DoStatement(expression()));
	case Token::keyword_type:
		if (get(1).get_type() == Token::leftParenthesis)
			return static_cast<Statement*>(new DoStatement(expression()));
		return define_variable(false);
	case Token::keyword_if:
		next();
		{
			Expression* condition = expression();
			BlockStatement* if_code = code();
			BlockStatement* else_code = nullptr;
			if (get().get_type() == Token::keyword_else) {
				next();
				else_code = code();
			}
			return static_cast<Statement*>(new IfElseStatement(condition, if_code, else_code));
		}
	case Token::keyword_switch:
		next();
		{
			Expression* item = expression();
			if (get().get_type() == Token::endcommand || get().get_type() == Token::endline)
				return static_cast<Statement*>(new SwitchCaseStatement(item, {}, nullptr));
			consume(Token::colon);
			consume(Token::endline);
			consume(Token::tab);
			std::vector<std::pair<Expression*, BlockStatement*>> cases;
			BlockStatement* default_case { nullptr };
			while (get().get_type() != Token::untab) {
				consume(Token::keyword_case);
				//if (get().get_type() == Token::...)
				Expression* item2 = expression();
				BlockStatement* code = this->code();
				cases.push_back(std::pair(item2, code));
			}
			return static_cast<Statement*>(new SwitchCaseStatement(item, cases, default_case));
		}
	case Token::keyword_while:
		next();
		{
			Expression* condition = expression();
			BlockStatement* code = this->code();
			return static_cast<Statement*>(new WhileStatement(condition, code));
		}
	case Token::keyword_do:
		next();
		{
			BlockStatement* code = this->code();
			consume(Token::keyword_while);
			Expression* condition = expression();
			consume(Token::endline);
			return static_cast<Statement*>(new DoWhileStatement(condition, code));
		}
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
			return define_variable(false);
		default:
			throw; // syntax error
		}
	}
}

ExprPtr Parser::expression() {
	return logical();
}

ExprPtr Parser::logical() {
	ExprPtr result = additive();
	#ifdef DEBUG
		for (int COUNT = 0; COUNT != 10'000; ++COUNT) {
	#else
		while (true) {
	#endif
		TokenType token = get().get_type();
		switch (token) {
		case Token::operator_equal:
			next();
			result = ExprPtr(new BinaryExpression(
				to_operation(token, binary),
				result, additive()
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
				result, additive()
			));
			continue;
		}
		return result;
	}
}

ExprPtr Parser::additive() {
	ExprPtr result = multiplicative();
	#ifdef DEBUG
		for (int COUNT = 0; COUNT != 10'000; ++COUNT) {
	#else
		while (true) {
	#endif
		TokenType token = get().get_type();
		switch (token) {
		case Token::operator_plus:
		case Token::operator_minus:
			next();
			result = ExprPtr(new BinaryExpression(
				to_operation(token, binary),
				result, multiplicative()
			));
			continue;
		}
		return result;
	}
}

ExprPtr Parser::multiplicative() {
	ExprPtr result = unary();
	#ifdef DEBUG
		for (int COUNT = 0; COUNT != 10'000; ++COUNT) {
	#else
		while (true) {
	#endif
		TokenType token = get().get_type();
		switch (token) {
		case Token::operator_star:
		case Token::operator_slash:
			next();
			result = ExprPtr(new BinaryExpression(
				to_operation(token, binary),
				result, unary()
			));
			continue;
		}
		return result;
	}
}

ExprPtr Parser::unary() {
	TokenType token = get().get_type();
	if (getGroup(token) == (Token::operator_)) {
		Operation operation = to_operation(token, unary_prefix);
		if (operation != Operation::none) {
			next();
			return ExprPtr(new UnaryExpression(operation, primary()));
		}
	}
	ExprPtr expr = primary();
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

ExprPtr Parser::primary() {
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
		while (get().get_type() == Token::colon) {
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
		ExprPtr expr = expression();
		consume(Token::rightParenthesis);
		return expr;
	}
	}
	throw;
}

bool Parser::match(Token::Type type) {
	if (this_token->get_type() != type) return false;
	++pos;
	return true;
}

Token& Parser::get(size_t pos) {
	return tokens.at(this->pos + pos);
}

Token& Parser::get() {
	return *this_token;
}

void Parser::consume(TokenType expected) {
	if (get().get_type() != expected)
		throw;
	next();
}

Token& Parser::next() {
	if (++pos >= tokens.size()) throw;
	this_token = &tokens[pos];
	return *this_token;
}
