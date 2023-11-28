//
// Created by bligh on 2023/11/27.
//

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
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

void MyGameApp::loadGeometry() const {
    GameApp::loadGeometry();

    static const struct
    {
        float x, y;
        float r, g, b;
    } vertices[3] =
            {
                    { -0.6f, -0.4f, 1.f, 0.f, 0.f },
                    {  0.6f, -0.4f, 0.f, 1.f, 0.f },
                    {   0.f,  0.6f, 0.f, 0.f, 1.f }
            };

    GLuint program = mShaderProgram->getProgram();

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint vertex_buffer;
    GLint mvp_location, vpos_location, vcol_location;

    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    mvp_location = glGetUniformLocation(program, "MVP");
    vpos_location = glGetAttribLocation(program, "vPos");
    vcol_location = glGetAttribLocation(program, "vCol");
    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
                          sizeof(float) * 5, (void*) 0);
    glEnableVertexAttribArray(vcol_location);
    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
                          sizeof(float) * 5, (void*) (sizeof(float) * 2));

    //必须在调用glUniform前执行
    glUseProgram(program);

    glm::mat4 Proj = glm::perspective(glm::radians(45.0f), 4.0f/3.0f, 0.1f, 10.0f);
    glm::mat4 View = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 Model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 MVP = Proj * View * Model;
    glUniformMatrix4fv(mvp_location, 1, GL_FALSE, glm::value_ptr(MVP));
}

void MyGameApp::drawScene() {
    GameApp::drawScene();
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
    GameApp::onMouseMove(x, y);
}

void MyGameApp::onMouseButton(int button, int action) {
    GameApp::onMouseButton(button, action);
}


