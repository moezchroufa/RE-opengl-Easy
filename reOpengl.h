#ifndef RE_OPENGL
#define RE_OPENGL
/*list of includes*/

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stb_img.h"
#include "LAmath.h"
/* type decl */

typedef enum
{
    TEXTURE_CLAMP = 0,
    TEXTURE_REPEAT = 1
} TextureSetting;
typedef struct
{
    Mat4f view;
    Mat4f projection;
} CameraS;

typedef struct
{
    CameraS cam;
    Vec3f position;
    Vec3f front;
    Vec3f up;
    float speed;
    float sensitivity;
    float yaw;   // rotation around y axis
    float pitch; // rotation around x axis

    float lastx;
    float lasty;
    int firstMouse;
} CameraControllerS;

typedef struct
{

    GLuint id;
    int w; // width
    int h;
    int pipes; // channels (RGBA)
    TextureSetting setting;
} TextureS;

typedef struct
{
    GLuint vao;
    GLuint vbo;
    GLuint vertexCount;
} MeshS;

typedef struct
{
    GLuint shader;  // shader Program
    GLuint vao;     // how to handle raw data pointers
    GLuint texture; // add some texture if you want
    float mvp[16];  // transformation matrix flat(4x4) contains data to transform object into screen space

} DrawingS;

typedef struct
{
    GLuint FBO;
    GLuint RBO;
    TextureS texture;
    int width;
    int height;
} FrameBufferS;
/* rendering to textures !!!*/
// creation of the framebuffer
FrameBufferS CreateFrameBuffer(int w, int h);
// destroying the framebuffer
void FreeFrameBufferS(FrameBufferS *fb);
// resizing the framebuffer by updating its w,h
void ResizeFrameBufferS(FrameBufferS *fbs, int n_w, int n_h);

/* implementation */

FrameBufferS CreateFrameBuffer(int w, int h)
{
    FrameBufferS fb = {0}; // init or maybe memset() ??
    fb.width = w;
    fb.height = h;

    // create a framebuffer 1/ Gen 2/Bind
    glGenFramebuffers(1, &fb.FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, fb.FBO);

    fb.texture.w = w;
    fb.texture.h = h;

    glGenTextures(1, &fb.texture.id);
    glBindTexture(GL_TEXTURE_2D, fb.texture.id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16, fb.texture.w, fb.texture.h, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fb.texture.id, 0);

    /* depth and stencil*/

    glGenRenderbuffers(1, &fb.RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, fb.RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, w, h);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, fb.RBO);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        fprintf(stderr, "ERROR::FRAMEBUFFER:: Framebuffer is not complete!\n");
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0); // unbind

    return fb;
}

void FreeFrameBufferS(FrameBufferS *fb)
{
    if (!fb)
        return; // fb doesn't exist or not allocated

    glDeleteFramebuffers(1, &fb->FBO);
    glDeleteTextures(1, &fb->texture.id);
    glDeleteRenderbuffers(1, &fb->RBO);
    // maybe ill change it to memset instead of this
    fb->FBO = 0;
    fb->texture.id = 0;
    fb->RBO = 0;
}
void ResizeFrameBufferS(FrameBufferS *fbs, int n_w, int n_h)
{
    FreeFrameBufferS(fbs);                // free that last version
    (*fbs) = CreateFrameBuffer(n_w, n_h); // create a new one
    return;
}

/*func decl */
GLFWwindow *CreateWindow(int w, int h, const char *wname);
GLFWwindow *CreateWindowContext(int w, int h, const char *wname);
void InitGLFW();
void FreeWindow(GLFWwindow *window);
GLuint CreateShader(const char *vertexSource, const char *fragmentSource);
char *Read_File(const char *path);
GLuint CreateShaderFiles(const char *vertexPath, const char *fragmentPath);
GLuint ReloadShader(GLuint *shader, const char *vertexPath, const char *fragPath);
GLuint CreateVertexArrayObject();
GLuint CreateVertexBufferObject(const void *data, size_t sz);
void SetUniform1i(GLuint program, const char *name, int value);
void SetUniform1f(GLuint program, const char *name, float value);
void SetUniform3f(GLuint program, const char *name, float x, float y, float z);
void SetUniform4f(GLuint program, const char *name, float x, float y, float z, float w);
void SetUniformMat4(GLuint program, const char *name, const float *matrix);
TextureS LoadTexture(const char *path, TextureSetting setting);
bool IsShaderCompiled(GLuint shader, const char *shaderName);
bool IsProgramLinked(GLuint program);
void SetupVertexAttrib(GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer);
void SetViewport(int x, int y, int w, int h);                   // glViewport()
void FrameBufferSizeCallBack(GLFWwindow *window, int w, int h); // setViewort()
void RegisterFrameBufferSizeCallBack(GLFWwindow *window, void (*callback)(GLFWwindow *, int, int));
void EnableDepthTest();
void DisableDepthTest();
bool IsKeyPressed(GLFWwindow *window, int key);
void CleanScreen(float r, float g, float b, float alpha);
void FreeTextureS(TextureS *tex);
void BindTextureS(TextureS *tex);
void UnbindTextureS();
void DrawMeshS(MeshS *mesh);
void UpdateCameraFront(CameraControllerS *camera);
void MouseCallback(GLFWwindow *window, double xpos, double ypos);
/* those kinda help for debugging */
void AboutRenderer();
void ErrorCallback(int error, const char *description);
/* impl : about renderer and error callback*/
void AboutRenderer()
{
    const GLubyte *renderer = glGetString(GL_RENDERER);
    const GLubyte *version = glGetString(GL_VERSION);
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version: %s\n", version);
    return;
}

