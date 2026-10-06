#define _USE_MATH_DEFINES
#include <assert.h>
#include <cgclib/raster/Triangle.h>
#include <cgclib/sys/CGWindow.h>
#include <math.h>

static int32_t RenderScene(PixelBuffer p)
{
    ClearColorBuffer(p, Color(32, 32, 32));

    Vec3 aColor = { 1, 0, 1 };
    Vec3 bColor = { 1, 1, 0 };
    Vec3 cColor = { 0, 1, 1 };

    DrawTriangleGouraud(p, FloatToFixed(p.width * 0.1f), FloatToFixed(p.height * 0.1f), FloatToFixed(p.width * 0.9f),
                        FloatToFixed(p.height * 0.2f), FloatToFixed(p.width * 0.2f), FloatToFixed(p.height * 0.8f),
                        aColor, bColor, cColor);
    return 1;
}

int main()
{
    CGWindow cgwindow = { 0 };
    CreateCGWindow(&cgwindow, 512, 512, "Triangle Gouraud", &RenderScene);
    RunCGWindow(&cgwindow);
    DestroyCGWindow(&cgwindow);
    return 0;
}
