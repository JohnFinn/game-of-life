#include "Window.h"

#include <stdexcept>

namespace gl {
    Window::Window(int w, int h, char *title, GLFWmonitor *monitor, GLFWwindow *share) :
            window(glfwCreateWindow(w, h, title, monitor, share)) {
        if (not window)
            throw std::runtime_error("Window or context creation failed");
    }


    Window::Window(int w, int h, char *title) : Window(w, h, title, NULL, NULL) {}


    Window::~Window() { glfwDestroyWindow(window); }


    void Window::use() {
        glfwMakeContextCurrent(window);
    }


    int Window::should_close() {
        return glfwWindowShouldClose(window);
    }


    void Window::swap_buffers() {
        glfwSwapBuffers(window);
    }


    std::pair<int, int> Window::get_size() const noexcept{
        int width, height;
        get_size(width, height);
        return {width, height};
    }


    void Window::get_size(int& width, int& height) const noexcept {
        glfwGetWindowSize(window , &width, &height);
    }
} // namespace gl