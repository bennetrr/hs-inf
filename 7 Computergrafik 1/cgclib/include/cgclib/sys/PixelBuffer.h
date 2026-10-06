#ifndef PIXELBUFFER_H
#define PIXELBUFFER_H
#include <cgclib/sys/Util.h>
#include <stdbool.h>
#include <stdint.h>


/**
 * @brief Represents a pixel buffer used for rendering, including color and depth information.
 */
typedef struct PixelBuffer
{
  uint32_t* pixels;
  float*    zBuffer;
  int32_t   width;
  int32_t   height;
  float     time;
} PixelBuffer;

/**
 * @brief Creates a 32-bit ARGB color from red, green, and blue components.
 *
 * Ensures that each component is clamped to a maximum of 255.
 *
 * @param r Red component (0–255)
 * @param g Green component (0–255)
 * @param b Blue component (0–255)
 * @return uint32_t ARGB color value
 */
static inline uint32_t Color(uint32_t r, uint32_t g, uint32_t b)
{
  return 0xff000000 | ((MIN((r), 255)) << 16) | ((MIN((g), 255)) << 8) | (MIN((b), 255));
}

/**
 * @brief Computes the Pixel Offset.
 *
 * Does not perform clipping.
 *
 * @param pixelBuffer Pointer to the PixelBuffer structure.
 * @param x X-coordinate of the pixel.
 * @param y Y-coordinate of the pixel.
 * @return int32_t Pixel-Offset in PixelBuffer.pixels.
 *
 */
static inline int32_t ComputePixelOffset(PixelBuffer p, int32_t x, int32_t y)
{
  return y * p.width + x;
}

/**
 * @brief Sets a pixel.
 *
 * Does not perform clipping. x and y outside the view buffer results in undefined behaviour.
 *
 * @param pixelBuffer Pointer to the PixelBuffer structure.
 * @param x X-coordinate of the pixel.
 * @param y Y-coordinate of the pixel.
 * @param color Color of the pixel.
 *
 */
static inline void SetPixelBufferPixel(PixelBuffer p, int32_t x, int32_t y, uint32_t color)
{
  p.pixels[ComputePixelOffset(p, x, y)] = color;
}

/**
 * @brief Get the color value of  a pixel.
 *
 * Does not perform clipping. x and y outside the view buffer results in undefined behaviour.
 *
 * @param pixelBuffer Pointer to the PixelBuffer structure.
 * @param x X-coordinate of the pixel.
 * @param y Y-coordinate of the pixel.
 * @return uint32_t Color of the pixel.
 *
 */
static inline uint32_t GetPixelBufferPixel(PixelBuffer p, int32_t x, int32_t y)
{
  return p.pixels[ComputePixelOffset(p, x, y)];
}

/**
 * @brief Converts a floating-point value to an 8-bit color component.
 *
 * @param y Value in range [0.0, 1.0]
 * @return uint32_t Corresponding 8-bit color component (0–255)
 */
static inline uint32_t ToColorComponent(float y)
{
  return (uint32_t)(y * 255.0f + 0.5f);
}

/**
 * @brief Allocates memory and initializes a pixel buffer.
 *
 * @param pixelBuffer Pointer to the PixelBuffer structure to initialize.
 * @param width Width of the buffer in pixels.
 * @param height Height of the buffer in pixels.
 * @param ownsPixels If true, the PixelBuffer will manage (free) the pixel memory.
 * @return int32_t Status code (0 for success, non-zero for failure).
 */
int32_t CreatePixelBuffer(PixelBuffer* pixelBuffer, int32_t width, int32_t height, bool ownsPixel);

/**
 * @brief Frees memory associated with a pixel buffer.
 *
 * @param pixelBuffer Pointer to the PixelBuffer structure to destroy.
 * @param ownsPixels If true, the PixelBuffer will manage (free) the pixel memory.

 */
void DestroyPixelBuffer(PixelBuffer* pixelBuffer, bool ownsPixel);

/**
 * @brief Clears the color buffer to a specified color.
 *
 * @param p PixelBuffer to clear.
 * @param c Color value to fill (ARGB format).
 */
void ClearColorBuffer(PixelBuffer p, uint32_t c);

/**
 * @brief Clears the Z-buffer to a specified depth value.
 *
 * @param p PixelBuffer to clear.
 * @param z Depth value to set.
 */
void ClearZBuffer(PixelBuffer p, float z);

/**
 * @brief Sets all Z-buffer values to zero.
 *
 * @param p PixelBuffer whose Z Buffer should be cleared.
 */
void SetZBufferToZero(PixelBuffer p);

/**
 * @brief Saves the color buffer of a screen buffer to a png file.
 *
 * @param p PixelBuffer whose color buffer should be written.
 * @param filename const char* Filename of the image
 * 
 * @return 0 on failure, non-zero on success.
 */
int SavePixelBufferToFile(PixelBuffer p, const char* filename);



typedef struct
{
  bool WidthMismatch;
  bool HeightMismatch;
  bool PixelMismatch;
} ComparePixelBufferResult;

/**
 * @brief Compares a PixelBuffer against a reference image file.
 *
 * This function compares the contents of a given PixelBuffer p to a reference image
 * specified by referenceFileName. It saves the PixelBuffer to a file
 * (pixelBufferFileName) and generates a diff image (diffImageFileName) 
 * It reports mismatches in width, height, and pixel data.
 *
 * @param p The PixelBuffer to compare.
 * @param referenceFileName Path to the reference image file.
 * @param pixelBufferFileName Path to save the PixelBuffer image.
 * @param diffImageFileName Path to save the diff image highlighting differences.
 * @param mismatchResult Pointer to a struct that gives fine difference results.
 * @param createReference True, if you want to create the reference
 * @return 0 on error.
 */
int ComparePixelBufferToFile(PixelBuffer p, 
	const char* referenceFileName, 
	const char* pixelBufferFileName,                              
	const char* diffImageFileName, ComparePixelBufferResult* mismatchResult,
	bool createReference);
	

#endif
