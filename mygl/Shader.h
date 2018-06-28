#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "glcall.h"

namespace gl {
    class Shader {
        friend class Program;

        unsigned int id;
    public:
        Shader(GLenum type, const char *source);

        Shader(Shader&& other);

        Shader& operator=(Shader&& other);

        explicit Shader(GLenum type);

        ~Shader();

        void setSource(const char *src);

        void compile();

        int get_iv(GLenum pname);

        std::string getInfoLog(int length);
    };
} //namespace gl


