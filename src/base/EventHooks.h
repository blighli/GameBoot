//
// Created by bligh on 2023/11/28.
//

#ifndef GAMEBOOT_EVENTHOOKS_H
#define GAMEBOOT_EVENTHOOKS_H

struct GLFWwindow;

//各种回调函数
void error_callback(int error, const char* description);
void size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void cursor_pos_callback(GLFWwindow* window, double x, double y);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void drop_callback(GLFWwindow* window, int count, const char** paths);
void window_close_callback(GLFWwindow* window);

#endif //GAMEBOOT_EVENTHOOKS_H
