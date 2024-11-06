cmake_minimum_required (VERSION 3.13)

project (src)

add_library (
	token
	STATIC
		token/token.hpp
		token/token.cpp
)

target_include_directories (token INTERFACE token)

add_library (
	lexer
	STATIC
		lexer/lexer.hpp
		lexer/lexer.cpp
)

target_include_directories (lexer INTERFACE lexer)

target_link_libraries (
	lexer
	PUBLIC
		token
)

add_executable (
	upl
		main.cpp
)

target_link_libraries (
	upl
	PRIVATE
		lexer
)

set_target_properties(
	token
	lexer
	upl
	PROPERTIES
		CXX_STANDARD 20
)
