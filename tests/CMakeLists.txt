cmake_minimum_required (VERSION 3.13)

project (tests)

add_executable (
    tests
        pch.hpp
        Lexer/Lexer_tests.cpp
)

target_include_directories (
	tests
	PRIVATE
		Lexer
        .
)

set_target_properties (
    tests
    PROPERTIES
        CXX_STANDARD 20
)
