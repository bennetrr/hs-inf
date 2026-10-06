#ifndef MESH2DTRANSFORMS_H
#define MESH2DTRANSFORMS_H
#include <cgclib/math/Mat4.h>
#include <cgclib/math/Transforms.h>
#include <cgclib/math/Vec3.h>
#include <math.h>

Mat4 ObjectToCamera(float time)
{
  Mat4 modelTransform = SetIdentity();
  // TODO: Implement me (Sheet A03, Assignment 4.1)
  return modelTransform;
}

Mat4 ModelToWindow(uint32_t width, uint32_t height, float time)
{
  // TODO: Implement me (Sheet A03, Assignment 4.2)
  Mat4 ndcTransform = SetIdentity();
  return ndcTransform;
}
#endif
