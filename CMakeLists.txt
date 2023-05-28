cmake_minimum_required(VERSION 3.25)
project(monkey_lang_cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

include_directories(.)

add_executable(monkey_lang_cpp
        lexer.cpp
        lexer.h
        main.cpp
        token.cpp
        token.h)
