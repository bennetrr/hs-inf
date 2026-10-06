#define _USE_MATH_DEFINES
#include <math.h>

#include <cgclib/math/Lighting.h>
#include <cgclib/math/LineEquation.h>
#include <cgclib/math/LineEquationFloat.h>
#include <cgclib/raster/Triangle.h>
#include <cgclib/raster/TriangleCull.h>
#include <stdlib.h>

void DrawTriangleFlatFloat(PixelBuffer p, float ax, float ay, float bx, float by, float cx, float cy, Vec3 color)
{
  // TODO: Implement me (Sheet B02, Assignment 5)
}

void DrawTriangleFlat(PixelBuffer p, fixed_t ax, fixed_t ay, fixed_t bx, fixed_t by, fixed_t cx, fixed_t cy, Vec3 color)
{
  // TODO: Implement me (Sheet A02, Assignment 5)
}


void DrawTriangleGouraud(PixelBuffer p, fixed_t ax, fixed_t ay, fixed_t bx, fixed_t by, fixed_t cx, fixed_t cy,
                         Vec3 aColor, Vec3 bColor, Vec3 cColor)
{
  // TODO: Implement me (Sheet A05, Assignment 1)
}

void DrawTriangleZBufferFlat(PixelBuffer p, fixed_t ax, fixed_t ay, fixed_t bx, fixed_t by, fixed_t cx, fixed_t cy,
                             float z0, float z1, float z2, Vec3 color)
{
  // TODO: Implement me (Sheet A06, Assignment 1)
}

void DrawTriangleZBufferGouraud(PixelBuffer p, fixed_t ax, fixed_t ay, fixed_t bx, fixed_t by, fixed_t cx, fixed_t cy,
                                float z0, float z1, float z2, Vec3 aColor, Vec3 bColor, Vec3 cColor)
{
  // TODO: Implement me (Sheet A08, Assignment 2)
}

void DrawTriangleZBufferBlinnPhong(PixelBuffer p, fixed_t ax, fixed_t ay, fixed_t bx, fixed_t by, fixed_t cx,
                                   fixed_t cy, float z0, float z1, float z2, Vec3 aNormal, Vec3 bNormal, Vec3 cNormal,
                                   Vec3 aPos, Vec3 bPos, Vec3 cPos, Vec3 dColor, Vec3 sColor, float shinyness,
                                   Vec3 viewPosition, Vec3 lightDirection)
{
  // TODO: Implement me (Sheet A09, Assignment 1)
}

void DrawTriangleZBufferBlinnPhongOptimized(PixelBuffer p, BoundingBox bb, fixed_t ax, fixed_t ay, fixed_t bx,
                                            fixed_t by, fixed_t cx, fixed_t cy, float z0, float z1, float z2,
                                            Vec3 aNormal, Vec3 bNormal, Vec3 cNormal, Vec3 aPos, Vec3 bPos, Vec3 cPos,
                                            Vec3 dColor, Vec3 sColor, float shinyness, Vec3 viewPosition,
                                            Vec3 lightDirection)
{
  // TODO: Implement me (Sheet A10, Assignments 7 and 8)
}
