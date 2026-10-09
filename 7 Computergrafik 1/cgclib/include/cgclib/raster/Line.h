#ifndef LINE_H
#define LINE_H
#include <cgclib/sys/PixelBuffer.h>
#include <stdint.h>

/**
 * @brief Draws a line on a pixel buffer using an efficient integer-based algorithm.
 *
 * This function performs clipping to discard lines that fall outside the buffer.
 * It uses a modified Bresenham-like approach to rasterize lines in either horizontal or vertical dominant direction.
 *
 * @param p Pixel buffer to draw on.
 * @param x0 Starting x-coordinate.
 * @param y0 Starting y-coordinate.
 * @param x1 Ending x-coordinate.
 * @param y1 Ending y-coordinate.
 * @param color Color value to write to the buffer.
 */
void DrawLine(PixelBuffer p, int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t color);

#endif
