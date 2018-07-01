#pragma once

#include <vector>
#include <cstdint>

class GameOfLife{
public:

    std::vector<uint8_t> world, next;
    unsigned int height=0, width=0;

    void step();

    GameOfLife(unsigned int width, unsigned int height);

    uint8_t& cell(unsigned int x, unsigned int y);

    uint8_t& cell_next(unsigned int x, unsigned int y);

    void update_cell(unsigned int x, unsigned int y);

    uint8_t count_around(unsigned int x, unsigned int y);

    void randomize();

    void diagonals();

    void bars();

};