#ifndef RE_OPENGL_H
#define RE_OPENGL_H

/* list of includes */
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stb_img.h"
#include "cglm/cglm.h"
#include <math.h>
/* end list of includes*/

typedef enum
{
    TEXTURE_CLAMP,
    TEXTURE_REPEAT
} TextureSettingS;

typedef enum
{
    FILTER_LINEAR,
    FILTER_NEAREST
} TextureFilterS;

typedef struct
{
    GLuint id;
    int width;
    int height;
    size_t channels;
    TextureSettingS setting;

} TextureS;
typedef struct
{
    mat4 view;
    mat4 projections;
} CameraS;
/* for the camera control setting*/
typedef struct
{
    CameraS camera;
    vec3 position;
    vec3 front;
    vec3 up;
    float speed;
    float sensitivity;
    float yaw;
    float pitch;
    float lastx;
    float lasty;
} CCameraS;

typedef struct
{
    GLuint vao;
    GLuint vbo;
    TextureS texture;
    int vertexCount;
    float mvp[16];
} MeshS;

typedef struct
{
    GLuint FBO;
    GLuint RBO;
    TextureS texture;
    int width;
    int height;
} FrameBufferS;
typedef struct
{
    CCameraS camera;
    FrameBufferS framebuffer;
    GLuint defaultShader;
    GLuint quadVAO;
} RendererS;

typedef enum
{
    UI_BUTTON,
    UI_TEXT,
    UI_LABEL,
    UI_BOX,
    UI_MOUSE
} UItypeS;

typedef struct
{
    TextureS texture;
    vec2 position;
    vec2 size;
    UItypeS type;
    bool isVisible;
} UIelementS;
typedef enum
{
    UI_STATE_NORMAL,
    UI_STATE_HOVER,
    UI_STATE_PRESSED
} UIButtonState;

typedef struct UIelementS
{
    TextureS textureNormal;
    TextureS textureHover;
    TextureS texturePressed;
    vec2 position;
    vec2 size;
    UItypeS type;
    bool isVisible;
    UIButtonState state;
    void (*onClick)(struct UIelementS *btn);
} UIButtonS;

/* function declaration*/
GLFWwindow *CreateWindowContext(int w, int h, const char *wname);
void InitGLFW();
void DestroyWindow(GLFWwindow *window);
GLuint CreateShaderStr(const char *vertexShSouce, const char *fragmentShSource);
GLuint CreateShaderFiles(const char *vertexShPath, const char *fragmentShPath);
GLuint CreateVertexArrayObject();
GLuint CreateVertexBufferObject(const void *data, size_t size);
bool IsShaderCompiled(GLuint shader, const char *shaderName);
bool IsProgramLinked(GLuint program);
TextureS LoadTexture(const char *path, TextureSettingS setting);
void SetUniform1i(GLuint program, const char *name, int value);
void SetUniform1f(GLuint program, const char *name, float value);
void SetUniform3f(GLuint program, const char *name, float x, float y, float z);
void SetUniform4f(GLuint program, const char *name, float x, float y, float z, float w);
void SetUniformMat4(GLuint program, const char *name, const float *matrix);
void SetupVertexAttrib(GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer);
void SetViewport(int x, int y, int w, int h);
char *ReadGlslfile(const char *filepath);
void EnableDepthTest();
void DisableDepthTest();
static inline bool IsKeyPressed(GLFWwindow *window, int key);
void CleanScreen(float r, float g, float b, float alpha);
void FreeTextureS(TextureS *tex);
void BindTextureS(TextureS *tex);
void UnbindTextureS();
void BindMeshS(MeshS *mesh, GLuint shaderProgram);
void DrawMeshS(MeshS *mesh);
void DeleteMeshS(MeshS *mesh);
void AboutRenderer();
void InitCamera(CCameraS *cam);
void UpdateCameraFront(CCameraS *cam);
void UpdateViewMatrix(CCameraS *cam);
void UpdateCamera(GLFWwindow *window, CCameraS *cam, float deltaTime);
void MouseCallback(GLFWwindow *window, double xpos, double ypos);
void ProcessKeyboardInput(GLFWwindow *window, CCameraS *cam, float deltaTime);
float CalculateFPS();
bool CreateFrameBuffer(FrameBufferS *fb, int width, int height);
TextureS LoadEmptyTexture(int width, int height);
void FreeFrameBuffer(FrameBufferS *fb);
void BindFrameBuffer(FrameBufferS *fb);
void UnbindFrameBuffer(int windowWidth, int windowHeight);
void DrawFrameBufferTexture(FrameBufferS *fb, GLuint shaderProgram, GLuint quadVAO);
void UpdateCameraProjection(CCameraS *cam, float fovDeg, float aspect, float nearZ, float farZ);
void UpdateCameraOrtho(CCameraS *cam, float left, float right, float bottom, float top, float nearZ, float farZ);
/* framebuffersizecallback for updating the view port when resizing the window*/
void FramebufferSizeCallback(GLFWwindow *window, int width, int height);
/* framebuffersizecallback update the view port and the camera projection */
void SizeCallbackViewCam(GLFWwindow *window, int width, int height);

/* ----> all those function are deprecated <----------
void ComputeMVP(float out[16], mat4 model, mat4 view, mat4 projection);
mat4 LookAt4f(vec3 eye, vec3 center, vec3 up);
mat4 Perspective4f(float fov, float aspect, float near, float far);
mat4 Ortho4f(float right, float left, float bottom, float top, float near, float far);

we will use the follwing functions instead :
->Perspective projection:
void glm_perspective(float fovy, float aspect, float nearZ, float farZ, mat4 dest);
->Orthographic projection:
void glm_ortho(float left, float right, float bottom, float top, float nearZ, float farZ, mat4 dest);
->look at :
void glm_lookat(vec3 eye, vec3 center, vec3 up, mat4 dest);
->Multiply MVP:
glm_mat4_mul(projection, view, pv);
glm_mat4_mul(pv, model, mvp);

*/


#endif // RE_OPENGL_H
