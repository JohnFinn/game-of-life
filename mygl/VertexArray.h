#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace gl {

    class VertexArray {
        GLuint id;
    public:
        VertexArray();

        void bind() const;
    };
} // namespace gl
