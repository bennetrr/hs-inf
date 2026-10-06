#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <cgclib/math/FixedPoint.h>
#include <cgclib/math/Vec3.h>
#include <cgclib/raster/TriangleCull.h>
#include <cgclib/sys/PixelBuffer.h>
#include <stdint.h>

/**
 * @brief Rasterizes a filled triangle with a flat (uniform) color.
 *
 * Uses fixed-point coordinates and line equations to determine pixel coverage.
 * Only pixels inside the triangle are shaded with the given color.
 *
 * @param p Pixel buffer to draw on.
 * @param ax Fixed-point X-coordinate of vertex A.
 * @param ay Fixed-point Y-coordinate of vertex A.
 * @param bx Fixed-point X-coordinate of vertex B.
 * @param by Fixed-point Y-coordinate of vertex B.
 * @param cx Fixed-point X-coordinate of vertex C.
 * @param cy Fixed-point Y-coordinate of vertex C.
 * @param color RGB color to fill the triangle with.
 */
void DrawTriangleFlat(PixelBuffer p, fixed_t ax, fixed_t ay, fixed_t bx, fixed_t by, fixed_t cx, fixed_t cy,
                      Vec3 color);

/**
 * @brief Rasterizes a filled triangle with a flat (uniform) color.
 *
 * Uses floating-point coordinates and line equations to determine pixel coverage.
 * Only pixels inside the triangle are shaded with the given color.
 *
 * @param p Pixel buffer to draw on.
 * @param ax X-coordinate of vertex A.
 * @param ay Y-coordinate of vertex A.
 * @param bx X-coordinate of vertex B.
 * @param by Y-coordinate of vertex B.
 * @param cx X-coordinate of vertex C.
 * @param cy Y-coordinate of vertex C.
 * @param color RGB color to fill the triangle with.
 */
void DrawTriangleFlatFloat(PixelBuffer p, float ax, float ay, float bx, float by, float cx, float cy, Vec3 color);

/**
 * @brief Rasterizes a filled triangle with Gouraud shading (vertex color interpolation).
 *
 * Uses fixed-point coordinates and barycentric interpolation to blend vertex colors across the triangle surface.
 *
 * @param p Pixel buffer to draw on.
 * @param ax Fixed-point X-coordinate of vertex A.
 * @param ay Fixed-point Y-coordinate of vertex A.
 * @param bx Fixed-point X-coordinate of vertex B.
 * @param by Fixed-point Y-coordinate of vertex B.
 * @param cx Fixed-point X-coordinate of vertex C.
 * @param cy Fixed-point Y-coordinate of vertex C.
 * @param aColor Color at vertex A.
 * @param bColor Color at vertex B.
 * @param cColor Color at vertex C.
 */
void DrawTriangleGouraud(PixelBuffer p, fixed_t ax, fixed_t ay, fixed_t bx, fixed_t by, fixed_t cx, fixed_t cy,
                         Vec3 aColor, Vec3 bColor, Vec3 cColor);

/**
 * @brief Rasterizes a triangle with flat shading and Z-buffer depth testing.
 *
 * Uses fixed-point coordinates and barycentric interpolation to compute depth (Z) per pixel.
 * Only pixels passing the depth test are shaded with the uniform color.
 *
 * @param p Pixel buffer containing color and Z-buffer.
 * @param ax Fixed-point X-coordinate of vertex A.
 * @param ay Fixed-point Y-coordinate of vertex A.
 * @param bx Fixed-point X-coordinate of vertex B.
 * @param by Fixed-point Y-coordinate of vertex B.
 * @param cx Fixed-point X-coordinate of vertex C.
 * @param cy Fixed-point Y-coordinate of vertex C.
 * @param z0 Depth value at vertex A.
 * @param z1 Depth value at vertex B.
 * @param z2 Depth value at vertex C.
 * @param color Flat RGB color to fill the triangle.
 */
void DrawTriangleZBufferFlat(PixelBuffer p, fixed_t ax, fixed_t ay, fixed_t bx, fixed_t by, fixed_t cx, fixed_t cy,
                             float z0, float z1, float z2, Vec3 color);

/**
 * @brief Rasterizes a triangle with Gouraud shading and Z-buffer depth testing.
 *
 * Uses fixed-point coordinates and barycentric interpolation to compute both depth (Z) and color per pixel.
 * Only pixels passing the depth test are shaded with interpolated vertex color.
 *
 * @param p Pixel buffer containing color and Z-buffer.
 * @param ax Fixed-point X-coordinate of vertex A.
 * @param ay Fixed-point Y-coordinate of vertex A.
 * @param bx Fixed-point X-coordinate of vertex B.
 * @param by Fixed-point Y-coordinate of vertex B.
 * @param cx Fixed-point X-coordinate of vertex C.
 * @param cy Fixed-point Y-coordinate of vertex C.
 * @param z0 Depth value at vertex A.
 * @param z1 Depth value at vertex B.
 * @param z2 Depth value at vertex C.
 * @param aColor Color at vertex A.
 * @param bColor Color at vertex B.
 * @param cColor Color at vertex C.
 */
