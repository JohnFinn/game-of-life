#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace gl {
    class Window {
        GLFWwindow *window = nullptr;
    public:
        Window(int w, int h, char *title, GLFWmonitor *monitor, GLFWwindow *share);

        Window(int w, int h, char *title);

        ~Window();

        void use();

        int should_close();

        void swap_buffers();
    };
}