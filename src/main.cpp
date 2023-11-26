#include <iostream>
#include <glad/gl.h>
#include <glfw/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

void handle_input(GLFWwindow* window);
void handle_resize(GLFWwindow* window, int width, int height);


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

void setup() {
    int  success;
    char infoLog[512];

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint vertex_buffer, vertex_shader, fragment_shader, program;
    GLint mvp_location, vpos_location, vcol_location;

    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
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

    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::LINK_FAILED\n" << infoLog << std::endl;
    }


    mvp_location = glGetUniformLocation(program, "MVP");
    vpos_location = glGetAttribLocation(program, "vPos");
    vcol_location = glGetAttribLocation(program, "vCol");
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

    glUseProgram(program);
}

int main() {
    int SCR_WIDTH = 800;
    int SCR_HEIGHT = 600;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL Game Engine", NULL, NULL);
    if (window == NULL)
    {
        const char* description;
        int code = glfwGetError(&description);
        std::cout << description<< std::endl;
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

    setup();

    while (!glfwWindowShouldClose(window))
    {
        handle_input(window);

        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //Render Here
        glDrawArrays(GL_TRIANGLES, 0, 3);

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