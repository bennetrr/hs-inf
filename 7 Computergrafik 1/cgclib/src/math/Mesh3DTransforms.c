#include <cgclib/math/Mesh3DTransforms.h>
#include <cgclib/math/Transforms.h>
#include <cgclib/math/Vec3.h>
#include <math.h>

Mat4 ModelTransform(float alpha)
{
  Mat4 modelTransform = SetIdentity();
  // TODO: Implement me (Sheet A04, Assignment 4.1)
  modelTransform = (Mat4){1.00000000, 0.00000000, 0.00000000, 0.00000000, 0.00000000, 1.00000000, 0.00000000, 0.00000000,
                          0.00000000, 0.00000000, 1.00000000, -3.7000000, 0.00000000, 0.00000000, 0.00000000, 1.00000000};
  return modelTransform;
}

Mat4 ProjectionTransform(PixelBuffer p)
{
  // TODO: Implement me (Sheet A04, Assignment 4.2)
  Mat4 projectionTransform = {2.41421342, 0.00000000, 0.00000000,  0.00000000, 0.00000000,  2.41421342,
                              0.00000000, 0.00000000, 0.00000000,  0.00000000, -1.00121284, -0.0200121272,
                              0.00000000, 0.00000000, -1.00000000, 0.00000000};
  return projectionTransform;
}

Mat4 WindowTransform(PixelBuffer p)
{
  // TODO: Implement me (Sheet A04, Assignment 4.3)
  Mat4 windowTransform = {256.000000, 0.00000000, 0.00000000, 256.000000, 0.00000000, 256.000000,
                          0.00000000, 256.000000, 0.00000000, 0.00000000, 1.00000000, 0.00000000,
                          0.00000000, 0.00000000, 0.00000000, 1.00000000};

  return windowTransform;
}
