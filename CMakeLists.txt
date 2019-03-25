cmake_minimum_required(VERSION 3.10)
project(gameoflife)

set(CMAKE_CXX_STANDARD 17)

add_library(gameoflife STATIC GameOfLife/GameOfLife.cpp GameOfLifeExtensions.cpp Game.cpp)
add_library(mygl STATIC mygl/Window.cpp mygl/Buffer.cpp mygl/Shader.cpp mygl/Shader.h mygl/Program.cpp mygl/Program.h mygl/glcall.cpp mygl/VertexArray.cpp mygl/VertexArray.h mygl/mygl.cpp)
add_executable(game main.cpp GameOfLife/GameOfLife.h mygl/Window.h mygl/mygl.h mygl/Buffer.h GameOfLifeExtensions.h Game.h)

target_link_libraries(game gameoflife mygl glfw GLEW GL)
