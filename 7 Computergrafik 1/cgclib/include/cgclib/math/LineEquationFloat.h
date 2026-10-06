#ifndef LINE_EQUATIONFLOAT_H
#define LINE_EQUATIONFLOAT_H
#include <assert.h>
#include <math.h>
#include <stdint.h>
#include <cgclib/math/FixedPoint.h>

typedef struct 
{
  float nx;
  float ny;
  float d;
  float   invLength;
} LineEquationFloat;

static inline LineEquationFloat CreateLineEquationFloat(float ax, float ay, float bx, float by)
{
  LineEquationFloat result = {0};
  // TODO: Implement me (Sheet B02, Assignment 2)
  return result;
}

static inline float EvalLineEquationFloat(LineEquationFloat lineEquation, float x, float y)
{
  // TODO: Implement me (Sheet B02, Assignment 2)
  return 0;
}


static inline float DistanceToLineFloat(LineEquationFloat lineEquation, float x, float y)
{
  // TODO: Implement me (Sheet B02, Assignment 2)
  return 0.0f;
}

#endif
