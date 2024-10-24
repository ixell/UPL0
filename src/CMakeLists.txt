cmake_minimum_required (VERSION 3.13)

project (src)

set(lexer lexer/lexer.cpp lexer/lexer.hpp)
set(token lexer/token.cpp lexer/token.hpp)

add_executable (
    upl
        upl.cpp
        ${lexer}
        ${token}
)

set_property(TARGET upl PROPERTY CXX_STANDARD 20)
