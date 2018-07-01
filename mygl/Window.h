#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <utility>
#include <functional>
#include <map>

namespace gl {

    class Window {
    private:


        typedef std::function<void(int, int, int, int)> keyfunc_t;
        typedef std::function<void(int, int, int)> mouse_button_func_t;

        GLFWwindow *window = nullptr;

        static std::map<GLFWwindow*, Window*> windows;

    public:

        keyfunc_t keyfunc;

        mouse_button_func_t mouse_button_func;

        static Window* get(GLFWwindow* window);

        Window(unsigned int w, unsigned int h, char *title, GLFWmonitor *monitor, GLFWwindow *share);

        Window(unsigned int w, unsigned int h, char *title);

        ~Window();

        void use() const;

        int should_close() const;

        void swap_buffers();

        void get_size(int& height, int& width) const noexcept;

        std::pair<int, int> get_size() const noexcept; // width, height

        void set_point_size(GLfloat size);

        GLFWkeyfun SetKeyCallback(GLFWkeyfun callback);

        void SetKeyCallback(keyfunc_t callback);

        GLFWmousebuttonfun SetMouseButtonCallback(GLFWmousebuttonfun callback);

        void SetMouseButtonCallback(mouse_button_func_t callback);

        void get_cursor_pos(double &xpos, double &ypos) const;

        std::pair<double, double> get_cursor_pos() const;

        std::pair<double, double> get_relative_cursor_pos() const; // 0, 0 is center, -1,-1 left lower corner, etc.
    };
}