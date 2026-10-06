#ifndef RENDER3DMESHFLATZBUFFER_H
#define RENDER3DMESHFLATZBUFFER_H

#include <assert.h>
#include <cgclib/io/SimpleMesh.h>
#include <cgclib/math/FixedPoint.h>
#include <cgclib/math/Lighting.h>
#include <cgclib/math/Mat4.h>
#include <cgclib/math/Vec3.h>
#include <cgclib/math/Mesh3DTransforms.h>
#include <cgclib/raster/Triangle.h>

#include <math.h>

SimpleMesh mesh = {0};

#ifdef WIN32
#include <omp.h>
#endif

void Render3DMeshPhong(PixelBuffer p, Mat4 windowTransform, Mat4 projectionTransform, Mat4 modelTransform,
                       Vec3 lightDirection, Vec3 viewPosition, Vec3 dColor, Vec3 sColor, float shinyness)
{
// TODO: Implement me (Sheet A10, Assignment 2)
}

static int32_t RenderScene(PixelBuffer p)
{
  ClearColorBuffer(p, Color(255, 255, 255));
// TODO: Implement me (Sheet A10, Assignment 2)
  float alpha               = p.time * 0.1f / 180.0f * (float)M_PI;
  Mat4  modelTransform      = ModelTransform(alpha);
  Mat4  projectionTransform = ProjectionTransform(p);
  Mat4  windowTransform     = WindowTransform(p);

  Vec3 lightDirection = {0, 0, 1};
  lightDirection      = Normalize(lightDirection);


  Vec3  viewPosition = {0, 0, 0};
  Vec3  dColor       = {1, 0, 0};
  Vec3  sColor       = {1, 1, 1};
  float shinyness    = 128.0f;

  Render3DMeshPhong(p, windowTransform, projectionTransform, modelTransform, lightDirection, viewPosition, dColor,
                    sColor, shinyness);

  return 1;
}
#endif
