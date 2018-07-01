#include "Window.h"

#include <stdexcept>

namespace gl {

    std::map<GLFWwindow*, Window*> Window::windows;


    void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods){
        Window::windows[window]->keyfunc(window, key, scancode, action, mods);
    }


    Window::Window(unsigned int w, unsigned int h, char *title, GLFWmonitor *monitor, GLFWwindow *share) :
            window(glfwCreateWindow(w, h, title, monitor, share)) {
        if (not window)
            throw std::runtime_error("Window or context creation failed");
        windows[window] = this;
        SetKeyCallback(keyCallback);
    }


    Window::Window(unsigned int w, unsigned int h, char *title) : Window(w, h, title, nullptr, nullptr) {}


    Window::~Window() {
        windows.erase(window);
        glfwDestroyWindow(window);
    }


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


    GLFWkeyfun Window::SetKeyCallback(GLFWkeyfun cbfun) {
        return glfwSetKeyCallback(window, cbfun);
    }


    void Window::SetKeyCallback(Window::keyfunc_t func) {
        keyfunc = std::move(func);
    }


} // namespace gl