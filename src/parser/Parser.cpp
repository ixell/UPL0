#include "Parser.hpp"
#include "all.hpp"

using ExprPtr = ptr_t<Expression>;

Parser::Parser(std::vector<Token>& tokens)
	: tokens(tokens), this_token(0), pos(0) {
	if (!tokens.empty())
		this_token = &tokens[0];
}

void Parser::parse(std::vector<ExprPtr>& expressions) {
	if (tokens.empty()) throw;
	for (size_t i = 0; get().get_type() != Token::eof; ++i) {
		expressions.push_back(ExprPtr(expression()));
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
