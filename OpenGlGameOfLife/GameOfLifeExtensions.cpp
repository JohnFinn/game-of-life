#include "GameOfLifeExtensions.h"

void GameOfLifeExtensions::glider(unsigned int x, unsigned int y) { // TODO implement flight direction
    if (x == 0 or x + 1 >= width or y == 0 or y + 1 >= height)
        throw std::logic_error("impossible to create glider here");
    cell(x, y) = 1;
    cell(x+1,y) = 1;
    cell(x+2,y) = 1;
    cell(x+2,y+1) = 1;
    cell(x+1,y+2) = 1;
}

void GameOfLifeExtensions::randomize() {
    for (unsigned int y = 0; y < height; ++y)
        for (unsigned int x = 0; x < width; ++x)
            cell(x, y) = static_cast<uint8_t>(rand() % 2);
}

void GameOfLifeExtensions::diagonals() {
    for (unsigned int y = 0; y < height; ++y)
        for (unsigned int x = 0; x < width; ++x)
            cell(x, y) = static_cast<uint8_t>(x % 2 xor y % 2);
}

void GameOfLifeExtensions::bars() {
    for (unsigned int y = 0; y < height; ++y)
        for (unsigned int x = 0; x < width; ++x)
            cell(x, y) = static_cast<uint8_t>(x % 2 or y % 2);
}
