#include "Shader.h"
namespace gl {
    Shader::Shader(GLenum type, const char *source) : Shader(type) {
        setSource(source);
        compile();
    }

    Shader::Shader(GLenum type) : id(glCreateShader(type)) {}

    Shader::~Shader() {
        GLCALL(glDeleteShader(id);)
    }


    void Shader::setSource(const char *src) {
        GLCALL(glShaderSource(id, 1, &src, nullptr);)
    }

    void Shader::compile() {
        GLCALL(glCompileShader(id);)
        if (get_iv(GL_COMPILE_STATUS) == GL_FALSE)
            throw std::runtime_error("Failed to compile shader " + getInfoLog());
    }

    GLint Shader::get_iv(GLenum pname) const {
        GLint result;
        GLCALL(glGetShaderiv(id, pname, &result);)
        return result;
    }

    std::string Shader::getInfoLog() const {
        int length = get_iv(GL_INFO_LOG_LENGTH);
        std::string result;
        result.resize(length);
        GLCALL(glGetShaderInfoLog(id, length, &length, (char *) result.c_str());)
        return result;
    }

    Shader::Shader(Shader &&other) noexcept : id(other.id) {
        other.id = 0;
    }

    Shader &Shader::operator=(Shader &&other) noexcept {
        id = other.id;
        other.id = 0;
        return *this;
    }

} // namespace gl