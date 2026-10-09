#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <cgclib/math/Vec3.h>

/**
 * @brief Computes per-vertex normals for a 3D mesh.
 *
 * This function calculates normals for each vertex in a mesh based on the
 * positions of the vertices and the triangle indices.
 *
 * @param normals      Output array of size numVertices.
 *                     Each entry will be filled with the computed normal vector
 *                     for the corresponding vertex. It is in the callers
 *					   responsibility to make sure that at least numVertices
 *					   normals can be stored in this array.
 *
 * @param positions    Input array of size numVertices.
 *                     Contains the 3D coordinates (x, y, z) of each vertex.
 *
 * @param indices      Input array of size numTriangles * 3.
 *                     Each consecutive triplet defines a triangle by indexing
 *                     into the positions array.
 *
 * @param numVertices  Number of vertices in the mesh.
 *
 * @param numTriangles Number of triangles in the mesh.
 *
 * @note The function typically works by:
 *       1. Iterating over each triangle.
 *       2. Computing the face normal using the cross product of two edges.
 *       3. Accumulating the face normal into each of the triangle's vertices.
 *       4. Normalizing all vertex normals at the end.
 */
void ComputeNormals(Vec3* normals, Vec3* positions, uint32_t* indices, uint32_t numVertices, uint32_t numTriangles);

#endif
