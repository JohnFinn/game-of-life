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
} // namespace gl
