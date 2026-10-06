#define _USE_MATH_DEFINES
#include <assert.h>
#include <cgclib/math/FixedPoint.h>
#include <cgclib/raster/Triangle.h>
#include <cgclib/sys/CGWindow.h>
#include <math.h>

static int32_t RenderScene(PixelBuffer p)
{
    ClearColorBuffer(p, Color(32, 32, 32));

    Vec3 color = { 0, 1, 0 };

    DrawTriangleFlat(p, FloatToFixed(p.width * 0.1f), FloatToFixed(p.height * 0.1f), FloatToFixed(p.width * 0.9f),
                     FloatToFixed(p.height * 0.2f), FloatToFixed(p.width * 0.2f), FloatToFixed(p.height * 0.8f), color);
    return 1;
}

int main()
{
    CGWindow cgwindow = { 0 };
    CreateCGWindow(&cgwindow, 512, 512, "Computergrafik HS Coburg", &RenderScene);
    RunCGWindow(&cgwindow);
    DestroyCGWindow(&cgwindow);
    return 0;
}
