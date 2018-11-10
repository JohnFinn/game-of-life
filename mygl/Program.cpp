#include "Program.h"
#include "Shader.h"

namespace gl {


    Program Program::fromString(const std::string_view vert, const std::string_view frag) {
        return Program(Shader(GL_VERTEX_SHADER, vert), Shader(GL_FRAGMENT_SHADER, frag));
    }

    Program Program::fromFiles(const std::string &vertFname, const std::string &fragFname) {
        std::ifstream t(vertFname);
        std::string vshader((std::istreambuf_iterator<char>(t)),
                            std::istreambuf_iterator<char>());

        t = std::ifstream(fragFname);
        std::string fshader((std::istreambuf_iterator<char>(t)),
                            std::istreambuf_iterator<char>());
        return Program::fromString(vshader, fshader);
    }

    Program Program::fromFiles(std::string&& vertFname, std::string&& fragFname) {
        return fromFiles(vertFname, fragFname);
    }

    Program::Program(Shader&& vs, Shader &&fs):
    id (glCreateProgram()){
        attach(vs);
        attach(fs);
        link();
        if (not get_iv(GL_LINK_STATUS))
            throw std::runtime_error("[OpenGL Error] program linked unsuccessfully");
        validate();
    }


    Program::~Program() {
        GLCALL(glDeleteProgram(id);)
    }


    void Program::use() const {
        GLCALL(glUseProgram(id);)
    }


    void Program::attach(Shader & shader) {
        GLCALL(glAttachShader(id, shader.id);)
    }


    void Program::link() {
        GLCALL(glLinkProgram(id);)
    }


    void Program::validate() const  {
        GLCALL(glValidateProgram(id);)
    }


    Program::Program(Program &&other) noexcept : id(other.id) {
        other.id = 0;
    }


    Program &Program::operator=(Program &&other) noexcept {
        id = other.id;
        other.id = 0;
        return *this;
    }


    GLint Program::get_iv(GLenum pname) {
        GLint result;
        GLCALL(glGetProgramiv(id, pname, &result);)
        return result;
    }

} // namespace gl
