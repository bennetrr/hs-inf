#define _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#include "Render3DMeshOptimized.h"
#include <cgclib/io/SimpleMesh.h>
#include <cgclib/sys/CGWindow.h>

int main()
{
#ifdef WIN32
  omp_set_num_threads(omp_get_max_threads());
#endif
  CGWindow cgwindow = {0};
  CreateCGWindow(&cgwindow, 512, 512, "Optimized", &RenderScene);
  LoadSimpleMeshIO("../../../data/Bunny.smm", &mesh);

  RunCGWindow(&cgwindow);
  DestroyCGWindow(&cgwindow);

  return 0;
}
