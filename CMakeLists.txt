cmake_minimum_required(VERSION 3.12)

project(cpp_test_project VERSION 0.1 LANGUAGES CXX)


add_executable(cpp_test_project main.cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)