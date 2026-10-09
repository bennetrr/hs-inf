#ifndef ELLIPSIS_H
#define ELLIPSIS_H
#include <cgclib/sys/PixelBuffer.h>
#include <stdint.h>

/**
 * @brief Draws a filled circle onto a pixel buffer.
 *
 * The function rasterizes a circular region centered at (centerX, centerY) with the given radius.
 * Pixels outside the buffer bounds are culled, and only those within the circle are colored.
 *
 * @param p Pixel buffer to draw on.
 * @param centerX X-coordinate of the circle center.
 * @param centerY Y-coordinate of the circle center.
 * @param radius Radius of the circle (must be non-negative).
 * @param color Color value to apply to pixels inside the circle.
 */
void DrawCircle(PixelBuffer p, int32_t centerX, int32_t centerY, int32_t radius, uint32_t color);
#endif
