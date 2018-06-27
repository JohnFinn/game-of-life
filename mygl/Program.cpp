#include "Program.h"
#include "Shader.h"

namespace gl {

    Program Program::fromString(const char *vert, const char *frag) {
        return Program(Shader(GL_VERTEX_SHADER, vert), Shader(GL_FRAGMENT_SHADER, frag));
    }

    Program Program::fromFiles(const std::string &vertFname, const std::string &fragFname) {
        std::ifstream t(vertFname);
        std::string vshader((std::istreambuf_iterator<char>(t)),
                            std::istreambuf_iterator<char>());

        t = std::ifstream(fragFname);
        std::string fshader((std::istreambuf_iterator<char>(t)),
                            std::istreambuf_iterator<char>());
        return Program::fromString(vshader.c_str(), fshader.c_str());
    }


    Program::Program(Shader&& vs, Shader &&fs):
    id (glCreateProgram()), vertexShader(std::move(vs)), fragmentShader(std::move(fs)) {
        attach(vertexShader);
        attach(fragmentShader);
        link();
        validate();
    }

    Program::~Program() { GLCALL(glDeleteProgram(id);)}

    void Program::bind() const { GLCALL(glUseProgram(id);)}

    void Program::attach(Shader & shader) { GLCALL(glAttachShader(id, shader.id);)}

    void Program::link() { GLCALL(glLinkProgram(id);)}

    void Program::validate() const  { GLCALL(glValidateProgram(id);)}

} // namespace gl