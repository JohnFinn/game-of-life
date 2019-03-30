#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <sstream>
#include <map>


class glErrors {
public:
    class iterator : std::iterator<std::input_iterator_tag, GLenum, ptrdiff_t, GLenum *, GLenum &> {
        GLenum error;
    public:
        explicit iterator(int);                     // for end iterator
        iterator();
        iterator &operator++();
        const iterator operator++(int);
        GLenum operator*();
        bool operator==(const iterator &other);
        bool operator!=(const iterator &other);
    };
    iterator begin();
    iterator end();
};

template<>
struct ::std::iterator_traits<glErrors::iterator> {
    typedef ptrdiff_t difference_type;
    typedef std::input_iterator_tag iterator_category;
};

namespace gl {
    std::vector<GLenum> getErrors();

    std::string getErrorMessage(GLenum errcode);
}


#define GLCALL(expr) getErrors(); expr;\
    {std::vector<GLenum> errors = gl::getErrors();\
    if (!errors.empty()){\
        std::stringstream ss;\
        ss << "[OpenGL error] " << __FILE__ << ':' << __LINE__ <<'\n' << __FUNCTION__ << '\n';\
        for (auto i : errors)\
            ss << gl::getErrorMessage(i) << "\n";\
        throw std::runtime_error(ss.str());\
    }}
