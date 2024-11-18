#pragma once
#include <vector>
#include "token.hpp"
#include "Expression.hpp"

class Parser {
private:
	using TokenType = typename Token::Type;

	std::vector<Token>& tokens;
	Token* this_token;
	size_t pos;
public:
	Parser(std::vector<Token>& tokens);

	[[nodiscard]] std::vector<unique_ptr<Expression>> parse();
private:
	[[nodiscard]] Expression* expression();
	[[nodiscard]] Expression* multiplicative();
	[[nodiscard]] Expression* additive();
	[[nodiscard]] Expression* unary();
	[[nodiscard]] Expression* primary();
private:
	[[nodiscard]] bool match(TokenType type);
	[[nodiscard]] Token& get(size_t pos);
	[[nodiscard]] Token& get();
	Token& next();
};