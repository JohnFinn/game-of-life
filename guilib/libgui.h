#pragma once

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include "Window.h"

void error_callback(int error, const char* description) {
    std::cerr << "GLFW Error: " << description << '\n';
}
