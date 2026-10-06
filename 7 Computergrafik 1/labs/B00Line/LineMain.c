#define _USE_MATH_DEFINES
#include <cgclib/raster/Line.h>
#include <cgclib/sys/CGWindow.h>
#include <math.h>

static int32_t RenderScene(PixelBuffer p)
{
    ClearColorBuffer(p, Color(32, 32, 32));
    for (float a = 0; a <= 2 * M_PI; a += 0.5f)
    {
        float cx = p.width * 0.5f;
        float cy = p.height * 0.5f;
        float r  = (sinf(fmodf(p.time * 0.001f, 2.0f * (float)M_PI)) + 1.0f) * 0.5f * 120.0f;
        float x  = cosf(a + p.time * 0.0005f);
        float y  = sinf(a + p.time * 0.0005f);
        DrawLine(p, (int32_t)roundf(cx), (int32_t)roundf(cy), (int32_t)roundf(cx + r * x), (int32_t)roundf(cy + r * y),
                 Color(255, 0, 255));
    }
    return 1;
}

int main()
{
    CGWindow cgwindow = { 0 };
    CreateCGWindow(&cgwindow, 512, 512, "A1Line", &RenderScene);
    RunCGWindow(&cgwindow);
    DestroyCGWindow(&cgwindow);
    return 0;
}
