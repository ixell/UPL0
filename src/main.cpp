#include <fstream>
#include <iostream>
#include "Lexer.hpp"
#include "Parser.hpp"
#include "Interpreter.hpp"

int wmain(const int argc, const wchar_t* argv[]) {
	if (argc <= 1) return 1;
	std::vector<Statement*> ast;
	{
		std::vector<Token> tokens;
		{
			std::wifstream stream(argv[1]);
			if (stream.fail()) return 1;
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
		Interpreter interpreter(std::move(ast));
		interpreter.run();
		for (Statement* statement : ast)
			delete statement;
	}
	return 0;
}