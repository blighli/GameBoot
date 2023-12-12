#version 330 core

layout (location = 0) in vec4 pos;
layout (location = 1) in vec2 coord;

uniform mat4 mvp;

out vec4 vert_color;

void main(){
    gl_Position = mvp * pos;
    vert_color = vec4(coord, 0.0, 0.0);
}
