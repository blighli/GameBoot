#version 330 core

layout (location = 0) in vec4 pos;
layout (location = 1) in vec4 color;

uniform mat4 mvp;

out vec4 vert_color;

void main(){
    gl_Position = mvp * pos;
    vert_color = color;
}
