cmake_minimum_required(VERSION 3.10)
project(gameoflife)

set(CMAKE_CXX_STANDARD 17)

add_library(gameoflife STATIC GameOfLife/GameOfLife.cpp)
add_library(mygl STATIC mygl/SingleWindow.cpp mygl/Buffer.cpp mygl/Shader.cpp mygl/Program.cpp mygl/glcall.cpp mygl/VertexArray.cpp mygl/mygl.cpp)

add_library(OpenGlGameOfLife OpenGlGameOfLife/GameOfLifeExtensions.cpp OpenGlGameOfLife/Game.cpp)
link_libraries(OpenGlGameOfLife gameoflife)

add_executable(game main.cpp)
target_link_libraries(game OpenGlGameOfLife mygl glfw GLEW GL)
