#define _USE_MATH_DEFINES
#include "Render3DMeshGouraudShading.h"
#include <cgclib/io/SimpleMesh.h>
#include <cgclib/sys/CGWindow.h>

int main()
{
  CGWindow cgwindow = {0};
  CreateCGWindow(&cgwindow, 512, 512, "Gouraud Shading", &RenderScene);
  LoadSimpleMeshIO("../../../data/Sphere3.smm", &mesh);  
  RunCGWindow(&cgwindow);
  DestroyCGWindow(&cgwindow);
  return 0;
}
