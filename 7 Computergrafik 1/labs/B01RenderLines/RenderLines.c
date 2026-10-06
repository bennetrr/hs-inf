#define _USE_MATH_DEFINES
#include <assert.h>
#include <cgclib/io/SimpleMesh.h>
#include <cgclib/math/FixedPoint.h>
#include <cgclib/math/Mat4.h>
#include <cgclib/math/Transforms.h>
#include <cgclib/math/Vec3.h>
#include <cgclib/raster/Line.h>
#include <cgclib/sys/CGWindow.h>
#include <math.h>

SimpleMesh mesh = { 0 };

void Render3DMeshLines(PixelBuffer p, Mat4 ndcTransform)
{
    // TODO: Implement me (Sheet B01)
}

static int32_t RenderScene(PixelBuffer p)
{
    ClearColorBuffer(p, Color(255, 255, 255));

    float alpha = p.time * 0.1f / 180.0f * (float)M_PI;
    // TODO: Implement me (Sheet B01)
    Mat4 modelTransform  = { 0 };
    Mat4 windowTransform = { 0 };
    Mat4 projection3D    = { 0 };
    Mat4 ndcTransform    = { 0 };
    Render3DMeshLines(p, ndcTransform);

    return 1;
}

int main()
{
    CGWindow cgwindow = { 0 };
    CreateCGWindow(&cgwindow, 512, 512, "A3Mesh2D", &RenderScene);
    LoadSimpleMeshIO("../../../data/bunny.smm", &mesh);
    RunCGWindow(&cgwindow);
    DestroyCGWindow(&cgwindow);
    return 0;
}
