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

    GLfloat vertices[] = {
            -0.5f, -0.5f,
            0.5f, -0.5f,
            0.0f,  0.5f,
    };

    gl::VertexArray verar;
    gl::Buffer buff;
    verar.bind();
    buff.copy(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)nullptr);
    glEnableVertexAttribArray(0);

    gl::Program prog = gl::Program::fromFiles("../shaders/vertex.glsl", "../shaders/fragment.glsl");
    prog.bind();

    while (not window.should_close()){
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwPollEvents();
        window.swap_buffers();
    }



    glfwTerminate();
    return 0;
}