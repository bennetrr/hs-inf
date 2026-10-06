#define _USE_MATH_DEFINES
#include "Render3DMeshZBuffer.h"
#include <cgclib/io/SimpleMesh.h>
#include <cgclib/sys/CGWindow.h>

int main()
{
    CGWindow cgwindow = { 0 };
    CreateCGWindow(&cgwindow, 512, 512, "Mesh 3D ZBuffer", &RenderScene);
    LoadSimpleMeshIO("../../../data/bunny.smm", &mesh);
    RunCGWindow(&cgwindow);
    DestroyCGWindow(&cgwindow);
    return 0;
}
