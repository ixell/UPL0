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
	case Token::word:
	case Token::keyword_type:
		return define_variable(true);
	default:
		switch (getSubgroup(get().get_type())) {
		case Token::keyword_modificators:
			return define_variable(true);
		default: throw;
		}
	}
}

Statement* Parser::define_variable(bool is_global) {
	TypeStatement* type = static_cast<TypeStatement*>(this->type());
	std::wstring name;
	if (get().get_type() == Token::word)
		name = get().get_value();
	else throw;
	next();
	switch (get().get_type()) {
	case Token::leftParenthesis: {
		if (is_global) throw;
		std::vector<Statement*> args = this->args();
		BlockStatement* code;
		if (get().get_type() == Token::colon)
			code = this->code();
		else if (get().get_type() == Token::endcommand)
			code = nullptr;
		else throw;
		return static_cast<Statement*>(new FunctionStatement(type, name, args, code));
	}
	case Token::operator_assign: {
		next();
		std::vector<ExprPtr> arg{ expression() };
		Statement* result = static_cast<Statement*>(new InitStatement(new VariableStatement(type, name), arg));
		if (get().get_type() == Token::endcommand)
			return result;
		throw;
	}
	case Token::endcommand: {
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
	while (get().get_type() != closer) {
		TypeStatement* type = static_cast<TypeStatement*>(this->type());
		Statement* arg = type;
		if (get().get_type() == Token::word) {
			arg = static_cast<Statement*>(new VariableStatement(type, get().get_value()));
			next();
			if (get().get_type() == Token::operator_assign) {
				std::vector<Expression*> value = {expression()};
				arg = static_cast<Statement*>(
					new InitStatement(static_cast<VariableStatement*>(arg), value));
				next();
			}
		}
		if (get().get_type() != Token::operator_comma)
			throw;
		args.push_back(arg);
		next();
	}
	next();
	return args;
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
		if (get().get_type() != Token::word || get().get_type() != Token::keyword_type)
			throw;
		std::wstring type = get().get_value();
		std::vector<Statement*> template_;
		if (get().get_type() == Token::operator_lessThan)
			template_ = args();
		statement = new TypeStatement(type, modificators, template_);
	}
	while (get().get_type() != Token::word) {
		std::vector<Modificator> modificators {1};
		if (get().get_type() == Token::keyword_const) {
			modificators.push_back(Modificator::const_);
			next();
		}
		if (get().get_type() == Token::operator_binary_and) {
			std::vector<Statement*> template_ = {statement};
			statement = new TypeStatement(L"&", modificators, template_);
		}
		else throw;
		next();
	}
	return statement;
}

BlockStatement* Parser::code() {
	std::vector<Statement*> code;
	while (get().get_type() != Token::untab) {
		code.push_back(statement());
	}
	return new BlockStatement(code);
}

Statement* Parser::statement() {
	switch (get().get_type()) {
	case Token::word:
		switch (get(1).get_type()) {
		case Token::word:
		case Token::operator_binary_and:
			return define_variable(false);
		default:
			return new DoStatement(expression());
		}
		return nullptr; //...
	case Token::keyword_type:
		if (get(1).get_type() == Token::leftParenthesis)
			return new DoStatement(expression());
		return define_variable(false);
	case Token::keyword_if:
		next();
		return nullptr; //...
	case Token::keyword_else:
		next();
		return nullptr; //...
	case Token::keyword_switch:
		next();
		return nullptr; //...
	case Token::keyword_case:
		next();
		return nullptr; //...
	case Token::keyword_do:
		next();
		return nullptr; //...
	case Token::keyword_enum:
		next();
		return nullptr; //...
	case Token::keyword_while:
		next();
		return nullptr; //...
	default:
		switch (getSubgroup(get().get_type())) {
		case Token::keyword_modificators:
			return define_variable(false);
		}
	}
}

ExprPtr Parser::expression() {
	return additive();
}

ExprPtr Parser::additive() {
	ExprPtr result = multiplicative();
	while (true) {
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
	while (true) {
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
		next();
		Operation operation = to_operation(token, unary_prefix);
		return ExprPtr(new UnaryExpression(operation, unary()));
	}
	ExprPtr expr = primary();
	if (getGroup(token) == (Token::operator_)) {
		next();
		return ExprPtr(new UnaryExpression(to_operation(token, unary_postfix), expr));
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
	case Token::leftParenthesis: {
		next();
		ExprPtr expr = expression();
		if (get().get_type() != Token::rightParenthesis)
			throw;
		next();
		return expr;
	}
	}
	throw -1;
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

Token& Parser::next() {
	if (++pos >= tokens.size()) throw;
	this_token = &tokens[pos];
	return *this_token;
}
