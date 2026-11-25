#ifndef MAT4_H
#define MAT4_H
#define _USE_MATH_DEFINES
#include <cgclib/math/Vec3.h>
#include <cgclib/math/Vec4.h>
#include <math.h>

/**
 * @brief Represents a 4x4 matrix using a flat array of 16 floats.
 *
 * The matrix is stored in row-major order:
 * m[0] to m[3] -> first row,
 * m[4] to m[7] -> second row, etc.
 */
typedef struct
{
    float m[16];
} Mat4;

/**
 * @brief Computes the linear index in the 1D array for a given row and column in a 4x4 matrix.
 *
 * @param r__ Row index (0-3)
 * @param c__ Column index (0-3)
 * @return Index in the flat array representing the matrix.
 */
#define M4Ofs(r__, c__) (((r__) * 4) + (c__))

/**
 * @brief Creates and returns a 4x4 identity matrix.
 *
 * @return Mat4 Identity matrix.
 */
static inline Mat4 SetIdentity()
{
    Mat4 r = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
    return r;
}

/**
 * @brief Creates a 4x4 rotation matrix around the Z-axis.
 *
 * @param angle Rotation angle in radians.
 * @return Mat4 Z-axis rotation matrix.
 */
static inline Mat4 SetRotateZ(float angle)
{
    const auto sin_a = sinf(angle);
    const auto cos_a = cosf(angle);

    Mat4 r = { cos_a, -sin_a, 0, 0, sin_a, cos_a, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
    return r;
}

/**
 * @brief Creates a 4x4 rotation matrix around the X-axis.
 *
 * @param angle Rotation angle in radians.
 * @return Mat4 X-axis rotation matrix.
 */
static inline Mat4 SetRotateX(float angle)
{
    const auto sin_a = sinf(angle);
    const auto cos_a = cosf(angle);

    Mat4 r = { 1, 0, 0, 0, 0, cos_a, -sin_a, 0, 0, sin_a, cos_a, 0, 0, 0, 0, 1 };
    return r;
}

/**
 * @brief Creates a 4x4 rotation matrix around the Y-axis.
 *
 * @param angle Rotation angle in radians.
 * @return Mat4 Y-axis rotation matrix.
 */
static inline Mat4 SetRotateY(float angle)
{
    const auto sin_a = sinf(angle);
    const auto cos_a = cosf(angle);

    Mat4 r = { cos_a, 0, sin_a, 0, 0, 1, 0, 0, -sin_a, 0, cos_a, 0, 0, 0, 0, 1 };
    return r;
}

/**
 * @brief Creates a 4x4 translation matrix.
 *
 * @param tx Translation along the X-axis.
 * @param ty Translation along the Y-axis.
 * @param tz Translation along the Z-axis.
 * @return Mat4 Translation matrix.
 */
static inline Mat4 SetTranslate(float tx, float ty, float tz)
{
    Mat4 r = { 1, 0, 0, tx, 0, 1, 0, ty, 0, 0, 1, tz, 0, 0, 0, 1 };
    return r;
}

/**
 * @brief Creates a 4x4 scaling matrix.
 *
 * @param sx Scaling factor along the X-axis.
 * @param sy Scaling factor along the Y-axis.
 * @param sz Scaling factor along the Z-axis.
 * @return Mat4 Scaling matrix.
 */
static inline Mat4 SetScale(float sx, float sy, float sz)
{
    Mat4 r = { sx, 0, 0, 0, 0, sy, 0, 0, 0, 0, sz, 0, 0, 0, 0, 1 };
    return r;
}

/**
 * @brief Multiplies two 4x4 matrices.
 *
 * @param a First matrix.
 * @param b Second matrix.
 * @return Mat4 Result of a * b.
 */
static inline Mat4 Mat4xMat4(Mat4 a, Mat4 b)
{
    Mat4 result = {};

    for (int r = 0; r < 4; r++)
    {
        for (int c = 0; c < 4; c++)
        {
            float sum = 0;
            for (int k = 0; k < 4; k++)
            {
                sum += a.m[M4Ofs(r, k)] * b.m[M4Ofs(k, c)];
            }
            result.m[M4Ofs(r, c)] = sum;
        }
    }

    return result;
}

/**
 * @brief Applies an affine transformation to a 3D vector.
 *
 * @param a Transformation matrix.
 * @param b Input 3D vector.
 * @return Vec3 Transformed 3D vector.
 */
static inline Vec3 Mat4xVec3Affine(Mat4 a, Vec3 b)
{
    Vec3 result = {
        a.m[M4Ofs(0, 0)] * b.x + a.m[M4Ofs(0, 1)] * b.y + a.m[M4Ofs(0, 2)] * b.z + a.m[M4Ofs(0, 3)],
        a.m[M4Ofs(1, 0)] * b.x + a.m[M4Ofs(1, 1)] * b.y + a.m[M4Ofs(1, 2)] * b.z + a.m[M4Ofs(1, 3)],
        a.m[M4Ofs(2, 0)] * b.x + a.m[M4Ofs(2, 1)] * b.y + a.m[M4Ofs(2, 2)] * b.z + a.m[M4Ofs(2, 3)],
    };
    return result;
}

/**
 * @brief Applies a linear transformation to a 3D vector, returning a 4D vector.
 * Implicitly assumes that b[3] = 1, if b was 4D vector.
 *
 * @param a Transformation matrix.
 * @param b Input 3D vector.
 * @return Vec4 Transformed 4D vector.
 */
static inline Vec4 Mat4xVec3(Mat4 a, Vec3 b)
{
    Vec4 result = {
        a.m[M4Ofs(0, 0)] * b.x + a.m[M4Ofs(0, 1)] * b.y + a.m[M4Ofs(0, 2)] * b.z + a.m[M4Ofs(0, 3)],
        a.m[M4Ofs(1, 0)] * b.x + a.m[M4Ofs(1, 1)] * b.y + a.m[M4Ofs(1, 2)] * b.z + a.m[M4Ofs(1, 3)],
        a.m[M4Ofs(2, 0)] * b.x + a.m[M4Ofs(2, 1)] * b.y + a.m[M4Ofs(2, 2)] * b.z + a.m[M4Ofs(2, 3)],
        a.m[M4Ofs(3, 0)] * b.x + a.m[M4Ofs(3, 1)] * b.y + a.m[M4Ofs(3, 2)] * b.z + a.m[M4Ofs(3, 3)],
    };
    return result;
}

/**
 * @brief Applies the upper-left 3x3 part of a 4x4 matrix to a 3D vector.
 *
 * @param a Transformation matrix.
 * @param b Input 3D vector.
 * @return Vec3 Transformed 3D vector.
 */
static inline Vec3 Mat3xVec3(Mat4 a, Vec3 b)
{
    Vec3 result = {
        a.m[M4Ofs(0, 0)] * b.x + a.m[M4Ofs(0, 1)] * b.y + a.m[M4Ofs(0, 2)] * b.z,
        a.m[M4Ofs(1, 0)] * b.x + a.m[M4Ofs(1, 1)] * b.y + a.m[M4Ofs(1, 2)] * b.z,
        a.m[M4Ofs(2, 0)] * b.x + a.m[M4Ofs(2, 1)] * b.y + a.m[M4Ofs(2, 2)] * b.z,
    };
    return result;
}

#endif
