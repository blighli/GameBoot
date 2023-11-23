#include <iostream>
#include <glad/gl.h>
#include <glfw/glfw3.h>
#include <stb/stb_image.h>

void handle_input(GLFWwindow* window);
void handle_resize(GLFWwindow* window, int width, int height);

int main() {
    int SCR_WIDTH = 800;
    int SCR_HEIGHT = 600;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL Game Engine", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, handle_resize);

    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0) {
        printf("Failed to initialize OpenGL context\n");
        return -1;
    }

    while (!glfwWindowShouldClose(window))
    {
        handle_input(window);

        glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //Render Here

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    std::cout << "OpenGL Game Engine" << std::endl;

    glfwTerminate();
    return 0;
}

void handle_input(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void handle_resize(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}