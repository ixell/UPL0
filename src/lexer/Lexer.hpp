#pragma once
#include <fstream>
#include <vector>
#include <istream>
#include "token.hpp"

using std::wstring, std::operator""s;

class Lexer {
private:
	std::vector<Token>* tokens{ nullptr };
	std::wistream* code;
	std::wstring buffer;
	wchar_t ch{ 0 };
	
	int tabs = 0, tab_size = 0;
public:
	Lexer();
	explicit Lexer(std::wistream* code);
    ~Lexer();

    void open(std::wistream* code);

public:
	void tokenize(std::vector<Token>* tokens);

private:
	void tokenize_word();
	void tokenize_number();
	void tokenize_operator();
	void tokenize_parentheses();
	void tokenize_string();
	void tokenize_other();
	void tokenize_comment();
	void tokenize_tabs();

	void typify_word(Token& token);

	void next();
	[[nodiscard]] wchar_t get();
	void add(const Token& token);
	void add(TokenType typtokene);
	void add(TokenType token, const std::wstring& value);
};
