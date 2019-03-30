#include "SingleWindow.h"

#include <stdexcept>

namespace gl {
    void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods){
        SingleWindow::getInstance().keyfunc(key, scancode, action, mods);
    }

    void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
        SingleWindow::getInstance().mouse_button_func(button, action, mods);
    }

    void window_size_callback(GLFWwindow* window, int width, int height) {
        SingleWindow::getInstance().size_callback(width, height);
    }

    SingleWindow& SingleWindow::createInstance(unsigned int w, unsigned int h, char *title) {
        static SingleWindow window(w, h, title);
        return window;
    }

    SingleWindow& SingleWindow::getInstance() {
        return createInstance(0, 0, nullptr);
    }

    SingleWindow::SingleWindow(unsigned int w, unsigned int h, char *title, GLFWmonitor *monitor, GLFWwindow *share) :
            window(glfwCreateWindow(w, h, title, monitor, share)) {
        if (not window)
            throw std::runtime_error("Window or context creation failed");
        SetKeyCallback(keyCallback);
        SetMouseButtonCallback(mouse_button_callback);
        glfwSetWindowSizeCallback(window, window_size_callback);
        glfwMakeContextCurrent(window);
        if (GLenum err = glewInit())
            throw std::runtime_error("Failed to initialize GLEW " + std::to_string(err));
    }

    SingleWindow::SingleWindow(unsigned int w, unsigned int h, char *title) : SingleWindow(w, h, title, nullptr, nullptr) {}

    SingleWindow::~SingleWindow() {
        glfwDestroyWindow(window);
    }

    int SingleWindow::should_close() const {
        return glfwWindowShouldClose(window);
    }


    void SingleWindow::swap_buffers() {
        glfwSwapBuffers(window);
    }


    std::pair<int, int> SingleWindow::get_size() const noexcept {
        int width, height;
        get_size(width, height);
        return {width, height};
    }


    void SingleWindow::get_size(int& width, int& height) const noexcept {
        glfwGetWindowSize(window , &width, &height);
    }

    GLFWkeyfun SingleWindow::SetKeyCallback(GLFWkeyfun callback) {
        return glfwSetKeyCallback(window, callback);
    }

    void SingleWindow::SetKeyCallback(SingleWindow::keyfunc_t callback) {
        keyfunc = std::move(callback);
    }

    GLFWmousebuttonfun SingleWindow::SetMouseButtonCallback(GLFWmousebuttonfun callback) {
        return glfwSetMouseButtonCallback(window, callback);
    }

    void SingleWindow::SetMouseButtonCallback(SingleWindow::mouse_button_func_t callback) {
        mouse_button_func = std::move(callback);
    }

    void SingleWindow::SetWindowSizeCallback(SingleWindow::size_func_t callback) {
        size_callback = callback;
    }


    void SingleWindow::get_cursor_pos(double &xpos, double &ypos) const {
        glfwGetCursorPos(window, &xpos, &ypos);
    }

    std::pair<double, double> SingleWindow::get_cursor_pos() const {
        double xpos, ypos;
        get_cursor_pos(xpos, ypos);
        return {xpos, ypos};
    }

    std::pair<double, double> SingleWindow::get_relative_cursor_pos() const {
        int height, width;
        double x, y;
        get_size(width, height);
        get_cursor_pos(x, y);
        // x / width = ? / 2  |==> ? = 2x/width
        return {2*x/width - 1, 1 - 2*y/height};
    }

} // namespace gl