void DrawTriangleZBufferGouraud(PixelBuffer p, fixed_t ax, fixed_t ay, fixed_t bx, fixed_t by, fixed_t cx, fixed_t cy,
                                float z0, float z1, float z2, Vec3 aColor, Vec3 bColor, Vec3 cColor);

/**
 * @brief Rasterizes a triangle using Z-buffering and Blinn-Phong lighting.
 *
 * This function performs per-pixel lighting using interpolated normals and positions.
 *
 * @param p Pixel buffer to render into.
 * @param ax X-coordinate of vertex A (fixed-point).
 * @param ay Y-coordinate of vertex A (fixed-point).
 * @param bx X-coordinate of vertex B (fixed-point).
 * @param by Y-coordinate of vertex B (fixed-point).
 * @param cx X-coordinate of vertex C (fixed-point).
 * @param cy Y-coordinate of vertex C (fixed-point).
 * @param z0 Depth value at vertex A.
 * @param z1 Depth value at vertex B.
 * @param z2 Depth value at vertex C.
 * @param aNormal Normal vector at vertex A.
 * @param bNormal Normal vector at vertex B.
 * @param cNormal Normal vector at vertex C.
 * @param aPos World-space position of vertex A.
 * @param bPos World-space position of vertex B.
 * @param cPos World-space position of vertex C.
 * @param dColor Diffuse color of the material.
 * @param sColor Specular color of the material.
 * @param shinyness Shininess factor for specular highlights.
 * @param viewPosition Position of the camera/viewer in world space.
 * @param lightDirection Direction of the incoming light (normalized).
 */
void DrawTriangleZBufferBlinnPhong(PixelBuffer p, fixed_t ax, fixed_t ay, fixed_t bx, fixed_t by, fixed_t cx,
                                   fixed_t cy, float z0, float z1, float z2, Vec3 aNormal, Vec3 bNormal, Vec3 cNormal,
                                   Vec3 aPos, Vec3 bPos, Vec3 cPos, Vec3 dColor, Vec3 sColor, float shinyness,
                                   Vec3 viewPosition, Vec3 lightDirection);

/**
 * @brief Rasterizes a triangle using Z-buffering and Blinn-Phong lighting.
 *
 * This function performs per-pixel lighting using interpolated normals and positions.
 * It uses a bounding box to limit the rasterization area and applies depth testing
 * before writing to the pixel buffer. While the bounding box could be computed
 * inside this function, in many situations, the caller of the function has already
 * computed it for other optimizations.
 *
 * @param p Pixel buffer to render into.
 * @param b Bounding box that encloses the triangle.
 * @param ax X-coordinate of vertex A (fixed-point).
 * @param ay Y-coordinate of vertex A (fixed-point).
 * @param bx X-coordinate of vertex B (fixed-point).
 * @param by Y-coordinate of vertex B (fixed-point).
 * @param cx X-coordinate of vertex C (fixed-point).
 * @param cy Y-coordinate of vertex C (fixed-point).
 * @param z0 Depth value at vertex A.
 * @param z1 Depth value at vertex B.
 * @param z2 Depth value at vertex C.
 * @param aNormal Normal vector at vertex A.
 * @param bNormal Normal vector at vertex B.
 * @param cNormal Normal vector at vertex C.
 * @param aPos World-space position of vertex A.
 * @param bPos World-space position of vertex B.
 * @param cPos World-space position of vertex C.
 * @param dColor Diffuse color of the material.
 * @param sColor Specular color of the material.
 * @param shinyness Shininess factor for specular highlights.
 * @param viewPosition Position of the camera/viewer in world space.
 * @param lightDirection Direction of the incoming light (normalized).
 */
void DrawTriangleZBufferBlinnPhongOptimized(PixelBuffer p, BoundingBox b, fixed_t ax, fixed_t ay, fixed_t bx,
                                            fixed_t by, fixed_t cx, fixed_t cy, float z0, float z1, float z2,
                                            Vec3 aNormal, Vec3 bNormal, Vec3 cNormal, Vec3 aPos, Vec3 bPos, Vec3 cPos,
                                            Vec3 dColor, Vec3 sColor, float shinyness, Vec3 viewPosition,
                                            Vec3 lightDirection);

#ifdef WIN32
#include <intrin.h>
typedef union { float f; long l; } ZBits;
static inline bool ZTestAndSet(float* zBuf, int32_t ofs, float z)
{
  ZBits desired  = {z};
  ZBits expected = {zBuf[ofs]};
  while (expected.f > z)
  {
    ZBits prev;
    prev.l = _InterlockedCompareExchange((volatile long*)(zBuf + ofs), desired.l, expected.l);
    if (prev.l == expected.l) return true;
    expected.l = prev.l;
  }
  return false;
}
#endif

#endif
