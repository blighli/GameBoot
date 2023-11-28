//
// Created by bligh on 2023/11/27.
//

#include <glad/gl.h>
#include "base/ShaderProgram.h"
#include "MyGameApp.h"


void MyGameApp::loadShaders() {
    GameApp::loadShaders();
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
    mShaderProgram->loadShaderFromText(vertex_shader_text, fragment_shader_text);
}

void MyGameApp::drawScene() {
    //Render Here
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void MyGameApp::onSize(int width, int height) {
    GameApp::onSize(width, height);
}

void MyGameApp::onKey(int key, int action) {
    GameApp::onKey(key, action);
}

void MyGameApp::onMouseMove(int x, int y) {

}

void MyGameApp::onMouseButton(int button, int action) {

}


