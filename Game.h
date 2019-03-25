#pragma once

#include "GameOfLifeExtensions.h"
#include "Array3D.h"
#include "mygl/mygl.h"
#include "GameOfLife/GameOfLife.h"
#include "Game.h"


class Game {
public:
    size_t width, height;
    // order is important !
    gl::Library lib;        // has to be first (calls glwfinit in constructor and glfwterminate in destructor)
    gl::Window window;      // calls glewinit and also I need to be able to call window.use() before constructing vao and program
    GameOfLifeExtensions game;      // use comma operator to call window.use()
    gl::VertexArray vao;    // needs opengl context which window.use() does
    gl::Program program;    // same as vao

    Array3D<GLfloat> vertices;
    unsigned int cell_size = 1;

    explicit Game(unsigned int width, unsigned int height, unsigned int cell_size);

    void copy_cells();

    void copy_vao();

    void draw_vao();

    void draw();

    void step();

    void play();

    std::pair<unsigned int, unsigned int> get_cursor_cell_coords();;

    void invert_cell(unsigned int x, unsigned int y);

    void glider(unsigned int x, unsigned int y);

    void randomize();

    void diagonals();

    void bars();
};
