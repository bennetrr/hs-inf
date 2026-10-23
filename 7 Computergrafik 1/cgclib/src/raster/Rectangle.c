#include <cgclib/raster/Rectangle.h>
#include <stdlib.h>

void DrawRectangle(PixelBuffer p, int32_t lowerLeftX, int32_t lowerLeftY, int32_t width, int32_t height, uint32_t color)
{
    const int32_t x = CLAMP(0, lowerLeftX, p.width);
    const int32_t y = CLAMP(0, lowerLeftY, p.height);
    const int32_t w = CLAMP(0, width, p.width - x);
    const int32_t h = CLAMP(0, height, p.height - y);

    for (int iX = x; iX < x + w; ++iX)
    {
        for (int iY = y; iY < y + h; ++iY)
        {
            SetPixelBufferPixel(p, iX, iY, color);
        }
    }
}
