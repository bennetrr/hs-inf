#define _USE_MATH_DEFINES
#include <assert.h>
#include <cgclib/raster/Circle.h>
#include <cgclib/raster/Rectangle.h>
#include <cgclib/sys/CGWindow.h>
#include <math.h>
#include <stdio.h>

static int32_t RenderScene(PixelBuffer p)
{
    ClearColorBuffer(p, Color(32, 32, 32));

    DrawRectangle(p, 10, 50, 100, 200, Color(255, 255, 0));
    DrawRectangle(p, 50, 200, 200, 100, Color(0, 255, 255));
    DrawCircle(p, p.width / 2, p.height / 2, MIN(p.width / 4, p.height / 4), Color(0, 0, 0));
    return 1;
}

int main()
{
    CGWindow cgwindow = { 0 };
    CreateCGWindow(&cgwindow, 512, 512, "BasicRaster", &RenderScene);
    RunCGWindow(&cgwindow);
    ComparePixelBufferResult r;
    ComparePixelBufferToFile(cgwindow.pixelBuffer, "../../../labs/A01BasicRaster/Reference.png", "StudentAnswer.png",
                             "Difference.png", &r, false);
    DestroyCGWindow(&cgwindow);
    printf("Width: %s\n", !r.WidthMismatch ? "PASS" : "FAIL");
    printf("Height: %s\n", !r.HeightMismatch ? "PASS" : "FAIL");
    printf("Pixels: %s\n", !r.PixelMismatch ? "PASS" : "FAIL");
    return 0;
}
