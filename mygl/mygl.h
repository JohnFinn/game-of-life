#pragma once

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Window.h"
#include "Buffer.h"
#include "Program.h"
#include "VertexArray.h"

namespace gl {
    void error_callback(int error, const char *description);

    class Library {
    public:
        Library();
        ~Library();
    };
} // namespace gl
