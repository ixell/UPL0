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
			std::wifstream stream(argv[1]);
			Lexer lexer(&stream);
			lexer.tokenize(&tokens);
			stream.close();
		}
		{
			Parser parser(tokens);
			parser.parse(ast);
		}
	}
	{
		Interpreter interpreter {ast};
		interpreter.run();
		for (Statement* statement : ast)
			delete statement;
	}
}