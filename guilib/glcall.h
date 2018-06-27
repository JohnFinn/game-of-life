#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <sstream>
#include <map>

std::vector<GLenum> getErrors();

std::string getErrorMessage(GLenum errcode);


#define GLCALL(expr) getErrors(); expr;\
    {std::vector<GLenum> errors = getErrors();\
    if (!errors.empty()){\
        std::stringstream ss;\
        ss << "[OpenGL error] " << __FILE__ << ':' << __LINE__ <<'\n' << __FUNCTION__ << '\n';\
        for (auto i : errors)\
            ss << getErrorMessage(i) << "\n";\
        throw std::runtime_error(ss.str());\
    }}
