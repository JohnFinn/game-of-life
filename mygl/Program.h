#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include "glcall.h"
#include "Shader.h"


namespace gl {

    class Program {
        Shader vertexShader, fragmentShader;
        unsigned int id;
    public:
        static Program fromString(const char* vert, const char* frag);

        static Program fromFiles(const std::string &vertFname, const std::string &fragFname);

        Program(Shader &&vs, Shader &&fs);

        ~Program();

        void bind() const;

        void attach(Shader &shader);

        void link();

        void validate() const;
    };

} // namespace gl