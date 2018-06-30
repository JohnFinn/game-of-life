#version 130

in vec3 position;
out vec4 vertexColor;


void main() {
    gl_Position = vec4(position, 1);
    vertexColor = vec4(0, position.z, 0, 1);
}
