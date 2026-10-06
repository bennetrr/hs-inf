#ifndef RECTANGLE_H
#define RECTANGLE_H
#include <stdint.h>
#include <cgclib/sys/PixelBuffer.h>

/**
 * @brief Draws a filled rectangle onto a pixel buffer.
 *
 * The rectangle is clipped to the bounds of the pixel buffer to prevent out-of-bounds access.
 * It starts from the lower-left corner and fills a region of the specified width and height.
 *
 * @param p Pixel buffer to draw on.
 * @param lowerLeftX X-coordinate of the rectangle's lower-left corner.
 * @param lowerLeftY Y-coordinate of the rectangle's lower-left corner.
 * @param width Width of the rectangle in pixels.
 * @param height Height of the rectangle in pixels.
 * @param color Color value to fill the rectangle with.
 */
void DrawRectangle(PixelBuffer p, int32_t lowerLeftX, int32_t lowerLeftY, int32_t width, int32_t height,
                   uint32_t color);
#endif
