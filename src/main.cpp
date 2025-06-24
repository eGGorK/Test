#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Rendering/ShaderProgram.h"


int g_windowsizeX = 640;
int g_windowsizeY = 480;

GLfloat point[] = {
    0.0f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f
};

GLfloat colors[]{
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f,
};

const char* vertexShader =
"#version 460\n"
"layout(location = 0)in vec3 vertexposition;"
"layout(location = 1)in vec3 vertexcolor;"
"out vec3 color;"
"void main(){"
"   color = vertexcolor;"
"   gl_Position = vec4(vertexposition,1.0);"
"}";

const char* fragmentShader =
"#version 460\n"
"in vec3 color;"
"out vec4 flag_color;"
"void main() {"
" flag_color = vec4(color, 1.0);"
"}";


void glfwWindowSizeCallbak(GLFWwindow *window,int width, int height){

    g_windowsizeX = width;
    g_windowsizeY = height;
    glViewport(0, 0, g_windowsizeX, g_windowsizeY);

}
void glfwKeylCallbak(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);  
    }

}

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
    {   
        std::cout << "glfwInit failed!" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    window = glfwCreateWindow(g_windowsizeX, g_windowsizeY, "BatleCity", NULL, NULL);
    
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(window, glfwWindowSizeCallbak);
    glfwSetKeyCallback(window, glfwKeylCallbak);

    glfwMakeContextCurrent(window);

    if (!gladLoadGL()) {
        std::cout << "Can't load GLAD" << std::endl;
        return -1;
    }

    std::cout << "OpenGl:" << GLVersion.major << "." << GLVersion.minor << std::endl;

    glClearColor(0.1f, 0.2f, 0.3f , 1);
   
    std::string Vertexshader(vertexShader);
    std::string Fragmentshader(fragmentShader);
    Render::ShaderProgram shaderProgram(Vertexshader, Fragmentshader);
    if (!shaderProgram.isComplided()) {
        std::cerr << "Can't create shader program" << std::endl;
    }

    GLuint points_vbo = 0;
    glGenBuffers(1, &points_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);

    GLuint color_vbo = 0;
    glGenBuffers(1, &color_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);


    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);


    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        shaderProgram.use();
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}