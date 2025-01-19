#pragma once
#include <vector>
#include "token.hpp"
#include "Expression.hpp"
#include "BlockStatement.hpp"
#include "Statement.hpp"

class Parser {
#ifdef TESTING
	friend class ParserGetter;
#endif
private:
	std::vector<Token>& tokens;
	Token* this_token;
	size_t pos;
public:
	Parser(std::vector<Token>& tokens);

	void parse(std::vector<Statement*>& statements);
private:
	[[nodiscard]] Statement* global();
	[[nodiscard]] Statement* define_variable();
	[[nodiscard]] Statement* function();
	[[nodiscard]] BlockStatement* code();
	[[nodiscard]] std::vector<Expression*> args();
	[[nodiscard]] Expression* type();
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