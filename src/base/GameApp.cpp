//
// Created by bligh on 2023/11/27.
//

#include <iostream>
#include <glad/gl.h>
#include <glfw/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "ShaderProgram.h"
#include "GameApp.h"

//各种回调函数
void error_callback(int error, const char* description);
void size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void cursor_pos_callback(GLFWwindow* window, double x, double y);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void drop_callback(GLFWwindow* window, int count, const char** paths);
void window_close_callback(GLFWwindow* window);

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

GameApp::GameApp(int width, int height, const char *title,bool fullScreen) {
    //初始化OpenGL上下文
    initContext();
    //创建绘制窗口
    createWindow(width, height, title, fullScreen);
    //设置GLAD载入函数
    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0) {
        printf("Failed to initialize OpenGL context\n");
        return;
    }
    //绑定事件处理函数
    bindEvents();
    //创建Shader程序
    mShaderProgram = new ShaderProgram();
}

void GameApp::initContext() {//初始化glfw
    if (glfwInit()){
        //设置OpenGL版本
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    }
    else {
        std::cerr<<"GLFW initialization failed!"<<std::endl;
    }
}

void GameApp::createWindow(int width, int height, const char *title,bool fullScreen) {//创建窗口
    if(fullScreen){
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        if(mode)
        {
            mWindow = glfwCreateWindow(mode->width, mode->height, title, monitor, NULL);
        }
    }
    else{
        mWindow = glfwCreateWindow(width, height, title, NULL, NULL);
    }

    if (mWindow){
        //创建Context
        glfwMakeContextCurrent(mWindow);
    }
    else{
        const char* description;
        glfwGetError(&description);
        std::cout << "Failed to create GLFW window: " << description << std::endl;
        glfwTerminate();
    }
}

void GameApp::bindEvents() const {
    //设置事件回调对象指针
    glfwSetWindowUserPointer(mWindow, (void*)this);
    //设置各种回调函数
    glfwSetErrorCallback(error_callback);
    //键盘按键
    glfwSetKeyCallback(mWindow, key_callback);
    //鼠标按键
    glfwSetMouseButtonCallback(mWindow, mouse_button_callback);
    //鼠标移动
    glfwSetCursorPosCallback(mWindow, cursor_pos_callback);
    //窗口大小改变
    glfwSetFramebufferSizeCallback(mWindow, size_callback);
    //文件拖拽到窗口
    glfwSetDropCallback(mWindow, drop_callback);
    //窗口关闭
    glfwSetWindowCloseCallback(mWindow, window_close_callback);
}

GameApp::~GameApp() {
    glfwDestroyWindow(mWindow);
    glfwTerminate();
}

void GameApp::runLoop() {
    while (!glfwWindowShouldClose(mWindow)) {
        //绘制场景
        drawScene();

        glfwSwapBuffers(mWindow);
        glfwPollEvents();
    }
}
GLFWwindow *GameApp::getWindow() const {
    return mWindow;
}

void GameApp::drawScene() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void GameApp::onSize(int width, int height) {
    std::cout<<"Event: Window width="<<width<<",height="<<height<<std::endl;
    glViewport(0, 0, width, height);
}

void GameApp::onKey(int key, int action) {
    std::cout<<"Event: Key Pressed = "<<key<<std::endl;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(mWindow, GLFW_TRUE);
    }
}

void GameApp::onMouseMove(int x, int y) {

}

void GameApp::onMouseButton(int button, int action) {

}

void GameApp::loadShaders() {

}

void GameApp::loadModels() const {
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

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    auto pGameWindow = (GameApp*)glfwGetWindowUserPointer(window);
    pGameWindow->onKey(key,action);
}

void size_callback(GLFWwindow* window, int width, int height){
    auto pGameWindow = (GameApp*)glfwGetWindowUserPointer(window);
    pGameWindow->onSize(width,height);
}

void cursor_pos_callback(GLFWwindow* window, double x, double y){
    auto pGameWindow = (GameApp*)glfwGetWindowUserPointer(window);
    pGameWindow->onMouseMove((int)x,(int)y);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
    auto pGameWindow = (GameApp*)glfwGetWindowUserPointer(window);
    pGameWindow->onMouseButton(button,action);
}

void drop_callback(GLFWwindow* window, int count, const char** paths)
{
    for (int i = 0;  i < count;  i++) {
        std::cout<<"Status: Filename = "<<paths[i]<<std::endl;
    }
}

void window_close_callback(GLFWwindow* window){
    std::cout<<"Status:Close window"<<std::endl;
    //glfwSetWindowShouldClose(window, GLFW_FALSE);
}

void error_callback(int error, const char* description)
{
    std::cout<<"GLFW Error:"<<description<<std::endl;
}


