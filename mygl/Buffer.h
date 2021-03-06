#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace gl {

    class Buffer {
        GLuint id = 0;
    public:
        Buffer();

        ~Buffer();

        void bind(GLenum target) const;

        void copy(GLenum target,
                  GLsizeiptr size,
                  const GLvoid * data,
                  GLenum usage);
    };

}