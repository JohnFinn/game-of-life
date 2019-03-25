#pragma once

#include <cstring>
#include "mygl/mygl.h"
#include "GameOfLife/GameOfLife.h"
#include "GameOfLifeExtensions.h"

class GameOfLifeExtensions : public GameOfLife {
public:
    GameOfLifeExtensions(unsigned int width, unsigned int height) : GameOfLife(width, height) {}

    void glider(unsigned int x, unsigned int y);

    void randomize();

    void diagonals();

    void bars();
};
