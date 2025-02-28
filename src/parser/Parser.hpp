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
	[[nodiscard]] Statement* parse_global();
	[[nodiscard]] Statement* parse_definition(bool is_global = false);
	[[nodiscard]] Statement* parse_function();
	[[nodiscard]] BlockStatement* parse_code();
	[[nodiscard]] Statement* parse_statement();
	[[nodiscard]] Statement* parse_if_statement();
	[[nodiscard]] Statement* parse_switch_statement();
	[[nodiscard]] Statement* parse_while_statement();
	[[nodiscard]] Statement* parse_for_statement();
	[[nodiscard]] std::vector<Statement*> parse_args();
	[[nodiscard]] Statement* parse_type();
	[[nodiscard]] Expression* parse_expression();
	//[[nodiscard]] Expression* parse_comma();
	[[nodiscard]] Expression* parse_assignation();
	[[nodiscard]] Expression* parse_logical_or();
	[[nodiscard]] Expression* parse_logical_and();
	[[nodiscard]] Expression* parse_binary_or();
	[[nodiscard]] Expression* parse_binary_xor();
	[[nodiscard]] Expression* parse_binary_and();
	[[nodiscard]] Expression* parse_comparison();
	[[nodiscard]] Expression* parse_shift();
	[[nodiscard]] Expression* parse_logical();
	[[nodiscard]] Expression* parse_multiplicative();
	[[nodiscard]] Expression* parse_additive();
	[[nodiscard]] Expression* parse_unary();
	[[nodiscard]] Expression* parse_primary();
	[[nodiscard]] Expression* parse_variable();
	[[nodiscard]] Expression* _parse_variable();
private:
	[[nodiscard]] bool match(TokenType type);
	[[nodiscard]] Token& get(size_t pos);
	[[nodiscard]] Token& get();
	void consume(TokenType expected);
	Token& next();
};