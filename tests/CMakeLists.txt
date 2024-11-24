cmake_minimum_required (VERSION 3.13)

project (tests)

find_package(GTest REQUIRED)
if (GTEST_FOUND)
	enable_testing ()

    add_executable (
        lexer_tests
            pch.hpp
            lexer/Lexer_tests.cpp
    )

    target_include_directories (
        lexer_tests
        PRIVATE
            Lexer
            .
    )

    add_executable (
        parser_tests
            pch.hpp
            Parser/Parser_tests.cpp
    )

    target_include_directories (
        parser_tests
        PRIVATE
            Parser
            .
    )

    set_target_properties (
        lexer_tests
        parser_tests
        PROPERTIES
            CXX_STANDARD 20
    )


    target_link_libraries (
        lexer_tests
        PRIVATE
            ${GTEST_BOTH_LIBRARIES}
            lexer
    )

    add_test (
        NAME "check_lexer"
        COMMAND lexer_tests
    )

    target_link_libraries (
        parser_tests
        PRIVATE
            ${GTEST_BOTH_LIBRARIES}
            parser
            lexer
    )

    add_test (
        NAME "check_parser"
        COMMAND parser_tests
    )
else (GTEST_FOUND)
message (STATUS "GTest not found. Tests will not run.")
endif (GTEST_FOUND)