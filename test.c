#include "reOpengl.h"
#include <unistd.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_img.h"
const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos, 1.0);\n"
                                 "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(2.5, 0.5, 1.2, 1.0);\n"
                                   "}\0";

int main()
{

    InitGLFW();

    GLFWwindow *window = CreateWindowContext(800, 600, "Triangle");
    if (!window)
        return -1;

    GLuint shader = CreateShader(vertexShaderSource, fragmentShaderSource);

    float vertices[] = {
        0.0f, 0.5f, 0.0f,   // top
        -0.5f, -0.5f, 0.0f, // bottom left
        0.5f, -0.5f, 0.0f   // bottom right
    };

    GLuint vao = CreateVertexArrayObject();
    GLuint vbo = CreateVertexBufferObject(vertices, sizeof(vertices));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glUseProgram(shader);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    FreeWindow(window);
    return 0;
}