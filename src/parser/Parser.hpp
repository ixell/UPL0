#pragma once
#include <vector>
#include "token.hpp"
#include "Expression.hpp"

class Parser {
private:
	std::vector<Token>& tokens;
	Token* this_token;
	size_t pos;
public:
	Parser(std::vector<Token>& tokens);

	[[nodiscard]] std::vector<ptr_t<Expression>> parse();
private:
	[[nodiscard]] ptr_t<Expression> expression();
	[[nodiscard]] ptr_t<Expression> multiplicative();
	[[nodiscard]] ptr_t<Expression> additive();
	[[nodiscard]] ptr_t<Expression> unary();
	[[nodiscard]] ptr_t<Expression> primary();
private:
	[[nodiscard]] bool match(TokenType type);
	[[nodiscard]] Token& get(size_t pos);
	[[nodiscard]] Token& get();
	Token& next();
};