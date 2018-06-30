#pragma once

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Window.h"
#include "Buffer.h"
#include "Program.h"
#include "VertexArray.h"

namespace gl {

    void error_callback(int error, const char *description) {
        throw std::runtime_error(std::to_string(error) + std::string(" [GLFW Error] ") + description);
    }


    class Library{
    public:
        Library(){
            if (!glfwInit())
                error_callback(0, "Failed to initialize library");
//            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwSetErrorCallback(gl::error_callback);
        }

        ~Library(){
            glfwTerminate();
            glfwSetErrorCallback(nullptr);
        }
    };


} // namespace gl