#include <cgclib/sys/PixelBuffer.h>
#include <stdlib.h>
#include <string.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <cgclib/contrib/stb_image_write.h>
#define STB_IMAGE_IMPLEMENTATION
#include <cgclib/contrib/stb_image.h>

int32_t CreatePixelBuffer(PixelBuffer* pixelBuffer, int32_t width, int32_t height, bool ownsPixel)
{
    const int32_t maxWidth  = 4096;
    const int32_t maxHeight = 4096;
    if (pixelBuffer == NULL)
    {
        return 0;
    }
    if ((width < 0) || (width > maxWidth) || (height < 0) || (height > maxHeight))
    {
        return 0;
    }
    pixelBuffer->width  = width;
    pixelBuffer->height = height;

    pixelBuffer->zBuffer = malloc((size_t)pixelBuffer->width * pixelBuffer->height * sizeof(float));
    if (pixelBuffer->zBuffer == 0)
    {
        return 0;
    }

    pixelBuffer->pixels = 0;
    if (ownsPixel)
    {
        pixelBuffer->pixels = malloc((size_t)pixelBuffer->width * pixelBuffer->height * sizeof(uint32_t));
        if (pixelBuffer->pixels == 0)
        {
            free(pixelBuffer->zBuffer);
            pixelBuffer->zBuffer = 0;
            return 0;
        }
    }

    return 0;
}

void DestroyPixelBuffer(PixelBuffer* pixelBuffer, bool ownsPixel)
{
    if (pixelBuffer == NULL)
    {
        return;
    }

    pixelBuffer->width  = 0;
    pixelBuffer->height = 0;

    if (pixelBuffer->zBuffer != 0)
    {
        free(pixelBuffer->zBuffer);
        pixelBuffer->zBuffer = 0;
    }
    if (ownsPixel && (pixelBuffer->pixels != 0))
    {
        free(pixelBuffer->pixels);
        pixelBuffer->pixels = 0;
    }
}

void ClearColorBuffer(PixelBuffer p, uint32_t c)
{
    const auto nPixels = p.width * p.height;
    for (int32_t i = 0; i < nPixels; i++)
    {
        p.pixels[i] = c;
    }
}

void ClearZBuffer(PixelBuffer p, float z)
{
    const auto nPixels = p.width * p.height;
    for (int32_t i = 0; i < nPixels; i++)
    {
        p.zBuffer[i] = z;
    }
}

void SetZBufferToZero(PixelBuffer p)
{
    const auto nPixels = p.width * p.height;
    memset(p.zBuffer, 0, nPixels * sizeof(float));
}

int SavePixelBufferToFile(PixelBuffer p, const char* filename)
{
    uint8_t* rgbBuffer = (uint8_t*)malloc(p.width * p.height * 3);
    if (!rgbBuffer)
    {
        return 0;
    }
    for (int32_t i = 0; i < p.width * p.height; i++)
    {
        rgbBuffer[3 * i + 0] = (uint8_t)(p.pixels[i] >> 16);
        rgbBuffer[3 * i + 1] = (uint8_t)(p.pixels[i] >> 8);
        rgbBuffer[3 * i + 2] = (uint8_t)(p.pixels[i] >> 0);
    }
    stbi_flip_vertically_on_write(1);
    int result = stbi_write_png(filename, p.width, p.height, 3, rgbBuffer, p.width * 3);
    free(rgbBuffer);
    return result;
}

int ComparePixelBufferToFile(PixelBuffer p, const char* referenceFileName, const char* pixelBufferFileName,
                             const char* diffImageFileName, ComparePixelBufferResult* mismatchResult,
                             bool createReference)
{
    if (createReference)
    {
        if (!SavePixelBufferToFile(p, referenceFileName))
        {
            return 0;
        }
    }

    if (mismatchResult == NULL)
    {
        return 1;
    }

    mismatchResult->WidthMismatch  = true;
    mismatchResult->HeightMismatch = true;
    mismatchResult->PixelMismatch  = true;
    if (!SavePixelBufferToFile(p, pixelBufferFileName))
    {
        return 0;
    }

    int refImWidth = 0, refImHeight = 0, c = 0;
    stbi_set_flip_vertically_on_load(1);
    stbi_uc* referenceImage = stbi_load(referenceFileName, &refImWidth, &refImHeight, &c, 3);
    if (referenceImage == 0)
    {
        return 0;
    }
    mismatchResult->WidthMismatch  = refImWidth != p.width;
    mismatchResult->HeightMismatch = refImHeight != p.height;

    if (refImWidth == 0 || refImHeight == 0)
    {
        return 0;
    }
    uint32_t diffImgWidth  = MIN(p.width, refImWidth);
    uint32_t diffImgHeight = MIN(p.height, refImHeight);
    uint32_t nPixels       = diffImgWidth * diffImgHeight;

    uint8_t* diffImage = (uint8_t*)malloc(nPixels * 3);
    if (!diffImage)
    {
        return 0;
    }

    mismatchResult->PixelMismatch = false;
    for (uint32_t y = 0; y < diffImgHeight; y++)
        for (uint32_t x = 0; x < diffImgWidth; x++)
        {
            bool r = (uint8_t)(p.pixels[y * p.width + x] >> 16) != referenceImage[(y * refImWidth + x) * 3 + 0];
            bool g = (uint8_t)(p.pixels[y * p.width + x] >> 8) != referenceImage[(y * refImWidth + x) * 3 + 1];
            bool b = (uint8_t)(p.pixels[y * p.width + x] >> 0) != referenceImage[(y * refImWidth + x) * 3 + 2];

            mismatchResult->PixelMismatch |= r;
            mismatchResult->PixelMismatch |= g;
            mismatchResult->PixelMismatch |= b;

            diffImage[(y * diffImgWidth + x) * 3 + 0] = 255 * r;
            diffImage[(y * diffImgWidth + x) * 3 + 1] = 255 * g;
            diffImage[(y * diffImgWidth + x) * 3 + 2] = 255 * b;
        }
    stbi_flip_vertically_on_write(1);
    int result = stbi_write_png(diffImageFileName, diffImgWidth, diffImgHeight, 3, diffImage, diffImgWidth * 3);
    free(diffImage);
    return 1;
}
