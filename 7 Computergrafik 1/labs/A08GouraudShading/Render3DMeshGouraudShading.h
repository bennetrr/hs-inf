#ifndef RENDER3DMESHGOURAUDSHADING_H
#define RENDER3DMESHGOURAUDSHADING_H

#include <assert.h>
#include <cgclib/io/SimpleMesh.h>
#include <cgclib/math/FixedPoint.h>
#include <cgclib/math/Lighting.h>
#include <cgclib/math/Mat4.h>
#include <cgclib/math/Mesh3DTransforms.h>
#include <cgclib/math/Vec3.h>
#include <cgclib/raster/Triangle.h>

#include <math.h>

SimpleMesh mesh = { 0 };

void Render3DMeshGouraud(PixelBuffer p, Mat4 windowTransform, Mat4 projectionTransform, Mat4 modelTransform,
                         Vec3 lightDirection, Vec3 viewPosition, Vec3 diffuseColor, Vec3 specularColor, float shinyness)
{
    // TODO: Implement me (Sheet A08, Assignment 2)
    for (uint32_t tIdx = 0; tIdx < mesh.numTriangles; tIdx++)
    {
        // 1. Get vertex indices.

        // 2. Get the position in object space.

        // 3. Get the 3 normals in object space.

        // 4. Transform the 3 normals to view space

        // 5. Transform the 3 positions to view space

        // 6. Compute the 3 view direction vectors in view space.

        // 7. Compute the 3 diffuse lighting colors (DiffuseLighting)

        // 8. Compute the 3 specular lighting colors (BlinnLighting)

        // 9. Add the 3 diffuse to the 3 specular lighting colors.

        // 10. Transform the view-space positions (from step 5) to clip-space

        // 11. Transform the clip-space coordinates to normalized device coordinates.

        // 12. Compute the fixed-point 2d ndc coordinates.

        // 13. Rasterize the triangle (DrawTriangleZBufferGouraud)
    }
}

static int32_t RenderScene(PixelBuffer p)
{
    ClearColorBuffer(p, Color(255, 255, 255));
    // TODO: Implement me (Sheet A08, Assignment 2)
    float alpha               = p.time * 0.1f / 180.0f * (float)M_PI;
    Mat4  modelTransform      = ModelTransform(alpha);
    Mat4  projectionTransform = ProjectionTransform(p);
    Mat4  windowTransform     = WindowTransform(p);

    Vec3 lightDirection = { 0, 0, 1 };
    lightDirection      = Normalize(lightDirection);

    Vec3  viewPosition  = { 0, 0, 0 };
    Vec3  diffuseColor  = { 1, 0, 0 };
    Vec3  specularColor = { 1, 1, 1 };
    float shinyness     = 128.0f;
    Render3DMeshGouraud(p, windowTransform, projectionTransform, modelTransform, lightDirection, viewPosition,
                        diffuseColor, specularColor, shinyness);
    return 1;
}

#endif
