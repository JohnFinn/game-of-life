#include "glcall.h"
#include <algorithm>

glErrors::iterator::iterator(int){
    error = GL_NO_ERROR;
}

glErrors::iterator::iterator(){
    error = glGetError();
}

glErrors::iterator& glErrors::iterator::operator++(){
    error = glGetError();
}

glErrors::iterator glErrors::iterator::operator++(int){
    iterator copy(*this);
    operator++();
    return copy;
}

GLenum glErrors::iterator::operator*() {
    return error;
}

bool glErrors::iterator::operator==(const iterator& other) {
    return error == other.error;
}

bool glErrors::iterator::operator!=(const iterator& other) {
    return error != other.error;
}

glErrors::iterator glErrors::begin() {
    return glErrors::iterator();
}

glErrors::iterator glErrors::end() {
    return glErrors::iterator(0);
}


namespace gl {
    std::vector<GLenum> getErrors() {
        glErrors errors;
        std::vector<GLenum> result(errors.begin(), errors.end());
        return result;
    }

    std::string getErrorMessage(GLenum errcode) {
        std::map<GLenum, std::string> values;
        values[GL_NO_ERROR] =                       "GL_NO_ERROR                        No error has been recorded. The value of this symbolic constant is guaranteed to be 0.";
        values[GL_INVALID_ENUM] =                   "GL_INVALID_ENUM	                An unacceptable value is specified for an enumerated argument. The offending command is ignored and has no other side effect than to set the error flag.";
        values[GL_INVALID_VALUE] =                  "GL_INVALID_VALUE	                A numeric argument is out of range. The offending command is ignored and has no other side effect than to set the error flag.";
        values[GL_INVALID_OPERATION] =              "GL_INVALID_OPERATION	            The specified operation is not allowed in the current state. The offending command is ignored and has no other side effect than to set the error flag.";
        values[GL_INVALID_FRAMEBUFFER_OPERATION] =  "GL_INVALID_FRAMEBUFFER_OPERATION	The framebuffer object is not complete. The offending command is ignored and has no other side effect than to set the error flag.";
        values[GL_OUT_OF_MEMORY] =                  "GL_OUT_OF_MEMORY	                There is not enough memory left to execute the command. The state of the GL is undefined, except for the state of the error flags, after this error is recorded.";
        values[GL_STACK_UNDERFLOW] =                "GL_STACK_UNDERFLOW	                An attempt has been made to perform an operation that would cause an internal stack to underflow.";
        values[GL_STACK_OVERFLOW] =                 "GL_STACK_OVERFLOW	                An attempt has been made to perform an operation that would cause an internal stack to overflow.";

        return values[errcode];
    }
}
