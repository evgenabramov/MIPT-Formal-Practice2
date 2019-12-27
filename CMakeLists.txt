cmake_minimum_required(VERSION 3.15)
project(MIPT_Formal_Practice2)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(
        googletest-master
)

add_executable(
        unit_tests
        test.cpp
        tests.cpp
        Grammar.h
        GrammarRule.cpp
        GrammarRule.h
        Grammar.cpp
        Algo.cpp
        Algo.h
        Situation.cpp
        Situation.h
)

add_executable(
        MIPT_Formal_Practice2
        main.cpp
        Grammar.h
        GrammarRule.cpp
        GrammarRule.h
        Grammar.cpp
        Algo.cpp
        Algo.h
        Situation.cpp
        Situation.h
)

target_include_directories(
        unit_tests
        PUBLIC
        gtest
        gtest_main
)

target_link_libraries(
        unit_tests
        PUBLIC
        gtest
        gtest_main
)