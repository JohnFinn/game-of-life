#include "GameOfLife.h"
#include "mygl/mygl.h"
#include <iostream>


int main(){
    if (!glfwInit()) {
        std::cerr << "Failed to initialize library\n";
        return -1;
    }
    glfwSetErrorCallback(error_callback);

    gl::Window window(800,600,"game of life");
    window.use();

    if (GLenum err = glewInit()){
        std::cerr << "Failed to initialize GLEW\n" << err;
        return err;
    }

    gl::Buffer buff;
    gl::Program prog = gl::Program::fromFiles("../shaders/vertex.glsl", "../shaders/fragment.glsl");

    while (not window.should_close()){
        glfwPollEvents();
        window.swap_buffers();
    }



    glfwTerminate();
    return 0;
}