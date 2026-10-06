#ifndef MESH3DTRANSFORMS_H
#define MESH3DTRANSFORMS_H
#include <cgclib/math/Mat4.h>
#include <cgclib/sys/PixelBuffer.h>

Mat4 ModelTransform(float alpha);

Mat4 ProjectionTransform(PixelBuffer p);

Mat4 WindowTransform(PixelBuffer p);
#endif
