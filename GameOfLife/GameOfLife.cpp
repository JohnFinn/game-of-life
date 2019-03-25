#include <cstdlib>
#include "GameOfLife.h"


void GameOfLife::step(){
    for (unsigned int y = 0; y < height; ++y)
        for (unsigned int x = 0; x < width; ++x)
            update_cell(x, y);
    std::swap(world, next);
}

GameOfLife::GameOfLife(unsigned int width, unsigned int height)
        : height(height), width(width), world(height * width), next(height * width)
{}



uint8_t& GameOfLife::cell(unsigned int x, unsigned int y){
    return world.at(x+y*width);
}


uint8_t& GameOfLife::cell_next(unsigned int x, unsigned int y){
    return next.at(x + y * width);
}


void GameOfLife::update_cell(unsigned int x, unsigned int y){
    uint8_t count = count_around(x, y);
    bool alive = cell(x, y);
    cell_next(x, y) = static_cast<uint8_t>((not alive and count == 3) or (alive and (count == 3 or count == 4)));
}


uint8_t GameOfLife::count_around(unsigned int x, unsigned int y){
    unsigned int X1 = (x ? x - 1 : 0),
            Y1 = (y ? y - 1 : 0),
            X2 = (x + 1 < width ? x + 1 : width-1),
            Y2 = (y + 1 < height ? y + 1 : height-1);

    uint8_t result = 0;

    for (uint X = X1; X <= X2; ++X)
        for (uint Y = Y1; Y <= Y2; ++Y)
            result += cell(X, Y);
    return result;
}
