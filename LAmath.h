// a simple math lib for linear algebra
// it very basic ! for educational purpose
// do not take too serious!

#ifndef MATH_LINEAR_ALG_DECL
#define MATH_LINEAR_ALG_DECL

#include <stdlib.h>
#include <math.h>

typedef struct
{
    int x;
    int y;

} Vec2i;

typedef struct
{
    float x;
    float y;
} Vec2f;

typedef struct
{
    int x;
    int y;
    int z;
} Vec3i;

typedef struct
{
    float x;
    float y;
    float z;
} Vec3f;

typedef struct
{
    int x, y, z, w;
} Vec4i;

typedef struct
{
    float x, y, z, w;
} Vec4f;

Vec2i vec2i(int x, int y)
{
    Vec2i vec;
    vec.x = x;
    vec.y = y;
    return vec;
}
Vec2f vec2f(float x, float y)
{
    Vec2f vec;
    vec.x = x;
    vec.y = y;
    return vec;
}
Vec3i vec3i(int x, int y, int z)
{
    Vec3i vec;
    vec.x = x;
    vec.y = y;
    vec.z = z;
    return vec;
}
Vec3f vec3f(float x, float y, float z)
{
    Vec3f vec;
    vec.x = x;
    vec.y = y;
    vec.z = z;
    return vec;
}
Vec4i vec4i(int x, int y, int z, int w)
{
    Vec4i vec;
    vec.x = x;
    vec.y = y;
    vec.z = z;
    vec.w = w;
    return vec;
}
Vec4f vec4f(float x, float y, float z, float w)
{
    Vec4f vec;
    vec.x = x;
    vec.y = y;
    vec.z = z;
    vec.w = w;
    return vec;
}

Vec2i vec2i_add(Vec2i a, Vec2i b)
{
    Vec2i result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    return result;
}

Vec2i vec2i_sub(Vec2i a, Vec2i b)
{
    Vec2i result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    return result;
}

Vec2i vec2i_mul_scalar(Vec2i v, int s)
{
    Vec2i result;
    result.x = v.x * s;
    result.y = v.y * s;
    return result;
}

int vec2i_dot(Vec2i a, Vec2i b)
{
    return a.x * b.x + a.y * b.y;
}

float vec2i_length(Vec2i v)
{
    return sqrtf((float)(v.x * v.x + v.y * v.y));
}

Vec2f vec2f_add(Vec2f a, Vec2f b)
{
    Vec2f result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    return result;
}

Vec2f vec2f_sub(Vec2f a, Vec2f b)
{
    Vec2f result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    return result;
}

Vec2f vec2f_mul_scalar(Vec2f v, float s)
{
    Vec2f result;
    result.x = v.x * s;
    result.y = v.y * s;
    return result;
}

float vec2f_dot(Vec2f a, Vec2f b)
{
    return a.x * b.x + a.y * b.y;
}

float vec2f_length(Vec2f v)
{
    return sqrtf(v.x * v.x + v.y * v.y);
}

Vec2f vec2f_normalize(Vec2f v)
{
    float len = vec2f_length(v);
    Vec2f result;
    if (len == 0.0f)
    {
        result.x = 0.0f;
        result.y = 0.0f;
    }
    else
    {
        result.x = v.x / len;
        result.y = v.y / len;
    }
    return result;
}

Vec3f vec3f_add(Vec3f a, Vec3f b)
{
    Vec3f result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    return result;
}

Vec3f vec3f_sub(Vec3f a, Vec3f b)
{
    Vec3f result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    return result;
}

Vec3f vec3f_mul_scalar(Vec3f v, float s)
{
    Vec3f result;
    result.x = v.x * s;
    result.y = v.y * s;
    result.z = v.z * s;
    return result;
}

