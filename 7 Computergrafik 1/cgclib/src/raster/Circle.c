#include <cgclib/raster/Circle.h>

#include <stdio.h>
#include <stdlib.h>

static void DrawHLine(PixelBuffer p, int32_t x0, int32_t x1, int32_t y, uint32_t color)
{
    if (y < 0 || y >= p.height)
    {
        return;
    }

    x0 = CLAMP(0, x0, p.width - 1);
    x1 = CLAMP(0, x1, p.width - 1);

    for (int32_t x = x0; x <= x1; ++x)
    {
        SetPixelBufferPixel(p, x, y, color);
    }
}

void DrawCircle(PixelBuffer p, int32_t cx, int32_t cy, int32_t r, uint32_t color)
{
    if (r <= 0)
    {
        return;
    }

    int32_t w = r; // halbe Breite der aktuellen Zeile
    for (int32_t dy = 0; dy < r; ++dy)
    {
        // größtes w mit w² + dy² < r²
        while (w * w + dy * dy >= r * r)
        {
            --w;
        }

        DrawHLine(p, cx - w, cx + w, cy + dy, color);
        if (dy != 0)
        {
            DrawHLine(p, cx - w, cx + w, cy - dy, color);
        }
    }
}
