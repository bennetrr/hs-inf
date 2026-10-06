#include <cgclib/io/SimpleMesh.h>
#include <stdio.h>
#include <stdlib.h>

bool AllocAndRead(void** buffer, size_t elementSize, size_t elementCount, FILE* file)
{
  *buffer = malloc(elementSize * elementCount);
  if (NULL == *buffer)
  {
    return false;
  }
  if (fread(*buffer, elementSize, elementCount, file) != elementCount)
  {
    return false;
  }
  return true;
}

bool AllocAndReadIfExists(void** buffer, size_t elementSize, size_t elementCount, FILE* file)
{
  int hasAttribute = 0;
  {
    if (1 != fread(&hasAttribute, sizeof(uint32_t), 1, file))
    {
      return false;
    }
  }
  if (hasAttribute == 1)
  {
    return AllocAndRead(buffer, elementSize, elementCount, file);
  }
  return true;
}

bool OnError(const char* errorMessage, SimpleMesh* const simpleMesh, FILE* file)
{
  perror(errorMessage);
  DestroySimpleMeshIO(simpleMesh);
  fclose(file);
  return false;
}

bool LoadSimpleMeshIO(const char* pathToFile, SimpleMesh* const simpleMesh)
{

  if (NULL == simpleMesh)
  {
    perror("Simple Mesh must no be NULL.\n");
    return false;
  }

  DestroySimpleMeshIO(simpleMesh);

  // Open File
  FILE* file = fopen(pathToFile, "rb");
  if (NULL == file)
  {
    perror("Error opening SMM file.\n");
    return false;
  }

  // Read number of triangles.
  {
    if (1 != fread(&simpleMesh->numTriangles, sizeof(uint32_t), 1, file))
    {
      return OnError("Error reading number of triangles.\n", simpleMesh, file);
    }
  }

  // Indices
  {
    const size_t indicesPerTriangle = 3;
    if (!AllocAndRead((void**)&simpleMesh->indices, sizeof(uint32_t), indicesPerTriangle * simpleMesh->numTriangles, file))
    {
      return OnError("Error reading index buffer.\n", simpleMesh, file);
    }
  }

  // Read number of vertices.
  {
    if (1 != fread(&simpleMesh->numVertices, sizeof(uint32_t), 1, file))
    {
      return OnError("Error reading number of vertices.\n", simpleMesh, file);
    }
  }

  // Positions
  {
    const size_t componentsPerPosition = 3;
    if (!AllocAndRead((void**)&simpleMesh->positions, sizeof(float), componentsPerPosition * simpleMesh->numVertices, file))
    {
      return OnError("Error reading position buffer.\n", simpleMesh, file);
    }
  }

  // Colors
  const size_t componentsPerColor = 3;
  if (!AllocAndReadIfExists((void**)&simpleMesh->colors, sizeof(float), componentsPerColor * simpleMesh->numVertices, file))
  {
    return OnError("Error reading color buffer.\n", simpleMesh, file);
  }

  // Normals
  const size_t componentsPerNormal = 3;
  if (!AllocAndReadIfExists((void**)&simpleMesh->normals, sizeof(float), componentsPerNormal * simpleMesh->numVertices, file))
  {
    return OnError("Error reading normal buffer.\n", simpleMesh, file);
  }

  // Texture Coordinates
  const size_t componentsPerTextureCoordinate = 2;
  if (!AllocAndReadIfExists((void**)&simpleMesh->textureCoordinates, sizeof(float),
                            componentsPerTextureCoordinate * simpleMesh->numVertices, file))
  {
    return OnError("Error reading texture buffer.\n", simpleMesh, file);
  }
  fclose(file);
  return true;
}

void DestroySimpleMeshIO(SimpleMesh* const simpleMesh)
{
  if (simpleMesh == NULL)
  {
    return;
  }
  simpleMesh->numTriangles = 0;
  simpleMesh->numVertices  = 0;
  free(simpleMesh->indices);
  free(simpleMesh->positions);
  free(simpleMesh->normals);
  free(simpleMesh->textureCoordinates);
  simpleMesh->indices   = NULL;
  simpleMesh->positions = NULL;
  simpleMesh->normals   = NULL;
  simpleMesh->textureCoordinates = NULL;
}
