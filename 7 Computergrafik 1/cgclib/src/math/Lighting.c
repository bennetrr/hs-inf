#include <cgclib/math/Lighting.h>
#include <cgclib/sys/Util.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdint.h>

Vec3 DiffuseLighting(Vec3 normal, Vec3 lightDirection, Vec3 color)
{
  // TODO: Implement me (Sheet A07, Assignment 1)
  return (Vec3) {0, 0, 0};
}

Vec3 BlinnLighting(Vec3 normal, Vec3 lightDirection, Vec3 viewDirection, Vec3 color, float shinyness)
{
  // TODO: Implement me (Sheet A07, Assignment 1)
  return (Vec3) {0, 0, 0};
}

Vec3 PhongLighting(Vec3 normal, Vec3 lightDirection, Vec3 viewDirection, Vec3 color, float shinyness)
{
  // TODO: Implement me (Sheet A07, Assignment 1)
  return (Vec3) {0, 0, 0};
}
