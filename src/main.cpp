#include <fstream>
#include <iostream>
#include "Lexer.hpp"
#include "Parser.hpp"
#include "Interpreter.hpp"

int main(int argc, char* argv[]) {
#ifdef DEBUG
	std::cout << "DEBUG\n";
#endif
	std::vector<Statement*> ast;
	{
		std::vector<Token> tokens;
		{
			std::ifstream stream {argv[1]};
			Lexer lexer { stream };
			tokens = lexer.tokenize();
		}
		{
			Parser parser {tokens};
			ast = parser.parse();
		}
	}
	{
		Interpreter interpreter {ast};
		interpreter.run();
	}
}