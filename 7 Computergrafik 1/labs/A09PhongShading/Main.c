#define _USE_MATH_DEFINES
#include "Render3DMeshPhongShading.h"
#include <cgclib/io/SimpleMesh.h>
#include <cgclib/sys/CGWindow.h>

int main()
{
    CGWindow cgwindow = { 0 };
    CreateCGWindow(&cgwindow, 512, 512, "Phong Shading", &RenderScene);
    LoadSimpleMeshIO("../../../data/Bunny.smm", &mesh);
    RunCGWindow(&cgwindow);
    DestroyCGWindow(&cgwindow);
    return 0;
}
