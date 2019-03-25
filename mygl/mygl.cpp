#include "mygl.h"

void gl::error_callback(int error, const char *description) {
    throw std::runtime_error(std::to_string(error) + std::string(" [GLFW Error] ") + description);
}

gl::Library::Library() {
    if (!glfwInit())
        error_callback(0, "Failed to initialize library");
//            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwSetErrorCallback(gl::error_callback);
}

gl::Library::~Library() {
    glfwTerminate();
    glfwSetErrorCallback(nullptr);
}
