#include "Parser.hpp"
#include "all.hpp"

using ExpressionPtr = unique_ptr<Expression>;

Parser::Parser(std::vector<Token>& tokens)
	: tokens(tokens), this_token(0), pos(0) {
	if (!tokens.empty())
		this_token = &tokens[0];
}

std::vector<unique_ptr<Expression>> Parser::parse() {
	std::vector<ExpressionPtr> result;
	if (tokens.empty()) throw -1;
	for (size_t i = 0; !match(Token::eof); ++i) {
		result.push_back(ExpressionPtr(expression()));
	}
	return result;
}

Expression* Parser::expression() {
	return additive();
}
Expression* Parser::additive() {
	Expression* result = multiplicative();
	while (true) {
		TokenType token = get().get_type();
		switch (token) {
		case Token::operator_plus:
		case Token::operator_minus:
			next();
			result = new BinaryExpression(
				to_operation(token, binary),
				std::move(result), std::move(multiplicative())
			);
			continue;
		}
		return result;
	}
}
Expression* Parser::multiplicative() {
	Expression* result = unary();
	while (true) {
		TokenType token = get().get_type();
		switch (token) {
		case Token::operator_star:
		case Token::operator_slash:
			next();
			result = new BinaryExpression(
				to_operation(token, binary),
				std::move(result), std::move(unary())
			);
			continue;
		}
		return result;
	}
}
Expression* Parser::unary() {
	TokenType token = get().get_type();
	if (token & (Token::operator_)) {
		next();
		Operation operation = to_operation(token, unary_prefix);
		return new UnaryExpression(operation, unary());
	}
	Expression* expr = primary();
	if (token & (Token::operator_)) {
		next();
		return new UnaryExpression(to_operation(token, unary_postfix), std::move(expr));
	}
	return expr;
}
Expression* Parser::primary() {
	Token& token = get();
	switch (token.get_type()) {
	case Token::integer:
		next();
		return new NumberExpression(_wtoi64(token.get_value().c_str()));
	case Token::float_:
		next();
		return new NumberExpression(_wtof(token.get_value().c_str()));
	case Token::leftParenthesis: {
		next();
		Expression* expr = expression();
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
