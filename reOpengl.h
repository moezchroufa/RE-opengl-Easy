#ifndef RE_OPENGL
#define RE_OPENGL
/*list of includes*/

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stb_img.h"

/*func decl */
GLFWwindow *CreateWindow(int w, int h, const char *wname);
GLFWwindow *CreateWindowContext(int w, int h, const char *wname);
void InitGLFW();
void FreeWindow(GLFWwindow *window);
GLuint CreateShader(const char *vertexSource, const char *fragmentSource);
char *ReadFile(const char *path);
GLuint CreateShaderFiles(const char *vertexPath, const char *fragmentPath);
GLuint ReloadShader(GLuint *shader, const char *vertexPath, const char *fragPath);
GLuint CreateVertexArrayObject();
GLuint CreateVertexBufferObject(const void *data, size_t sz);
void SetUniform1i(GLuint program, const char *name, int value);
void SetUniform1f(GLuint program, const char *name, float value);
void SetUniform3f(GLuint program, const char *name, float x, float y, float z);
void SetUniform4f(GLuint program, const char *name, float x, float y, float z, float w);
void SetUniformMat4(GLuint program, const char *name, const float *matrix);
GLuint LoadTexture(const char *path);
bool IsShaderCompiled(GLuint shader, const char *sharderName);
bool IsProgramLinked(GLuint program);
void SetupVertexAttrib(GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer);

/*func impl*/

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

void InitGLFW()
{
    if (!glfwInit())
    {

        fprintf(stderr, "GLFW init failed..\n");
        exit(1);
    }
}

void FreeWindow(GLFWwindow *window)
{
    if (window)
    {
        glfwDestroyWindow(window);
    }

    glfwTerminate();
}

/* you can your GLSL source as a string */
GLuint CreateShader(const char *vertexSource, const char *fragmentSource)
{
    // Compile vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    if (!IsShaderCompiled(vertexShader, "vertex shader"))
    {
        glDeleteShader(vertexShader);

        return 0;
    }

    // Compile fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    if (!IsShaderCompiled(fragmentShader, "fragment shader"))
    {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return 0;
    }

    // Link shaders into program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    if (!IsProgramLinked(shaderProgram))
    {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glDeleteProgram(shaderProgram);
        return 0;
    }

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

/* read the GLSL source code via a file path*/
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
    GLuint shaderProgram = CreateShader(vertexSource, fragmentSource);
    free(vertexSource);
    free(fragmentSource);

    return shaderProgram;
}

GLuint ReloadShader(GLuint *shader, const char *vertexPath, const char *fragPath)
{
    GLuint sh = CreateShaderFiles(vertexPath, fragPath);

    if (sh)
    {
        glDeleteProgram(*shader);
        *shader = sh;
    }

    return *shader;
}

GLuint CreateVertexArrayObject()
{
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    return vao;
}

GLuint CreateVertexBufferObject(const void *data, size_t sz)
{
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sz, data, GL_STATIC_DRAW);

    return vbo;
}

void SetUniform1i(GLuint program, const char *name, int value)
{
    GLint loc = glGetUniformLocation(program, name);
    if (loc != -1)
        glUniform1i(loc, value);
    else
        fprintf(stderr, "Uniform %s not found.\n", name);
}

void SetUniform1f(GLuint program, const char *name, float value)
{
    GLint loc = glGetUniformLocation(program, name);
    if (loc != -1)
        glUniform1f(loc, value);
    else
        fprintf(stderr, "Uniform %s not found.\n", name);
}

void SetUniform3f(GLuint program, const char *name, float x, float y, float z)
{
    GLint loc = glGetUniformLocation(program, name);
    if (loc != -1)
        glUniform3f(loc, x, y, z);
    else
        fprintf(stderr, "Uniform %s not found.\n", name);
}

void SetUniform4f(GLuint program, const char *name, float x, float y, float z, float w)
{
    GLint loc = glGetUniformLocation(program, name);
    if (loc != -1)
        glUniform4f(loc, x, y, z, w);
    else
        fprintf(stderr, "Uniform %s not found.\n", name);
}

void SetUniformMat4(GLuint program, const char *name, const float *matrix)
{
    GLint loc = glGetUniformLocation(program, name);
    if (loc != -1)
        glUniformMatrix4fv(loc, 1, GL_FALSE, matrix);
    else
        fprintf(stderr, "Uniform %s not found.\n", name);
}

GLuint LoadTexture(const char *path, int setting)
{
    int w;
    int h;
    int pipes; // R,G,B or R,G,B,ALPHA

    unsigned char *data = stbi_load(path, &w, &h, &pipes, 0);
    if (!data)
    {
        fprintf(stderr, "Failed to load texture : %s \n", path);
        return 0;
    }
    GLenum format;
    switch (pipes)
    {
    case 1:
        format = GL_RED;
        break;
    case 3:
        format = GL_RGB;
        break;
    case 4:
        format = GL_RGBA;
        break;
    default:
        fprintf(stderr, "unsupported number of pipes : %d", pipes);
        stbi_image_free(data);
        return 0;
    }

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // todo: change setting to enum type will be better and more precise
    switch (setting)
    {
    case 1:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        break;
    default:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    };

    glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
    return texture;
}

bool IsShaderCompiled(GLuint shader, const char *shaderName)
{

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {

        char log[1024];
        glGetShaderInfoLog(shader, sizeof(log), NULL, log);
        fprintf(stderr, "[%s] compilation failed with [%s] \n", shaderName, log);
        return false;
    }

    return true;
}

bool IsProgramLinked(GLuint program)
{

    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        char log[1024];
        glGetProgramInfoLog(program, sizeof(log), NULL, log);
        fprintf(stderr, "Linking failed with [%s] \n", log);
        return false;
    }

    return true;
}
/*  reason : i noticed that i call those multiple times so i decided to make
    them as a function! hope they will be useful
    i.e : SetupVertexAttrib(0,3,GL_FLOAT,3*sizeof(type),(void*)0);
*/
void SetupVertexAttrib(GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer)
{
    glVertexAttribPointer(index, size, type, GL_FALSE, stride, pointer);
    glEnableVertexAttribArray(index);
}

#endif