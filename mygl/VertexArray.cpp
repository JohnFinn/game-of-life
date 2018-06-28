#include "VertexArray.h"
#include "glcall.h"

namespace gl{

    VertexArray::VertexArray() {
        GLCALL(glGenVertexArrays(1, &id);)
    }

    void VertexArray::bind() const {
        GLCALL(glBindVertexArray(id);)
    }
} // namespace gl