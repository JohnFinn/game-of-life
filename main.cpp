#include "GameOfLife.h"
#include "mygl/mygl.h"
#include <iostream>


int main(){
    if (!glfwInit()) {
        std::cerr << "Failed to initialize library\n";
        return -1;
    }
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwSetErrorCallback(error_callback);

    gl::Window window(800,600,"game of life");
    window.use();

    if (GLenum err = glewInit()){
        std::cerr << "Failed to initialize GLEW\n" << err;
        return err;
    }

    auto&& [width, height] = window.get_size();
    std::cout << height << ' ' << width << '\n';

    GLfloat vertices[] = {
            -1.0f, -1.0f,
            1.0f, -1.0f,
            0.0f,  0.0f,
            0.0f,  1.0f,
    };

    gl::VertexArray verar;
    verar.copy(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    verar.set_layout(GL_ARRAY_BUFFER, {{2, GL_FLOAT, GL_FALSE}});

    gl::Program prog = gl::Program::fromFiles("../shaders/vertex.glsl", "../shaders/fragment.glsl");
    prog.use();

    verar.bind();
    glPointSize(99);
    while (not window.should_close()){
        glDrawArrays(GL_POINTS, 0, 4);
        glfwPollEvents();
        window.swap_buffers();
    }



    glfwTerminate();
    return 0;
}