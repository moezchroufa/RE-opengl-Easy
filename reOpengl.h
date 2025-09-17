

#ifndef RE_OPENGL
#define RE_OPENGL
// includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

// functions

GLFWwindow *CreateWindow(int w, int h, const char *wname)
{
    GLFWwindow *window = glfwCreateWindow(w, h, wname, NULL, NULL);
    if (!window)
    {
        fprintf(stderr, "failed to create a window ...\n");
        glfwTerminate();
        return NULL;
    }
    return window;
}

GLFWwindow *CreateWindowContext(int w, int h, const char *wname)
{
    GLFWwindow *window = glfwCreateWindow(w, h, wname, NULL, NULL);
    if (!window)
    {
        fprintf(stderr, "failed to create a window ...\n");
        glfwTerminate();
        return NULL;
    }
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        fprintf(stderr, "Failed to initialize GLEW: %s\n", glewGetErrorString(err));
        glfwDestroyWindow(window);
        glfwTerminate();
        return NULL;
    }
    return window;
}

void FreeWindow(GLFWwindow *window)
{
    if (window)
    {
        glfwDestroyWindow(window);
    }

    glfwTerminate();
}

// params : needs GLSL source code
GLuint CreateShader(const char *vertexSource, const char *fragmentSource)
{
    // Compile vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    // Compile fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    // Link shaders into program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // free shaders after linking
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

// reading files

char *ReadFile(const char *path)
{
    FILE *file = fopen(path, "rb");

    if (!file)
    {
        fprintf(stderr, "failed to open current file %s \n", path);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long len = ftell(file);
    rewind(file);

    char *buffer = (char *)malloc(len + 1); // include null terminator

    if (!buffer)
    {
        fprintf(stderr, "alloca failed");
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, len, file);
    buffer[len] = '\0';
    fclose(file);

    return buffer;
}

// read from files : CreateShader(f1,f2);

GLuint CreateShaderFiles(const char *vertexPath, const char *fragmentPath)
{
    char *vertexSource = ReadFile(vertexPath);
    if (!vertexSource)
    {
        fprintf(stderr, "Vertex shader file read error.\n");
        return 0;
    }

    char *fragmentSource = ReadFile(fragmentPath);
    if (!fragmentSource)
    {
        fprintf(stderr, "Fragment shader file read error.\n");
        free(vertexSource);
        return 0;
    }

    GLuint program = CreateShader(vertexSource, fragmentSource);

    free(vertexSource);
    free(fragmentSource);

    return program;
}

#endif