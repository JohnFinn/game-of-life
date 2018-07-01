#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <utility>
#include <functional>
#include <map>

namespace gl {

    class Window {
        friend void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

        GLFWwindow *window = nullptr;

        typedef std::function<void(GLFWwindow *, int, int, int, int)> keyfunc_t;

        static std::map<GLFWwindow*, Window*> windows;

        keyfunc_t keyfunc;

    public:
        Window(unsigned int w, unsigned int h, char *title, GLFWmonitor *monitor, GLFWwindow *share);

        Window(unsigned int w, unsigned int h, char *title);

        ~Window();

        void use() const;

        int should_close() const;

        void swap_buffers();

        void get_size(int& height, int& width) const noexcept;

        std::pair<int, int> get_size() const noexcept; // width, height

        void set_point_size(GLfloat size);

        GLFWkeyfun SetKeyCallback(GLFWkeyfun cbfun);

        void SetKeyCallback(keyfunc_t func);
    };
}