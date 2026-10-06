#define _USE_MATH_DEFINES
#include <cgclib/sys/CGWindow.h>
#include <cgclib/io/SimpleMesh.h>
#include "Render2DMesh.h"

int main()
{
  CGWindow cgwindow = {0};
  CreateCGWindow(&cgwindow, 512, 512, "Mesh2D", &RenderScene);
  LoadSimpleMeshIO("../../../data/lion.smm", &mesh);
  RunCGWindow(&cgwindow);
  DestroyCGWindow(&cgwindow);
  return 0;
}
