cmake_minimum_required(VERSION 3.10)
project(gameoflife)

set(CMAKE_CXX_STANDARD 17)

add_library(libgameoflife STATIC GameOfLife.cpp)
add_library(libgui STATIC guilib/Window.cpp guilib/glcall.cpp)
add_executable(game main.cpp GameOfLife.h main.cpp guilib/Window.cpp guilib/Window.h guilib/libgui.h)
target_link_libraries(game libgameoflife)
target_link_libraries(game glfw)
target_link_libraries(game GLEW)
target_link_libraries(game libgui)
