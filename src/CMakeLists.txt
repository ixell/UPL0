cmake_minimum_required (VERSION 3.13)

project (src)

add_library (
	token
	STATIC
		token/token.hpp
		token/token.cpp
)

target_include_directories (token PUBLIC token)

target_compile_definitions (
	token
	PUBLIC
		$IF:<$<CONFIG:Debug>,DEBUG,NDEBUG>
)

add_library (
	lexer
	STATIC
		lexer/lexer.hpp
		lexer/lexer.cpp
)

target_include_directories (lexer PUBLIC lexer)

target_link_libraries (
	lexer
	PUBLIC
		token
)

add_subdirectory (ast)

target_link_libraries (
	expressions
	PRIVATE
		token
)

add_library (
	parser
	STATIC
		parser/parser.hpp
		parser/parser.cpp
)

target_include_directories (parser PUBLIC parser)

target_link_libraries (
	parser
	PRIVATE
		token
	PUBLIC
		expressions
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

set_target_properties (
	token
	lexer
	expressions
	parser
	upl
	PROPERTIES
		CXX_STANDARD 20
)
