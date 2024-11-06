#include <Lexer.hpp>
#include <sstream>
#include <iostream>

int main() {
    std::wstring code(L"- + / ==");
    std::wistringstream input(code);
	Lexer lexer;
    lexer.open(&input);
    std::vector<Token> tokens;
    lexer.tokenize(&tokens);
    for (const Token& token : tokens) {
        std::wclog << token.to_string() << L'\n';
    }
}