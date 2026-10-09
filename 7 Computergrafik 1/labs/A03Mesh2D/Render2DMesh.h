#ifndef RENDER2DMESH_H
#define RENDER2DMESH_H
#include "Mesh2DTransforms.h"
#include <cgclib/io/SimpleMesh.h>
#include <cgclib/raster/Triangle.h>

static SimpleMesh mesh = { 0 };

static void Render2DMesh(PixelBuffer p, Mat4 ndcTransform)
{
    // TODO: Implement me (Sheet A03, Assignment 3)

    // 1. Iterate over the number of triangles. See SimpleMeshIO for details
    for (;;)
    {
        // 2. For each triangle, get the three indices.
        // Indices are stored in mesh.indices.
        // uint32_t i0 = ;
        // uint32_t i1 = ;
        // uint32_t i2 = ;

        // 3. For each vertex index, get the 3D vector position.
        // Vec3 p0 = ;
        // Vec3 p1 = ;
        // Vec3 p2 = ;

        // 4. Transform them to ndc with ndcTransform and a meaningful matrix vector transform.
        // p0 = ;
        // p1 = ;
        // p2 = ;

        // 5. Convert the NDCs from float to fixed point
        // fixed_t p0x = ;
        // fixed_t p0y = ;
        // fixed_t p1x = ;
        // fixed_t p1y = ;
        // fixed_t p2x = ;
        // fixed_t p2y = ;

        // 6. The color is stored in the array mesh.colors for i0.
        // Vec3 color = ;

        // 7. Now draw the triangle with DrawTriangleFlat
    }
}

static int32_t RenderScene(PixelBuffer p)
{
    ClearColorBuffer(p, Color(255, 255, 255));
    // TODO: Compute this instead of using hardcoded values (Sheet A03, Assignment 5)
    Mat4 modelToWindow = { 256, 0, 0, 384, 0, 256, 0, 256, 0, 0, 1, 0, 0, 0, 0, 1 };
    Render2DMesh(p, modelToWindow);
    return 1;
}

#endif
