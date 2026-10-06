#ifndef SIMPLEMESHMODELIO_H
#define SIMPLEMESHMODELIO_H
#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Represents a simple mesh structure for I/O operations.
 *
 * Stores triangle and vertex counts along with pointers to mesh attributes.
 */
typedef struct SimpleMesh
{
  uint32_t  numTriangles;			// Number of Triangles.
  uint32_t  numVertices;			// Number of Vertices.
  uint32_t* indices;				// Vertex indices. Tripelts of uint32_ts define a triangle, i.e., 
									// triangle i has the indices:
								    // indices[3 * i + 0], indices[3 * i + 1], indices[3 * i + 2].
  float*    positions;				// Positions. Triplets of floats define a position, i.e., 
									// position i has the coordiantes
									// positions[3 * i + 0], positions[3 * i + 1], positions[3 * i + 2].
  float*    colors;					// Colors. Triplets of floats define a normal, i.e., 
									// color i has the coordiantes
									// colors[3 * i + 0], colors[3 * i + 1], colors[3 * i + 2].
  float*    normals;				// Normals. Triplets of floats define a normal, i.e., 
									// normal i has the coordiantes
									// normals[3 * i + 0], normals[3 * i + 1], normals[3 * i + 2].
  float*    textureCoordinates;		// Texture coordinates. Pairs of floats define a texture coordinate, i.e.,
									// texture coordinate i has the coordinates
									// textureCoordinates[2 * i + 0], textureCoordinates[2 * i + 1].


} SimpleMesh;

/**
 * @brief Represents a simple mesh structure for I/O operations.
 *
 * Stores triangle and vertex counts along with pointers to mesh attributes.
 */
bool LoadSimpleMeshIO(const char* pathToFile, SimpleMesh* const simpleMesh);

/**
 * @brief Frees memory allocated for a SimpleMeshIO mesh.
 *
 * @param simpleMesh Pointer to the mesh structure to destroy.
 */
void DestroySimpleMeshIO(SimpleMesh* simpleMesh);

#endif
