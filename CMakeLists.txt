cmake_minimum_required(VERSION 3.10)
project(gameoflife)

set(CMAKE_CXX_STANDARD 17)

add_library(libgameoflife STATIC GameOfLife.cpp)
add_executable(game main.cpp GameOfLife.h main.cpp)
target_link_libraries(game libgameoflife)