void ErrorCallback(int error, const char *description)
{
    fprintf(stderr, "GLFW Error [%d]: %s\n", error, description);
}

void EnableDepthTest()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    printf("Depth test enabled (GL_LESS)\n");
}

void DisableDepthTest()
{
    glDisable(GL_DEPTH_TEST);
    printf("Depth test disabled \n");
}

/* binding the mesh */
void BindMeshS(MeshS *mesh);
// implementation
void BindMeshS(MeshS *mesh)
{
    glBindVertexArray(mesh->vao);
    return;
}
// clear screen impl
void CleanScreen(float r, float g, float b, float alpha)
{
    glClearColor(r, g, b, alpha);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/* special for keys and input*/
bool IsKeyPressed(GLFWwindow *window, int key)
{
    return glfwGetKey(window, key) == GLFW_PRESS;
}

/* special function for drawing and projection*/
void ComputeMVP(float out[16], Mat4f model, Mat4f view, Mat4f projection);
Mat4f LookAt4f(Vec3f eye, Vec3f center, Vec3f up);
Mat4f Perspective4f(float fov, float aspect, float near, float far);
Mat4f Ortho4f(float right, float left, float bottom, float top, float near, float far);
/* func impl for drawing and projection*/

void ComputeMVP(float out[16], Mat4f model, Mat4f view, Mat4f projection)
{

    // MVP = view*model*projection
    // MVP as a flat(4x4) matrix

    Mat4f viewXmodel = mat4f_mul(model, view);
    Mat4f mvp = mat4f_mul(projection, viewXmodel);
    // Mat4f is 4x4 matrix but we need to flaten as OPENGL dump expect as to
    // do
    // OUT[y * 4 + x] = mvp.m[x][y];
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            out[y * 4 + x] = mvp.m[x][y];
        }
    }
}
// we define the camera orientation and position
// out : (4x4) matrix transform world cordinates into camera view space
Mat4f LookAt4f(Vec3f eye, Vec3f center, Vec3f up)
{
    Vec3f ce = vec3f_normalize(vec3f_sub(center, eye));
    Vec3f fup = vec3f_normalize(vec3f_cross(ce, up));
    Vec3f v = vec3f_cross(fup, ce);

    // output
    Mat4f result = mat4f_identity();

    result.m[0][0] = fup.x;
    result.m[0][1] = fup.y;
    result.m[0][2] = fup.z;

    result.m[1][0] = v.x;
    result.m[1][1] = v.y;
    result.m[1][2] = v.z;

    result.m[2][0] = -ce.x;
    result.m[2][1] = -ce.y;
    result.m[2][2] = -ce.z;

    result.m[0][3] = -vec3f_dot(fup, eye);
    result.m[1][3] = -vec3f_dot(v, eye);
    result.m[2][3] = -vec3f_dot(ce, eye);

    return result;
}

/* perpective of view objects : simulate human eyes / player
    fov : field of view angle (rad)
    aspect : w/h
    near,far : clipping planes
*/
Mat4f Perspective4f(float fov, float aspect, float near, float far)
{

    Mat4f res = {0};
    float tanhf = tanf(fov / 2.0f);
    res.m[0][0] = 1.0f / (aspect * tanhf);
    res.m[1][1] = 1.0f / tanhf;
    res.m[2][2] = -(far + near) / (far - near);
    res.m[2][3] = -2.0f * far * near / (far - near);
    res.m[3][2] = -1.0f;

    return res;
}

