#include "VertexArray.h"
#include "glcall.h"

namespace gl{


    size_t size(GLenum type) {
        switch (type) {
            case GL_UNSIGNED_INT: return sizeof(GLuint);
            case GL_INT:          return sizeof(GLint);
            case GL_FLOAT:        return sizeof(GLfloat);
            case GL_DOUBLE:       return sizeof(GLdouble);
            default:
                throw std::runtime_error("Size not implemented " + std::to_string(type));
        }
    }


    VertexArray::VertexArray() {
        GLCALL(glGenVertexArrays(1, &id);)
    }


    void VertexArray::bind() const {
        GLCALL(glBindVertexArray(id);)
    }


    void VertexArray::set_layout(GLenum target, std::vector<BufferElement> layout) {
        bind();
        buffer.bind(target);
        unsigned int offset = 0;

        unsigned int elem_size = 0;
        for (auto&& [count, type, normalized] : layout)
            elem_size += size(type) * count;


        for (unsigned int index = 0; index < layout.size(); ++index){
            auto&& [count, type, normalized] = layout[index];
            GLCALL(glEnableVertexAttribArray(index);)
            GLCALL(glVertexAttribPointer(index, count, type, normalized, elem_size, (GLvoid*) offset);)
            offset += count * size(type);
        }
        GLCALL(glBindBuffer(target, 0);)
        GLCALL(glBindVertexArray(0);)
    }


    void VertexArray::copy(GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage) {
        bind();
        buffer.copy(target, size, data, usage);
        GLCALL(glBindVertexArray(0);)
    }


    void VertexArray::draw(GLenum mode, GLint first, GLsizei count) const {
        bind();
        GLCALL(glDrawArrays(mode, first, count);)
        GLCALL(glBindVertexArray(0);)
    }


} // namespace gl