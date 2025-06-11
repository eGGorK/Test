#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


int g_windowsizeX = 640;
int g_windowsizeY = 480;

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

    glClearColor(0, 1, 0 , 1);
    
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}