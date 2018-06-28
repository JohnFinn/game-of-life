#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdexcept>
#include <vector>

#include "Buffer.h"

namespace gl {

    struct BufferElement{
        GLint count;
        GLenum type;
        GLboolean normalized;
    };

    size_t size(GLenum type);

    class VertexArray {
        GLuint id;
        Buffer buffer;

    public:
        VertexArray();

        void bind() const;

        void set_layout(GLenum target, std::vector<BufferElement> layout);

        void copy(GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage);
    };
} // namespace gl
