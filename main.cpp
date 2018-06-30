#include "GameOfLife.h"
#include "mygl/mygl.h"
#include <iostream>
#include <cstring>


int main(){
    if (!glfwInit()) {
        std::cerr << "Failed to initialize library\n";
        return -1;
    }
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwSetErrorCallback(error_callback);

    char title[] = "game of life";
    gl::Window window(1000,600,title);
    window.use();

    if (GLenum err = glewInit()){
        std::cerr << "Failed to initialize GLEW\n" << err;
        return err;
    }



    const auto&& [width, height] = window.get_size();
    glViewport(0, 0, width, height); // TODO find out what is it for

    const int cell_size = 1;

    float relative_x_cell_size = static_cast<float>(cell_size*2) / width;
    float relative_y_cell_size = static_cast<float>(cell_size*2) / height;

    GLfloat vertices[height/cell_size][width/cell_size][3];
    GameOfLife game(static_cast<uint>(width/cell_size), static_cast<uint>(height/cell_size));
    game.randomize();

    for (uint y = 0; y < height / cell_size; ++y) {
        for (uint x = 0; x < width / cell_size; ++x) {
            vertices[y][x][0] = -1.0f + x * relative_x_cell_size + relative_x_cell_size/2;
            vertices[y][x][1] = -1.0f + y * relative_y_cell_size + relative_y_cell_size/2;
            vertices[y][x][2] = static_cast <float> (game.cell(x, y));
        }
    }



    gl::VertexArray verar;
    verar.copy(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);
    verar.set_layout(GL_ARRAY_BUFFER, {{3, GL_FLOAT, GL_FALSE}});

    gl::Program prog = gl::Program::fromFiles("../shaders/vertex.glsl", "../shaders/fragment.glsl");
    prog.use();

    verar.bind();
    glPointSize(cell_size);
    while (not window.should_close()){
        verar.draw(GL_POINTS, 0, height/cell_size * width/cell_size);
        glfwPollEvents();
        window.swap_buffers();
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
        game.step();
        for (uint y = 0; y < height / cell_size; ++y)
            for (uint x = 0; x < width / cell_size; ++x)
                vertices[y][x][2] = static_cast <float> (game.cell(x, y));
        verar.copy(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);
    }



    glfwTerminate();
    return 0;
}