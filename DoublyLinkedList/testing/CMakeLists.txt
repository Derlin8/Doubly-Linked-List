cmake_minimum_required(VERSION 3.13)
project(TestDoubleLinkedList)

set(CMAKE_CXX_STANDARD 14)

find_package(Threads REQUIRED)
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG master
)

FetchContent_GetProperties(googletest)
if (NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
endif ()
add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})

add_executable(DoubleLinkedListTester main.cpp DoubleLinkedListTest.cpp DoubleLinkedListTest.h)


target_link_libraries(DoubleLinkedListTester
        PRIVATE
        DoubleLinkedList
        gtest
        gmock
        )
target_compile_options(DoubleLinkedListTester PRIVATE -Wall -Werror -Wextra)
