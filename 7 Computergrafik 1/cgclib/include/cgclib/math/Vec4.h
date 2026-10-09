#ifndef VEC4_H
#define VEC4_H

#include "Vec3.h"
/**
 * @brief Represents a 4D vector with float components.
 *
 * Provides both named access (x, y, z, w) and array-style access (m[0] to m[3]).
 */
typedef struct
{
    float x, y, z, w;
} Vec4;

/**
 * @brief Converts a 4D homogeneous vector to a 3D Cartesian vector.
 *
 * Performs perspective division by w: (x/w, y/w, z/w).
 *
 * @param p Input 4D vector.
 * @return Vec3 Resulting 3D vector.
 */
static inline Vec3 Homogenize(Vec4 p)
{
    // TODO: Implement me (Sheet A04, Assignment 1)
    return (Vec3) { 0, 0, 0 };
}

#endif