float vec3f_dot(Vec3f a, Vec3f b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

float vec3f_length(Vec3f v)
{
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vec3f vec3f_normalize(Vec3f v)
{
    float len = vec3f_length(v);
    Vec3f result;
    if (len == 0.0f)
    {
        result.x = result.y = result.z = 0.0f;
    }
    else
    {
        result.x = v.x / len;
        result.y = v.y / len;
        result.z = v.z / len;
    }
    return result;
}

Vec3f vec3f_cross(Vec3f a, Vec3f b)
{
    Vec3f result;
    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;
    return result;
}

Vec4i vec4i_add(Vec4i a, Vec4i b)
{
    Vec4i result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    result.w = a.w + b.w;
    return result;
}

Vec4i vec4i_sub(Vec4i a, Vec4i b)
{
    Vec4i result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    result.w = a.w - b.w;
    return result;
}

Vec4i vec4i_mul_scalar(Vec4i v, int s)
{
    Vec4i result;
    result.x = v.x * s;
    result.y = v.y * s;
    result.z = v.z * s;
    result.w = v.w * s;
    return result;
}

int vec4i_dot(Vec4i a, Vec4i b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

float vec4i_length(Vec4i v)
{
    return sqrtf((float)(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w));
}

Vec4f vec4f_add(Vec4f a, Vec4f b)
{
    Vec4f result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    result.w = a.w + b.w;
    return result;
}

Vec4f vec4f_sub(Vec4f a, Vec4f b)
{
    Vec4f result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    result.w = a.w - b.w;
    return result;
}

Vec4f vec4f_mul_scalar(Vec4f v, float s)
{
    Vec4f result;
    result.x = v.x * s;
    result.y = v.y * s;
    result.z = v.z * s;
    result.w = v.w * s;
    return result;
}

float vec4f_dot(Vec4f a, Vec4f b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

float vec4f_length(Vec4f v)
{
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}

Vec4f vec4f_normalize(Vec4f v)
{
    float len = vec4f_length(v);
    Vec4f result;
    if (len == 0.0f)
    {
        result.x = result.y = result.z = result.w = 0.0f;
    }
    else
    {
        result.x = v.x / len;
        result.y = v.y / len;
        result.z = v.z / len;
        result.w = v.w / len;
    }
    return result;
}

// Matrix operations

typedef struct
{
    float m[2][2];
} Mat2f;

typedef struct
{
    float m[3][3];
} Mat3f;

typedef struct
{
    float m[4][4];
} Mat4f;

Mat2f mat2f(float m00, float m01, float m10, float m11)
{
    Mat2f result;
    result.m[0][0] = m00;
    result.m[0][1] = m01;
    result.m[1][0] = m10;
    result.m[1][1] = m11;
    return result;
}

Mat3f mat3f(
    float m00, float m01, float m02,
    float m10, float m11, float m12,
    float m20, float m21, float m22)
{

    Mat3f result;
    result.m[0][0] = m00;
    result.m[0][1] = m01;
    result.m[0][2] = m02;
    result.m[1][0] = m10;
    result.m[1][1] = m11;
    result.m[1][2] = m12;
    result.m[2][0] = m20;
    result.m[2][1] = m21;
    result.m[2][2] = m22;
    return result;
}
Mat4f mat4f(
    float m00, float m01, float m02, float m03,
    float m10, float m11, float m12, float m13,
    float m20, float m21, float m22, float m23,
    float m30, float m31, float m32, float m33)
{

    Mat4f result;
    result.m[0][0] = m00;
    result.m[0][1] = m01;
    result.m[0][2] = m02;
    result.m[0][3] = m03;
    result.m[1][0] = m10;
    result.m[1][1] = m11;
    result.m[1][2] = m12;
    result.m[1][3] = m13;
    result.m[2][0] = m20;
    result.m[2][1] = m21;
    result.m[2][2] = m22;
    result.m[2][3] = m23;
    result.m[3][0] = m30;
    result.m[3][1] = m31;
    result.m[3][2] = m32;
    result.m[3][3] = m33;
    return result;
}

Mat2f mat2f_identity()
{
    Mat2f result;
    result.m[0][0] = 1.0f;
    result.m[0][1] = 0.0f;
    result.m[1][0] = 0.0f;
    result.m[1][1] = 1.0f;
    return result;
}

Mat2f mat2f_mul(Mat2f a, Mat2f b)
{
    Mat2f result;
    int i, j, k;
    for (i = 0; i < 2; ++i)
    {
        for (j = 0; j < 2; ++j)
        {
            result.m[i][j] = 0.0f;
            for (k = 0; k < 2; ++k)
            {
                result.m[i][j] += a.m[i][k] * b.m[k][j];
            }
        }
    }
    return result;
}

Vec2f mat2f_mul_vec2f(Mat2f m, Vec2f v)
{
    Vec2f result;
    result.x = m.m[0][0] * v.x + m.m[0][1] * v.y;
    result.y = m.m[1][0] * v.x + m.m[1][1] * v.y;
    return result;
}

Mat2f mat2f_transpose(Mat2f m)
{
    Mat2f result;
    result.m[0][0] = m.m[0][0];
    result.m[0][1] = m.m[1][0];
    result.m[1][0] = m.m[0][1];
    result.m[1][1] = m.m[1][1];
    return result;
}

Mat3f mat3f_identity()
{
    Mat3f result;
    int i, j;
    for (i = 0; i < 3; ++i)
        for (j = 0; j < 3; ++j)
            result.m[i][j] = (i == j) ? 1.0f : 0.0f;
    return result;
}

Mat3f mat3f_mul(Mat3f a, Mat3f b)
{
    Mat3f result;
    int i, j, k;
    for (i = 0; i < 3; ++i)
    {
        for (j = 0; j < 3; ++j)
        {
            result.m[i][j] = 0.0f;
            for (k = 0; k < 3; ++k)
            {
                result.m[i][j] += a.m[i][k] * b.m[k][j];
            }
        }
    }
    return result;
}

Vec3f mat3f_mul_vec3f(Mat3f m, Vec3f v)
{
    Vec3f result;
    result.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z;
    result.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z;
    result.z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z;
    return result;
}

Mat3f mat3f_transpose(Mat3f m)
{
    Mat3f result;
    int i, j;
    for (i = 0; i < 3; ++i)
        for (j = 0; j < 3; ++j)
            result.m[i][j] = m.m[j][i];
    return result;
}

Mat4f mat4f_identity()
{
    Mat4f result;
    int i, j;
    for (i = 0; i < 4; ++i)
        for (j = 0; j < 4; ++j)
            result.m[i][j] = (i == j) ? 1.0f : 0.0f;
    return result;
}

Mat4f mat4f_mul(Mat4f a, Mat4f b)
{
    Mat4f result;
    int i, j, k;
    for (i = 0; i < 4; ++i)
    {
        for (j = 0; j < 4; ++j)
        {
            result.m[i][j] = 0.0f;
            for (k = 0; k < 4; ++k)
            {
                result.m[i][j] += a.m[i][k] * b.m[k][j];
            }
        }
    }
    return result;
}

Vec4f mat4f_mul_vec4f(Mat4f m, Vec4f v)
{
    Vec4f result;
    result.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z + m.m[0][3] * v.w;
    result.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z + m.m[1][3] * v.w;
    result.z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z + m.m[2][3] * v.w;
    result.w = m.m[3][0] * v.x + m.m[3][1] * v.y + m.m[3][2] * v.z + m.m[3][3] * v.w;
    return result;
}

Mat4f mat4f_transpose(Mat4f m)
{
    Mat4f result;
    int i, j;
    for (i = 0; i < 4; ++i)
        for (j = 0; j < 4; ++j)
            result.m[i][j] = m.m[j][i];
    return result;
}

Mat4f mat4f_translate(Vec3f t)
{
    Mat4f result = mat4f_identity();
    result.m[0][3] = t.x;
    result.m[1][3] = t.y;
    result.m[2][3] = t.z;
    return result;
}
Mat4f mat4f_scale(Vec3f s)
{
    Mat4f result = mat4f_identity();
    result.m[0][0] = s.x;
    result.m[1][1] = s.y;
    result.m[2][2] = s.z;
    return result;
}

Mat4f mat4f_rotate_x(float angle)
{
    Mat4f result = mat4f_identity();
    float c = cosf(angle);
    float s = sinf(angle);

    result.m[1][1] = c;
    result.m[1][2] = -s;
    result.m[2][1] = s;
    result.m[2][2] = c;
    return result;
}

Mat4f mat4f_rotate_y(float angle)
{
    Mat4f result = mat4f_identity();
    float c = cosf(angle);
    float s = sinf(angle);

    result.m[0][0] = c;
    result.m[0][2] = s;
    result.m[2][0] = -s;
    result.m[2][2] = c;
    return result;
}

Mat4f mat4f_rotate_z(float angle)
{
    Mat4f result = mat4f_identity();
    float c = cosf(angle);
    float s = sinf(angle);

    result.m[0][0] = c;
    result.m[0][1] = -s;
    result.m[1][0] = s;
    result.m[1][1] = c;
    return result;
}

Mat4f mat4f_rotate_axis(Vec3f axis, float angle)
{
    axis = vec3f_normalize(axis);
    float x = axis.x, y = axis.y, z = axis.z;
    float c = cosf(angle);
    float s = sinf(angle);
    float one_minus_c = 1.0f - c;

    Mat4f result;
    result.m[0][0] = c + x * x * one_minus_c;
    result.m[0][1] = x * y * one_minus_c - z * s;
    result.m[0][2] = x * z * one_minus_c + y * s;
    result.m[0][3] = 0.0f;

    result.m[1][0] = y * x * one_minus_c + z * s;
    result.m[1][1] = c + y * y * one_minus_c;
    result.m[1][2] = y * z * one_minus_c - x * s;
    result.m[1][3] = 0.0f;

    result.m[2][0] = z * x * one_minus_c - y * s;
    result.m[2][1] = z * y * one_minus_c + x * s;
    result.m[2][2] = c + z * z * one_minus_c;
    result.m[2][3] = 0.0f;

    result.m[3][0] = 0.0f;
    result.m[3][1] = 0.0f;
    result.m[3][2] = 0.0f;
    result.m[3][3] = 1.0f;

    return result;
}

Mat4f mat4f_perspective(float fov_radians, float aspect, float near, float far)
{
    Mat4f result = {0};

    float f = 1.0f / tanf(fov_radians / 2.0f);
    result.m[0][0] = f / aspect;
    result.m[1][1] = f;
    result.m[2][2] = (far + near) / (near - far);
    result.m[2][3] = (2.0f * far * near) / (near - far);
    result.m[3][2] = -1.0f;

    return result;
}
Mat4f mat4f_ortho(float left, float right, float bottom, float top, float near, float far)
{
    Mat4f result = mat4f_identity();

    result.m[0][0] = 2.0f / (right - left);
    result.m[1][1] = 2.0f / (top - bottom);
    result.m[2][2] = -2.0f / (far - near);

    result.m[0][3] = -(right + left) / (right - left);
    result.m[1][3] = -(top + bottom) / (top - bottom);
    result.m[2][3] = -(far + near) / (far - near);

    return result;
}
#endif
