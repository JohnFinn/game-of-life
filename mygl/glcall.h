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
struct std::iterator_traits<glErrors::iterator> {
    typedef ptrdiff_t difference_type;
    typedef std::input_iterator_tag iterator_category;
};

namespace gl {
    std::vector<GLenum> getErrors();

    std::string getErrorMessage(GLenum errcode);

    void handleErrors(std::string location);
}

#define S(x) #x
#define S_(x) S(x)
#define S__LINE__ S_(__LINE__)
#define LOCATION std::string(__PRETTY_FUNCTION__) + " " __FILE__ ":" S__LINE__

#define GLCALL(expr) gl::handleErrors(""); expr; gl::handleErrors(LOCATION);
//#define GLCALL(expr) expr;
