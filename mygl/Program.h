#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include "glcall.h"
#include "Shader.h"


namespace gl {

    class Program {
        GLuint id;
    public:
        static Program fromString(const std::string_view vert, const std::string_view frag);

        static Program fromFiles(const std::string_view vertFname, const std::string_view fragFname);

        Program(Shader &&vs, Shader &&fs);

        Program(Program&& other) noexcept ;

        Program& operator=(Program&& other) noexcept;

        ~Program();

        void use() const;

        void attach(Shader &shader);

        void link();

        void validate() const;

        GLint get_iv(GLenum pname);
    };

} // namespace gl
