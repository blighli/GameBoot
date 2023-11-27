//
// Created by bligh on 2023/11/27.
//

#include "GameApp.h"
#include <iostream>
#include "glad/gl.h"
#include "glfw/glfw3.h"

static const char* vertex_shader_text =
        "#version 330 core\n"
        "uniform mat4 MVP;\n"
        "in vec3 vCol;\n"
        "in vec2 vPos;\n"
        "out vec3 color;\n"
        "void main()\n"
        "{\n"
        "    gl_Position =   vec4(vPos, 0.0, 1.0);\n"
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

//各种回调函数
void error_callback(int error, const char* description);
void size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void cursor_pos_callback(GLFWwindow* window, double x, double y);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void drop_callback(GLFWwindow* window, int count, const char** paths);
void window_close_callback(GLFWwindow* window);

GameApp::GameApp(bool fullScreen, int width, int height, const char* title) {
    //初始化glfw
    if (!glfwInit())
    {
        std::cerr<<"GLFW initialization failed!"<<std::endl;
        return;
    }
    //设置各种回调函数
    glfwSetErrorCallback(error_callback);
    //设置OpenGL版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    //创建窗口
    if(fullScreen)
    {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        if(mode)
        {
            mWindow = glfwCreateWindow(mode->width, mode->height, title, monitor, NULL);
        }
    }
    else
    {
        mWindow = glfwCreateWindow(width, height, title, NULL, NULL);
    }
    if (!mWindow)
    {
        const char* description;
        glfwGetError(&description);
        std::cout << "Failed to create GLFW window: " << description << std::endl;
        glfwTerminate();
        return;
    }

    //创建Context
    glfwMakeContextCurrent(mWindow);
    //设置GLAD载入函数
    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0) {
        printf("Failed to initialize OpenGL context\n");
        return;
    }

    glfwSetWindowUserPointer(mWindow, (void*)this);

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
    int  success;
    char infoLog[512];
    GLuint vertex_buffer, vertex_shader, fragment_shader;
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    mShaderProgram = glCreateProgram();
    glAttachShader(mShaderProgram, vertex_shader);
    glAttachShader(mShaderProgram, fragment_shader);
    glLinkProgram(mShaderProgram);
    glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(mShaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::LINK_FAILED\n" << infoLog << std::endl;
    }
}

void GameApp::loadModels() {
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint vertex_buffer;
    GLint mvp_location, vpos_location, vcol_location;

    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    mvp_location = glGetUniformLocation(mShaderProgram, "MVP");
    vpos_location = glGetAttribLocation(mShaderProgram, "vPos");
    vcol_location = glGetAttribLocation(mShaderProgram, "vCol");
    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
                          sizeof(float) * 5, (void*) 0);
    glEnableVertexAttribArray(vcol_location);
    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
                          sizeof(float) * 5, (void*) (sizeof(float) * 2));

    //glm::mat4 Proj = glm::perspective(glm::radians(45.0f), 4.0f/3.0f, 0.1f, 10.0f);
    //glm::mat4 View = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    //glm::mat4 Model = glm::mat4(1.0f); //glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    //glm::mat4 MPV = Proj * View * Model;
    //glUniformMatrix4fv(mvp_location, 1, GL_FALSE, glm::value_ptr(MPV));

    glUseProgram(mShaderProgram);
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
