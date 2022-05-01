cmake_minimum_required(VERSION 3.20)
project(astcalc LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
    add_compile_options(
            /std:c++latest
            /MT
    )
else()
    add_compile_options (
            -std=c++17
            -Wall -Wextra -Wshadow -pedantic
    )
endif()

add_executable(astcalc
               AstNode.cxx
               AstNodeVisitor.cxx
               CodeGenStack.cxx
               AstTree.cxx
               Logger.cxx
               Parser.cxx
               Token.cxx
               numberCalc.cxx
              )
