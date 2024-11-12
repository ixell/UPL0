#include <Lexer.hpp>
#include <sstream>
#include <iostream>

int main() {
#ifdef DEBUG
	std::cout << "DEBUG\n";
#endif
	std::wstring code(L"abc");
	std::wistringstream input(code);
	Lexer lexer;
	lexer.open(&input);
	std::vector<Token> tokens;
	lexer.tokenize(&tokens);
	for (const Token& token : tokens) {
		std::wclog << token.to_string() << L'\n';
	}
}