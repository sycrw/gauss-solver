cmake_minimum_required(VERSION 3.31)
project(gauss_solver)

set(CMAKE_CXX_STANDARD 20)

add_executable(gauss_solver src/main.cpp src/userInput.cpp
        src/gauss.cpp
        include/gauss.hpp
)
