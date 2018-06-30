#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <utility>

namespace gl {
    class Window {
        GLFWwindow *window = nullptr;
    public:
        Window(int w, int h, char *title, GLFWmonitor *monitor, GLFWwindow *share);

        Window(int w, int h, char *title);

        ~Window();

        void use() const;

        int should_close() const;

        void swap_buffers();

        void get_size(int& height, int& width) const noexcept;

        std::pair<int, int> get_size() const noexcept; // width, height

        void set_point_size(GLfloat size);
    };
}