//
// Created by bligh on 2023/11/28.
//

#ifndef GAMEBOOT_SHADERPROGRAM_H
#define GAMEBOOT_SHADERPROGRAM_H

#include <glad/gl.h>

class ShaderProgram {
public:
    ShaderProgram(const char* vsFile, const char* fsFile);
    virtual ~ShaderProgram();

    void useProgram() const;
    GLuint getProgram() const;
private:
    GLuint program;
};


#endif //GAMEBOOT_SHADERPROGRAM_H
