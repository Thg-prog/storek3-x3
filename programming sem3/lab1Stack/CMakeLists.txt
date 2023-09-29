cmake_minimum_required(VERSION 3.24)
project(lab1Stack)

set(CMAKE_CXX_STANDARD 17)

find_package(benchmark REQUIRED)
# библиотеки Google Test и Google Mock
find_package(GTest REQUIRED)


add_executable(lab1Stack main.cpp Stack.h StackExceptions.h)

target_link_libraries(lab1Stack benchmark::benchmark)
target_link_libraries(lab1Stack GTest::GTest GTest::Main)