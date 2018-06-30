#include "Window.h"

#include <stdexcept>

namespace gl {

    Window::Window(int w, int h, char *title, GLFWmonitor *monitor, GLFWwindow *share) :
            window(glfwCreateWindow(w, h, title, monitor, share)) {
        if (not window)
            throw std::runtime_error("Window or context creation failed");
    }


    Window::Window(int w, int h, char *title) : Window(w, h, title, nullptr, nullptr) {}


    Window::~Window() { glfwDestroyWindow(window); }


    void Window::use() const {
        glfwMakeContextCurrent(window);
        if (GLenum err = glewInit())
            throw std::runtime_error("Failed to initialize GLEW " + std::to_string(err));
    }


    int Window::should_close() const {
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


    void Window::set_point_size(GLfloat size) {
        use();
        glPointSize(size);
    }
} // namespace gl