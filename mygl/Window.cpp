#include "Window.h"

#include <stdexcept>

namespace gl {

    std::map<GLFWwindow*, Window*> Window::windows;


    void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods){
        Window::get(window)->keyfunc(key, scancode, action, mods);
    }


    void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
        Window::get(window)->mouse_button_func(button, action, mods);
    }


    Window::Window(unsigned int w, unsigned int h, char *title, GLFWmonitor *monitor, GLFWwindow *share) :
            window(glfwCreateWindow(w, h, title, monitor, share)) {
        if (not window)
            throw std::runtime_error("Window or context creation failed");
        windows[window] = this;
        SetKeyCallback(keyCallback);
        SetMouseButtonCallback(mouse_button_callback);
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


    GLFWkeyfun Window::SetKeyCallback(GLFWkeyfun callback) {
        return glfwSetKeyCallback(window, callback);
    }


    void Window::SetKeyCallback(Window::keyfunc_t callback) {
        keyfunc = std::move(callback);
    }


    Window *Window::get(GLFWwindow *window) {
        return Window::windows[window];
    }


    GLFWmousebuttonfun Window::SetMouseButtonCallback(GLFWmousebuttonfun callback) {
        return glfwSetMouseButtonCallback(window, callback);
    }


    void Window::SetMouseButtonCallback(Window::mouse_button_func_t callback) {
        mouse_button_func = std::move(callback);
    }


    void Window::get_cursor_pos(double &xpos, double &ypos) const {
        glfwGetCursorPos(window, &xpos, &ypos);
    }


    std::pair<double, double> Window::get_cursor_pos() const {
        double xpos, ypos;
        get_cursor_pos(xpos, ypos);
        return {xpos, ypos};
    }

    std::pair<double, double> Window::get_relative_cursor_pos() const {
        int height, width;
        double x, y;
        get_size(width, height);
        get_cursor_pos(x, y);
        // x / width = ? / 2  |==> ? = 2x/width
        return {2*x/width - 1, 1 - 2*y/height};
    }

} // namespace gl