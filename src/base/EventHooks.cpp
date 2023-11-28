//
// Created by bligh on 2023/11/28.
//

#include <iostream>
#include <glfw/glfw3.h>
#include "GameApp.h"
#include "EventHooks.h"

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