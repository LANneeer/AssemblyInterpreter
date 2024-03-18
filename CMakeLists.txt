cmake_minimum_required(VERSION 3.23)
project(Assembly)

set(CMAKE_CXX_STANDARD 17)

add_executable(Assembly main.cpp Interpreter.cpp)
