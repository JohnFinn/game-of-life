#include "GameOfLife.h"
#include "mygl/mygl.h"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <unitypes.h>


class MyGameOfLife : public GameOfLife {
public:
    using GameOfLife::GameOfLife;

    void glider(unsigned int x, unsigned int y){ // TODO implement flight direction
        if (x == 0 or x + 1 >= width or y == 0 or y + 1 >= height)
            throw std::logic_error("impossible to create glider here");
        cell(x, y) = 1;
        cell(x+1,y) = 1;
        cell(x+2,y) = 1;
        cell(x+2,y+1) = 1;
        cell(x+1,y+2) = 1;
    }


    void randomize(){
        for (unsigned int y = 0; y < height; ++y)
            for (unsigned int x = 0; x < width; ++x)
                cell(x, y) = static_cast<uint8_t>(std::rand() % 2);
    }


    void diagonals() {
        for (unsigned int y = 0; y < height; ++y)
            for (unsigned int x = 0; x < width; ++x)
                cell(x, y) = static_cast<uint8_t>(x % 2 xor y % 2);
    }


    void bars() {
        for (unsigned int y = 0; y < height; ++y)
            for (unsigned int x = 0; x < width; ++x)
                cell(x, y) = static_cast<uint8_t>(x % 2 or y % 2);
    }

};


template <unsigned int wcount = 80, unsigned int hcount = 60>
class Game{
public:
    // order is important !
    gl::Library lib;        // has to be first (calls glwfinit in constructor and glfwterminate in destructor)
    gl::Window window;      // calls glewinit and also I need to be able to call window.use() before constructing vao and program
    MyGameOfLife game;      // use comma operator to call window.use()
    gl::VertexArray vao;    // needs opengl context which window.use() does
    gl::Program program;    // same as vao

    GLfloat vertices[hcount][wcount][3];

    unsigned int cell_size = 1;


    Game() : Game(10) {}


    explicit Game(unsigned int cell_size) :
            cell_size(cell_size),
            window(cell_size * wcount, cell_size * hcount, "Game of life"),
            game(wcount, (window.use(), hcount)),
            program(gl::Program::fromFiles("../shaders/vertex.glsl", "../shaders/fragment.glsl"))
    {

        // cells should be displayed as squares
        // here we calculate height and width in interval -1, 1 in order not to allow overlapping
        GLfloat relative_x_cell_size = 2.0f/wcount,
                relative_y_cell_size = 2.0f/hcount;

        // position of the first cell
        GLfloat x_start = relative_x_cell_size/2 - 1,
                y_start = relative_y_cell_size/2 - 1;

        // initial values of vertices
        for (unsigned int y = 0; y < hcount; ++y) {
            for (unsigned int x = 0; x < wcount; ++x) {
                vertices[y][x][0] = x_start + x * relative_x_cell_size;
                vertices[y][x][1] = y_start + y * relative_y_cell_size;
                vertices[y][x][2] = static_cast <float> (game.cell(x, y));
            }
        }
        vao.set_layout(GL_ARRAY_BUFFER, {{3, GL_FLOAT, GL_FALSE}});
        program.use();
        window.set_point_size(cell_size);
    }


    void copy_cells(){
        for (unsigned int y = 0; y < hcount; ++y)
            for (unsigned int x = 0; x < wcount; ++x)
                vertices[y][x][2] = static_cast <float> (game.cell(x, y));
    }


    void copy_vao(){
        vao.copy(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);
    }


    void draw(){
        vao.draw(GL_POINTS, 0, hcount * wcount);
        window.swap_buffers();
    }


    void step(){
        game.step();
        copy_cells();
        copy_vao();


        glfwPollEvents(); // TODO incapsulate it in gl::Window
        draw();
    }


    void play(){
        copy_vao();
        draw();
        bool running = false;
        window.SetKeyCallback([&](int key, int scancode, int action, int mods){
//            std::cout << window << ' ' << key << ' ' << scancode << ' ' << action << ' ' << mods << std::endl;
            if (key == GLFW_KEY_SPACE and action == GLFW_PRESS)
                running = not running;
            else if (key == GLFW_KEY_N and action == GLFW_PRESS or action == GLFW_REPEAT)
                step();
        });
        window.SetMouseButtonCallback([&](int button, int action, int mods){
            if (action == GLFW_PRESS) {
                auto&&[x, y] = get_cursor_cell_coords();
                game.cell(x, y) = not game.cell(x, y);
                vertices[y][x][2] = static_cast <GLfloat> (game.cell(x, y));
                copy_vao();
                draw();
                std::cout << button << ' ' << action << ' ' << mods <<  ' ' << x << ' ' << y << std::endl;
            }
        });

        while (not window.should_close()){
            if (running)
                step();
            else
                glfwPollEvents();
//            sleep(1);
        }
    }


    std::pair<unsigned int, unsigned int> get_cursor_cell_coords(){ // coordinates in game
        auto&& [x, y] = window.get_cursor_pos();
        x /= cell_size;
        y = hcount - y / cell_size;
        return {x, y};
    };


    void glider(unsigned int x, unsigned int y){ // TODO implement flight direction
        game.glider(x, y);
        for (unsigned int Y = y; Y <= y+2; ++Y)
            for (unsigned int X = x; X <= x+2; ++X)
                vertices[Y][X][2] = static_cast <float> (game.cell(X, Y));
        copy_vao();
        draw();
    }


    void randomize(){
        game.randomize();
        copy_cells();
        copy_vao();
        draw();
    }


    void diagonals() {
        game.diagonals();
        copy_cells();
        copy_vao();
        draw();
    }


    void bars() {
        game.bars();
        copy_cells();
        copy_vao();
        draw();
    }
};


int main(){
    Game<100, 80> g(10);
    g.glider(10, 50);
    g.glider(10, 40);
    g.glider(20, 50);
    g.glider(20, 40);
    g.play();

    return 0;
}