//
// Created by bligh on 2023/11/27.
//

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "base/ShaderProgram.h"
#include "MyGameApp.h"
#include "base/Camera.h"
#include "iostream"
#include "glfw/glfw3.h"
#include "base/Geometry.h"

void MyGameApp::loadShaders() {
    GameApp::loadShaders();
    /*
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
     */
    mShaderProgram->loadShaderFromFile("../media/shader/vertex.glsl","../media/shader/fragment.glsl");
    mShaderProgram->useProgram();
}

void MyGameApp::loadGeometry() const {
    GameApp::loadGeometry();

    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    mGeometry->loadGeomeryFromFile("../media/object/triangle.txt");

//    static const struct
//    {
//        float x, y;
//        float r, g, b;
//    } vertices[3] =
//    {
//        -0.6f, -0.4f, 1.f, 0.f, 0.f,
//        0.6f, -0.4f, 0.f, 1.f, 0.f,
//        0.f,  0.6f, 0.f, 0.f, 1.f
//    };

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER,  sizeof(GLfloat)*mGeometry->getVertexCount()*6, mGeometry->getVertexBuffer(), GL_STATIC_DRAW);

    GLuint index_buffer;
    glGenBuffers(1, &index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,  sizeof(int)*mGeometry->getIndexCount(), mGeometry->getIndexBuffer(), GL_STATIC_DRAW);

    GLint vpos_location, vcol_location;
    GLuint program = mShaderProgram->getProgram();
    vpos_location = glGetAttribLocation(program, "pos");
    vcol_location = glGetAttribLocation(program, "color");
    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE,
                          sizeof(float) * 6, (void*) 0);
    glEnableVertexAttribArray(vcol_location);
    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
                          sizeof(float) * 6, (void*) (sizeof(float) * 3));

    //mCamera->orbit(0.0, -30.0);
    mCamera->setPosition(glm::vec3(0.0, 1.0, 2.0));
}

void MyGameApp::drawScene() {
    GameApp::drawScene();
    //Render Here
    GLuint program = mShaderProgram->getProgram();
    GLint mvp_location = glGetUniformLocation(program, "mvp");
    glm::mat4 Model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 MVP = mCamera->mat4() * Model;
    glUniformMatrix4fv(mvp_location, 1, GL_FALSE, glm::value_ptr(MVP));

    //glDrawArrays(GL_TRIANGLES, 0, mGeometry->getVertexCount());
    glDrawElements(GL_TRIANGLES, mGeometry->getIndexCount(), GL_UNSIGNED_INT, 0);
}

void MyGameApp::onSize(int width, int height) {
    GameApp::onSize(width, height);
}

void MyGameApp::onKey(int key, int action) {
    GameApp::onKey(key, action);
}

void MyGameApp::onMouseMove(int x, int y) {
    GameApp::onMouseMove(x, y);
    static int lastX = x;
    static int lastY = y;

    int deltaX = x - lastX;
    int deltaY = y - lastY;

    lastX = x;
    lastY = y;

    if(glfwGetMouseButton(mWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
        int width, height;
        glfwGetFramebufferSize(mWindow, &width, &height);
        mCamera->orbit( -(float)deltaX/(float)width*180.0f, -(float)deltaY/(float)height*180.0f);
    }
}

void MyGameApp::onMouseButton(int button, int action) {
    GameApp::onMouseButton(button, action);
    setTimer(0.01);
}

void MyGameApp::onTimer() {
    GameApp::onTimer();
    //mCamera->orbit(1.0, 0.0);
}


