cmake_minimum_required(VERSION 3.13)

project(interpreter)

add_library(
    interpreter
    STATIC
        Interpreter.cpp
        systemFunctions.cpp
)
