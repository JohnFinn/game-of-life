#include "Game.h"

Game::Game(size_t width, size_t height, size_t cell_size) :
        width(width),
        height(height),
        vertices(width, height, 3),
        cell_size(cell_size),
        window(gl::SingleWindow::createInstance(cell_size * width, cell_size * height, "Game of life")),
        game(width, height),
        program(gl::Program::fromFiles("../shaders/vertex.glsl", "../shaders/fragment.glsl"))
{

    // cells should be displayed as squares
    // here we calculate height and width in interval -1, 1 in order not to allow overlapping
    GLfloat relative_x_cell_size = 2.0f/width,
            relative_y_cell_size = 2.0f/height;

    // position of the first cell
    GLfloat x_start = relative_x_cell_size/2 - 1,
            y_start = relative_y_cell_size/2 - 1;
    // initial values of vertices
    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            vertices.set(y, x, 0, x_start + x * relative_x_cell_size);
            vertices.set(y, x, 1, y_start + y * relative_y_cell_size);
            vertices.set(y, x, 2, static_cast <float> (game.cell(x, y)));
        }
    }
    vao.set_layout(GL_ARRAY_BUFFER, {{3, GL_FLOAT, GL_FALSE}});
    program.use();
    glPointSize(cell_size);
    window.SetWindowSizeCallback([](int width, int height) {
        std::cout << "window resized to " << width << "x" << height << std::endl;
    });
    window.SetMouseButtonCallback([&](int button, int action, int mods){
        auto&&[x, y] = get_cursor_cell_coords();
        if (button == GLFW_MOUSE_BUTTON_1 and action == GLFW_PRESS) {
            invert_cell(x, y);
        } else if (button == GLFW_MOUSE_BUTTON_2 and action == GLFW_PRESS){
            bool caught = false;
            try {
                glider(x, y);
            } catch (std::logic_error& err){
                caught = true;
            }
            if (not caught) {
                draw_vao();
            }
        }
    });
}

void Game::draw_vao() {
    vao.copy(GL_ARRAY_BUFFER, vertices.len() * sizeof(GLfloat), vertices.data(), GL_STREAM_DRAW);
    vao.draw(GL_POINTS, 0, height * width);
    window.swap_buffers();
}

void Game::draw() {
    for (unsigned int y = 0; y < height; ++y)
        for (unsigned int x = 0; x < width; ++x)
            vertices.set(y, x, 2, static_cast <float> (game.cell(x, y)));
    draw_vao();
}

void Game::step() {
    game.step();
    draw();
    glfwPollEvents();
}

void Game::play() {
    draw_vao();
    bool running = false;
    window.SetKeyCallback([&](int key, int scancode, int action, int mods){
//            std::cout << window << ' ' << key << ' ' << scancode << ' ' << action << ' ' << mods << std::endl;
        if (key == GLFW_KEY_SPACE and action == GLFW_PRESS)
            running = not running;
        else if (key == GLFW_KEY_N and action == GLFW_PRESS or action == GLFW_REPEAT)
            step();
    });
    while (not window.should_close()){
        if (running)
            step();
        else
            glfwPollEvents();
    }
}

std::pair<unsigned int, unsigned int> Game::get_cursor_cell_coords() { // coordinates in game
    auto&& [x, y] = window.get_cursor_pos();
    x /= cell_size;
    y = height - y / cell_size;
    return {x, y};
}

void Game::invert_cell(unsigned int x, unsigned int y) {
    vertices.set(y, x, 2, game.cell(x, y) = not game.cell(x, y));
    draw_vao();
}

void Game::glider(unsigned int x, unsigned int y) { // TODO implement flight direction
    game.glider(x, y);
    for (unsigned int Y = y; Y <= y+2; ++Y)
        for (unsigned int X = x; X <= x+2; ++X)
            vertices.set(Y, X, 2, static_cast <float> (game.cell(X, Y)));
    draw_vao();
}

void Game::randomize() {
    game.randomize();
    draw();
}

void Game::diagonals() {
    game.diagonals();
    draw();
}

void Game::bars() {
    game.bars();
    draw();
}
