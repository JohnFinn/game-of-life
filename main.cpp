#include "OpenGlGameOfLife/Game.h"


int main(){
    Game g(100, 80, 10);
    std::cout << glGetString(GL_VERSION) << "\n";
    g.glider(10, 50);
    g.glider(10, 40);
    g.glider(20, 50);
    g.glider(20, 40);
    g.randomize();
    g.play();

    return 0;
}
