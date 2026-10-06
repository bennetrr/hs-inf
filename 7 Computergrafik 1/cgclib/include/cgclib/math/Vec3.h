#ifndef VEC3_H
#define VEC3_H

#include <math.h>
#include <stdint.h>

/**
 * @brief Represents a 3D vector with float components.
 *
 * Provides both named access (x, y, z) and array-style access (m[0], m[1], m[2]).
 */
typedef struct
{
  float x, y, z;
} Vec3;

/**
 * @brief Adds two 3D vectors component-wise.
 *
 * @param a First vector.
 * @param b Second vector.
 * @return Vec3 Resulting cross product vector of a and b.
 */
static inline Vec3 Add(Vec3 a, Vec3 b)
{
    // TODO: Implement me (Sheet A00, Assignment 1)
  return (Vec3) {0, 0, 0};
}

/**
 * @brief Subtracts two 3D vectors component-wise.
 *
 * @param a First vector.
 * @param b Second vector.
 * @return Vec3 Resulting difference vector of a and b.
 */
static inline Vec3 Sub(Vec3 a, Vec3 b)
{
  // TODO: Implement me (Sheet A00, Assignment 1)
  return (Vec3) {0, 0, 0};
}

/**
 * @brief Computes a barycentric weighted sum of three vectors,
 * i.e., (1-beta-gamma)*a + beta*b + gamma*c.
 *
 * @param beta Weight for vector b.
 * @param gamma Weight for vector c.
 * @param a Base vector.
 * @param b Second vector.
 * @param c Third vector.
 * @return Vec3 Resulting weighted combination.
 */
static inline Vec3 WeightedSum(float beta, float gamma, Vec3 a, Vec3 b, Vec3 c)
{
  // TODO: Implement me (Sheet A00, Assignment 1)
  return (Vec3) {0, 0, 0};
}

/**
 * @brief Computes the dot product of two vectors.
 *
 * @param a First vector.
 * @param b Second vector.
 * @return float Scalar, as a result of the dot product of a and b.
 */
static inline float Dot(Vec3 a, Vec3 b)
{
  // TODO: Implement me (Sheet A00, Assignment 1)
  return 0.0f;
}

/**
 * @brief Scales a vector by a scalar value.
 *
 * @param s Scalar multiplier.
 * @param v Vector to scale.
 * @return Vec3 Scaled vector.
 */
static inline Vec3 Scale(float s, Vec3 v)
{
  // TODO: Implement me (Sheet A00, Assignment 1)
  return (Vec3) {0, 0, 0};
}

/**
 * @brief Computes the cross product of two vectors.
 *
 * @param a First vector.
 * @param b Second vector.
 * @return Vec3 Resulting cross product vector of a and b.
 */
static inline Vec3 Cross(Vec3 a, Vec3 b)
{
  // TODO: Implement me (Sheet A00, Assignment 1)
  return (Vec3) {0, 0, 0};
}

/**
 * @brief Computes the Euclidean length (magnitude) of a vector.
 *
 * @param a Input vector.
 * @return float Length of the vector.
 */
static inline float Length(Vec3 a)
{
  // TODO: Implement me (Sheet A00, Assignment 1)
  return 0.0f;
}

/**
 * @brief Normalizes a vector to unit length.
 *
 * @param a Input vector. Behavior is undefined if a is the zero vector.
 * @return Vec3 Normalized vector with length 1.
 */
static inline Vec3 Normalize(Vec3 a)
{
  // TODO: Implement me (Sheet A00, Assignment 1)
  return (Vec3) {0, 0, 0};
}

#endif
