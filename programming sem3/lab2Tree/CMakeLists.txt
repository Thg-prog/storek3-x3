cmake_minimum_required(VERSION 3.24)
project(lab2Tree)

set(CMAKE_CXX_STANDARD 17)

find_package(benchmark REQUIRED)
find_package(GTest REQUIRED)

add_executable(lab2Tree main.cpp ThreadBST.cpp ThreadBST.h)

target_link_libraries(lab2Tree GTest::GTest GTest::Main)
target_link_libraries(lab2Tree benchmark::benchmark)
