#include "GameOfLife.h"
#include "mygl/mygl.h"
#include <iostream>
#include <cstring>
#include <unistd.h>

template <unsigned int wcount = 80, unsigned int hcount = 60>
class Game{
public:
    // order is important !
    gl::Library lib;        // has to be first (calls glwfinit in constructor and glfwterminate in destructor)
    gl::Window window;      // calls glewinit and also I need to be able to call window.use() before constructing vao and program
    GameOfLife game;        // use comma operator to call window.use()
    gl::VertexArray vao;    // needs opengl context which window.use() does
    gl::Program program;    // same as vao

    GLfloat vertices[hcount][wcount][3];


    Game() : Game(10) {}


    explicit Game(unsigned int cell_size) :
            window(cell_size * wcount, cell_size * hcount, "Game of life"),
            game(wcount, (window.use(), hcount)),
            program(gl::Program::fromFiles("../shaders/vertex.glsl", "../shaders/fragment.glsl"))
    {

        // glider
//        int x = 10, y = 50;
//        game.cell(x, y) = 1;
//        game.cell(x+1,y) = 1;
//        game.cell(x+2,y) = 1;
//        game.cell(x+2,y+1) = 1;
//        game.cell(x+1,y+2) = 1;
        game.bars();
//        game.randomize();
        GLfloat relative_x_cell_size = 2.0f/wcount,
                relative_y_cell_size = 2.0f/hcount;

        GLfloat x_start = relative_x_cell_size/2 - 1,
                y_start = relative_y_cell_size/2 - 1;

        for (uint y = 0; y < hcount; ++y) {
            for (uint x = 0; x < wcount; ++x) {
                vertices[y][x][0] = x_start + x * relative_x_cell_size;
                vertices[y][x][1] = y_start + y * relative_y_cell_size;
                vertices[y][x][2] = static_cast <float> (game.cell(x, y));
            }
        }
        vao.copy(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);
        vao.set_layout(GL_ARRAY_BUFFER, {{3, GL_FLOAT, GL_FALSE}});
        program.use();
        glPointSize(cell_size); // TODO make window do it
    }

    void play(){
        while (not window.should_close()){
            vao.draw(GL_POINTS, 0, hcount * wcount);
            glfwPollEvents(); // TODO incapsulate it in gl::Window
            window.swap_buffers();
            game.step();
            for (uint y = 0; y < hcount; ++y)
                for (uint x = 0; x < wcount; ++x)
                    vertices[y][x][2] = static_cast <float> (game.cell(x, y));
            vao.copy(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);
            sleep(1);
        }
    }
};


int main(){
    Game<100, 80> g(10);
    g.play();
    return 0;
}