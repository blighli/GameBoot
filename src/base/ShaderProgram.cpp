//
// Created by bligh on 2023/11/28.
//

#include <iostream>
#include "ShaderProgram.h"

const char* readFile(const char* fileName);
GLuint compileShader(GLenum shaderType, const char *shaderText);

ShaderProgram::ShaderProgram() {
    program = glCreateProgram();

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

void ShaderProgram::loadShaderFromText(const char *vsText, const char *fsText) const {
    GLuint vs = compileShader(GL_VERTEX_SHADER, vsText);
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, fsText);
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
}

void ShaderProgram::loadShaderFromFile(const char *vsFile, const char *fsFile) const {
    const char* vsText = readFile(vsFile);
    const char* fsText = readFile(fsFile);
    loadShaderFromText(vsText, fsText);
}

GLuint compileShader(GLenum shaderType, const char* shaderText) {
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderText, NULL);
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

const char* readFile(const char *fileName) {
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