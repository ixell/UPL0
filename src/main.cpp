#include <sstream>
#include <iostream>
#include "Lexer.hpp"
#include "Parser.hpp"

int main(int argc, char* argv[]) {
#ifdef DEBUG
	std::cout << "DEBUG\n";
#endif
	std::vector<Token> tokens = {Token(Token::eof)};
	Parser parser{tokens};
}