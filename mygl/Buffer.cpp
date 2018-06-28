#include "Buffer.h"
#include "glcall.h"

namespace gl {
    Buffer::Buffer() {
        GLCALL(glGenBuffers(1, &id);)
    }

    Buffer::~Buffer() {
        GLCALL(glDeleteBuffers(1, &id);)
    }

    void Buffer::bind(GLenum target) {
        GLCALL(glBindBuffer(target, id);)
    }

    void Buffer::copy(GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage) {
        bind(target);
        GLCALL(glBufferData(target, size, data, usage);)
        GLCALL(glBindBuffer(target, 0);)
    }
} // namespace gl
