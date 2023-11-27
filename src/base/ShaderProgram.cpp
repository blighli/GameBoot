//
// Created by bligh on 2023/11/28.
//

#include "ShaderProgram.h"
#include <iostream>

static const char* vertex_shader_text =
        "#version 330 core\n"
        "in vec2 vPos;\n"
        "in vec3 vCol;\n"
        "out vec3 color;\n"
        "uniform mat4 MVP;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
        "    color = vCol;\n"
        "}\n";
static const char* fragment_shader_text =
        "#version 330 core\n"
        "in vec3 color;\n"
        "out vec4 frag_color;\n"
        "void main()\n"
        "{\n"
        "    frag_color = vec4(color, 1.0);\n"
        "}\n";

const char* loadSource(const char* fileName);
GLuint loadShader(GLenum shaderType, const char *fileName);

ShaderProgram::ShaderProgram(const char* vsFile, const char* fsFile) {
    program = glCreateProgram();
    GLuint vs = loadShader(GL_VERTEX_SHADER, vsFile);
    GLuint fs = loadShader(GL_FRAGMENT_SHADER, fsFile);
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
}

ShaderProgram::~ShaderProgram() {
    glUseProgram(0);
    glDeleteProgram(program);
}

void ShaderProgram::useProgram() const {
    glUseProgram(program);
}

GLuint ShaderProgram::getProgram() const {
    return program;
}

const char* loadSource(const char *fileName) {
    FILE* file =  fopen(fileName, "rb");
    if (!file)
    {
        std::cerr<<"Load shader source " << fileName << " failed!"<<std::endl;
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    int len = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* source = new char[len+1];
    fread(source, 1, len, file);
    fclose(file);

    source[len] = 0;

    return const_cast<const char*>(source);
}

GLuint loadShader(GLenum shaderType, const char *fileName) {
    const char* source = NULL;
    if(fileName != NULL){
        source = loadSource(fileName);
    }
    else if(shaderType == GL_VERTEX_SHADER) {
        source = vertex_shader_text;
    }
    else if(shaderType == GL_FRAGMENT_SHADER) {
        source = fragment_shader_text;
    }

    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    GLint success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success){
        const unsigned int INFO_LOG_SIZE = 512;
        GLchar infoLog[INFO_LOG_SIZE];
        glGetShaderInfoLog(shader, INFO_LOG_SIZE, NULL, infoLog);
        std::cerr<<"ERROR::SHADER::COMPILATION_FAILED: " << infoLog << std::endl;
    }
    return shader;
}