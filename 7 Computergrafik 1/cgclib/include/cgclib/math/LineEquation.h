#ifndef LINE_EQUATION_H
#define LINE_EQUATION_H
#include <assert.h>
#include <cgclib/math/FixedPoint.h>
#include <math.h>
#include <stdint.h>

/**
 * @brief Represents a 2D line equation in normal form.
 *
 * The line is defined by its normal vector (nx, ny), a constant d,
 * and the inverse length of the normal vector for distance calculations.
 */
typedef struct LineEquation
{
    fixed_t nx;
    fixed_t ny;
    fixed_t d;
    float   invLength;
} LineEquation;

/**
 * @brief Creates a line equation from two points in 2D space.
 *
 * Computes the normal vector and constant term for the line passing through (ax, ay) and (bx, by).
 *
 * @param ax X-coordinate of the first point.
 * @param ay Y-coordinate of the first point.
 * @param bx X-coordinate of the second point.
 * @param by Y-coordinate of the second point.
 * @return LineEquation Struct representing the line equation.
 */
static inline LineEquation CreateLineEquation(fixed_t ax, fixed_t ay, fixed_t bx, fixed_t by)
{
    LineEquation result = { 0 };
    // TODO: Implement me (Sheet A02, Assignment 2)
    return result;
}

/**
 * @brief Evaluates the line equation at a given point.
 *
 * Returns the signed distance from the point (x, y) to the line (not normalized).
 *
 * @param lineEquation Line equation to evaluate.
 * @param x X-coordinate of the point.
 * @param y Y-coordinate of the point.
 * @return int32_t Signed value of the line equation at (x, y).
 */
static inline int32_t EvalLineEquation(LineEquation lineEquation, fixed_t x, fixed_t y)
{
    // TODO: Implement me (Sheet A02, Assignment 2)
    return 0;
}

/**
 * @brief Computes the perpendicular distance from a point to the line.
 *
 * Uses the normalized line equation to calculate the true Euclidean distance.
 *
 * @param lineEquation Line equation to evaluate.
 * @param x X-coordinate of the point.
 * @param y Y-coordinate of the point.
 * @return float Distance from the point to the line.
 */
static inline float DistanceToLine(LineEquation lineEquation, fixed_t x, fixed_t y)
{
    // TODO: Implement me (Sheet A02, Assignment 2)
    return 0.0f;
}

#endif
