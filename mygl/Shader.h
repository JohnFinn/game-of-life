#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "glcall.h"

namespace gl {
    class Shader {
        friend class Program;

        GLuint id;
    public:
        Shader(GLenum type, const std::string_view);

        Shader(Shader&& other) noexcept;

        Shader& operator=(Shader&& other) noexcept;

        explicit Shader(GLenum type);

        ~Shader();

        void setSource(const std::string_view);

        void compile();

        GLint get_iv(GLenum pname) const;

        std::string getInfoLog() const;
    };
} //namespace gl


