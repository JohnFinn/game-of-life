#include "GameOfLife.h"
#include <iostream>

int main(){
    GameOfLife game(20,10);
        for (int x = 0; x < 20; ++x)
            for (int y = 0; y < 10; ++y)
                game.cell_current(x,y) = std::rand()%2;

    for (int i = 0; i <= 10; ++i){
        for (int y = 0; y < 10; ++y) {
            for (int x = 0; x < 20; ++x)
                std::cout << static_cast<bool>(game.cell_current(x,y));
            std::cout << '\n';
        }
        game.step();
        std::cout << '\n';
    }
}