/* othographics projection matrix : no perspective
    especially we will need this for 2D & some UI overlays
*/
Mat4f Ortho4f(float right, float left, float bottom, float top, float near, float far)
{
    Mat4f res = mat4f_identity();

    res.m[0][0] = 2.0f / (right - left);
    res.m[1][1] = 2.0f / (top - bottom);
    res.m[2][2] = -2.0f / (far - near);

    res.m[0][3] = -(right + left) / (right - left);
    res.m[1][3] = -(top + bottom) / (top - bottom);
    res.m[2][3] = -(far + near) / (far - near);

    return res;
}

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

char *Read_File(const char *path)
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
    char *vertexSource = Read_File(vertexPath);
    if (!vertexSource)
    {
        fprintf(stderr, "Vertex shader file read error.\n");
        return 0;
    }

    char *fragmentSource = Read_File(fragmentPath);
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

TextureS LoadTexture(const char *path, TextureSetting setting)
{
    TextureS tex = {0};
    tex.setting = setting;

    unsigned char *data = stbi_load(path, &tex.w, &tex.h, &tex.pipes, 0);
    if (!data)
    {
        fprintf(stderr, "Failed to load texture : %s \n", path);
        TextureS S = {0};
        return S; // return a null object
    }
    GLenum format;
    switch (tex.pipes)
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
        fprintf(stderr, "unsupported number of pipes : %d", tex.pipes);
        stbi_image_free(data);
        return tex;
    }

    glGenTextures(1, &tex.id);
    glBindTexture(GL_TEXTURE_2D, tex.id);
    // todo: change setting to enum type will be better and more precise
    switch (setting)
    {
    case TEXTURE_REPEAT:
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

    glTexImage2D(GL_TEXTURE_2D, 0, format, tex.w, tex.h, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
    return tex;
}

void FreeTextureS(TextureS *tex)
{
    if (!tex)
    {
        return;
    }
    if (tex->id == 0)
    {
        fprintf(stderr, "already empty ....\n");
        return;
    }
    glDeleteTextures(1, &tex->id);
    tex->id = 0;
    tex->w = 0;
    tex->h = 0;
    tex->pipes = 0;
    tex->setting = TEXTURE_CLAMP;
}

void BindTextureS(TextureS *tex)
{
    glBindTexture(GL_TEXTURE_2D, tex->id);
}

void UnbindTextureS()
{
    // unbinding by setting the id to 0
    glBindTexture(GL_TEXTURE_2D, 0);
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

/* wrapper for glViewport(x,y,w,h)*/
void SetViewport(int x, int y, int w, int h)
{
    glViewport(x, y, w, h);
}
/* setViewport(0)*/
void FrameBufferSizeCallBack(GLFWwindow *window, int w, int h)
{
    SetViewport(0, 0, w, h);
}
/* glfwSetFramebufferSizeCallback (window , callback)
    window : window (window context)
    callback : FrameBufferSizeCallBack(int w , int h);

*/
void RegisterFrameBufferSizeCallBack(GLFWwindow *window, void (*callback)(GLFWwindow *, int, int))
{
    glfwSetFramebufferSizeCallback(window, callback);
}
/* drawing the mesh finally*/
void DrawMeshS(MeshS *mesh)
{
    // another option : GL_TRIANGLE_STRIP
    glBindVertexArray(mesh->vao);
    glDrawArrays(GL_TRIANGLES, 0, mesh->vertexCount);
}

/* updating the camera*/
void UpdateCameraFront(CameraControllerS *camera)
{
    Vec3f front;
    float radYaw = camera->yaw * (LAMATH_PI * 180.0f);
    float radPitch = camera->pitch * (LAMATH_PI / 180.0f);

    front.x = cosf(radYaw) * cosf(radPitch);
    front.y = sinf(radPitch);
    front.z = sinf(radYaw) * cosf(radPitch);
    camera->front = vec3f_normalize(front);
}

void MouseCallback(GLFWwindow *window, double xpos, double ypos)
{
    CameraControllerS camera;

    if (camera.firstMouse)
    {
        camera.lastx = xpos;
        camera.lasty = ypos;
        camera.firstMouse = 0;
    }

    float xoffset = xpos - camera.lastX;
    float yoffset = camera.lastY - ypos; // reversed y

    camera.lastX = xpos;
    camera.lastY = ypos;

    xoffset *= camera.sensitivity;
    yoffset *= camera.sensitivity;

    camera.yaw += xoffset;
    camera.pitch += yoffset;

    // Clamp pitch
    if (camera.pitch > 89.0f)
        camera.pitch = 89.0f;
    if (camera.pitch < -89.0f)
        camera.pitch = -89.0f;

    UpdateCameraFront(&camera);
}

#endif
