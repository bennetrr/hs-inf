#ifndef RENDER3DMESHPHONGSHADING_H
#define RENDER3DMESHPHONGSHADING_H

#include <assert.h>
#include <cgclib/io/SimpleMesh.h>
#include <cgclib/math/FixedPoint.h>
#include <cgclib/math/Lighting.h>
#include <cgclib/math/Mat4.h>
#include <cgclib/math/Mesh3DTransforms.h>
#include <cgclib/math/Vec3.h>
#include <cgclib/raster/Triangle.h>

#include <math.h>

SimpleMesh mesh = {0};

void Render3DMeshPhong(PixelBuffer p, Mat4 windowTransform, Mat4 projectionTransform, Mat4 modelTransform,
                       Vec3 lightDirection, Vec3 viewPosition, Vec3 diffuseColor, Vec3 specularColor, float shinyness)
{
// TODO: Implement me (Sheet A09, Assignment 1)
}

static int32_t RenderScene(PixelBuffer p)
{
  ClearColorBuffer(p, Color(255, 255, 255));
// TODO: Implement me (Sheet A09, Assignment 1)
  float alpha = p.time * 0.1f / 180.0f * (float)M_PI;

  Mat4 modelTransform      = ModelTransform(alpha);
  Mat4 projectionTransform = ProjectionTransform(p);
  Mat4 windowTransform     = WindowTransform(p);

  Vec3 lightDirection = {0, 0, 1};
  lightDirection      = Normalize(lightDirection);

  Vec3  viewPosition  = {0, 0, 0};
  Vec3  diffuseColor  = {1, 0, 0};
  Vec3  specularColor = {1, 1, 1};
  float shinyness     = 128.0f;

  Render3DMeshPhong(p, windowTransform, projectionTransform, modelTransform, lightDirection, viewPosition, diffuseColor,
                    specularColor, shinyness);

  return 1;
}

#endif
