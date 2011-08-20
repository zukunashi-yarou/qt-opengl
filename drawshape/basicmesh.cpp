#include "basicmesh.h"
#include "mesh.h"

#include <cstdlib>
#include <cstring>
#include <cmath>

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

Mesh* createPlane( float halfX, float halfY )
{
  float sizeX = 1.0f * halfX;
  float sizeY = 1.0f * halfY;

  GLushort numVertices = 4;
  GLushort numIndices = 6;

  VertexData vertices[] = { // (x,0,z)
    { QVector3D(-sizeX, 0.0f, -sizeY ), QVector3D( 0.0f, 1.0f, 0.0f ), QVector2D( 0.0f, 0.0f ) },
    { QVector3D( sizeX, 0.0f, -sizeY ), QVector3D( 0.0f, 1.0f, 0.0f ), QVector2D( 0.0f, 1.0f ) },
    { QVector3D( sizeX, 0.0f,  sizeY ), QVector3D( 0.0f, 1.0f, 0.0f ), QVector2D( 1.0f, 1.0f ) },
    { QVector3D(-sizeX, 0.0f,  sizeY ), QVector3D( 0.0f, 1.0f, 0.0f ), QVector2D( 1.0f, 0.0f ) }
  };
  GLushort indices[] = {
    0, 2, 1,
    0, 3, 2
  };

  return Mesh::create(vertices, numVertices, indices, numIndices);
}


Mesh* createCube( float half )
{
  float sx = 1.0f * half;
  float sy = 1.0f * half;
  float sz = 1.0f * half;

  GLushort numVertices = 24;
  GLushort numIndices = 36;

  VertexData vertices[] = {
    { QVector3D(-sx, -sy, -sz), QVector3D(+0.0f, -1.0f, +0.0f), QVector2D(0.0f, 0.0f) },
    { QVector3D(-sx, -sy, +sz), QVector3D(+0.0f, -1.0f, +0.0f), QVector2D(0.0f, 1.0f) },
    { QVector3D(+sx, -sy, +sz), QVector3D(+0.0f, -1.0f, +0.0f), QVector2D(1.0f, 1.0f) },
    { QVector3D(+sx, -sy, -sz), QVector3D(+0.0f, -1.0f, +0.0f), QVector2D(1.0f, 0.0f) },
    { QVector3D(-sx, +sy, -sz), QVector3D(+0.0f, +1.0f, +0.0f), QVector2D(1.0f, 0.0f) },
    { QVector3D(-sx, +sy, +sz), QVector3D(+0.0f, +1.0f, +0.0f), QVector2D(1.0f, 1.0f) },
    { QVector3D(+sx, +sy, +sz), QVector3D(+0.0f, +1.0f, +0.0f), QVector2D(0.0f, 1.0f) },
    { QVector3D(+sx, +sy, -sz), QVector3D(+0.0f, +1.0f, +0.0f), QVector2D(0.0f, 0.0f) },
    { QVector3D(-sx, -sy, -sz), QVector3D(+0.0f, +0.0f, -1.0f), QVector2D(0.0f, 0.0f) },
    { QVector3D(-sx, +sy, -sz), QVector3D(+0.0f, +0.0f, -1.0f), QVector2D(0.0f, 1.0f) },
    { QVector3D(+sx, +sy, -sz), QVector3D(+0.0f, +0.0f, -1.0f), QVector2D(1.0f, 1.0f) },
    { QVector3D(+sx, -sy, -sz), QVector3D(+0.0f, +0.0f, -1.0f), QVector2D(1.0f, 0.0f) },
    { QVector3D(-sx, -sy, +sz), QVector3D(+0.0f, +0.0f, +1.0f), QVector2D(0.0f, 0.0f) },
    { QVector3D(-sx, +sy, +sz), QVector3D(+0.0f, +0.0f, +1.0f), QVector2D(0.0f, 1.0f) },
    { QVector3D(+sx, +sy, +sz), QVector3D(+0.0f, +0.0f, +1.0f), QVector2D(1.0f, 1.0f) },
    { QVector3D(+sx, -sy, +sz), QVector3D(+0.0f, +0.0f, +1.0f), QVector2D(1.0f, 0.0f) },
    { QVector3D(-sx, -sy, -sz), QVector3D(-1.0f, +0.0f, +0.0f), QVector2D(0.0f, 0.0f) },
    { QVector3D(-sx, -sy, +sz), QVector3D(-1.0f, +0.0f, +0.0f), QVector2D(0.0f, 1.0f) },
    { QVector3D(-sx, +sy, +sz), QVector3D(-1.0f, +0.0f, +0.0f), QVector2D(1.0f, 1.0f) },
    { QVector3D(-sx, +sy, -sz), QVector3D(-1.0f, +0.0f, +0.0f), QVector2D(1.0f, 0.0f) },
    { QVector3D(+sx, -sy, -sz), QVector3D(+1.0f, +0.0f, +0.0f), QVector2D(0.0f, 0.0f) },
    { QVector3D(+sx, -sy, +sz), QVector3D(+1.0f, +0.0f, +0.0f), QVector2D(0.0f, 1.0f) },
    { QVector3D(+sx, +sy, +sz), QVector3D(+1.0f, +0.0f, +0.0f), QVector2D(1.0f, 1.0f) },
    { QVector3D(+sx, +sy, -sz), QVector3D(+1.0f, +0.0f, +0.0f), QVector2D(1.0f, 0.0f) }
  };

  GLushort indices[] = {
    0, 2, 1,
    0, 3, 2,
    4, 5, 6,
    4, 6, 7,
    8, 9, 10,
    8, 10, 11,
    12, 15, 14,
    12, 14, 13,
    16, 17, 18,
    16, 18, 19,
    20, 23, 22,
    20, 22, 21
  };

  return Mesh::create(vertices, numVertices, indices, numIndices);
}


Mesh* createSphere( float radius, unsigned int numSlices )
{
  unsigned int numParallels = numSlices;
  unsigned int numVertices = ( numParallels + 1 ) * ( numSlices + 1 );
  unsigned int numIndices = numParallels * numSlices * 6;
  float angleStep = (2.0f * M_PI) / ((float) numSlices);

  VertexData* vertices = new VertexData[numVertices];
  if (!vertices) { return NULL; }

  GLushort* indices = new GLushort[numIndices];
  if (!indices) { return NULL; }

  for (unsigned i=0; i<numParallels+1; ++i) {
    for (unsigned j=0; j<numSlices+1; ++j) {
      GLushort index = (i * (numSlices + 1) + j);

      vertices[index].position = QVector3D(
          radius * sinf(0.5f * angleStep * (float)i) * sinf(angleStep * (float)j),
          radius * cosf(0.5f * angleStep * (float)i),
          radius * sinf(0.5f * angleStep * (float)i) * cosf(angleStep * (float)j) );

      vertices[index].normal = QVector3D(
          vertices[index].position.x() / radius,
          vertices[index].position.y() / radius,
          vertices[index].position.z() / radius );

      vertices[index].texcoord = QVector2D(
          (float)j / (float)numSlices,
          (1.0f - (float)i) / (float)(numParallels - 1) );
    }
  }

  GLushort* indexBuf = indices;
  for (unsigned i=0; i<numParallels ; ++i) {
    for (unsigned j=0; j<numSlices; ++j) {
      *indexBuf++  = i * (numSlices + 1) + j;
      *indexBuf++ = (i + 1) * (numSlices + 1) + j;
      *indexBuf++ = (i + 1) * (numSlices + 1) + (j + 1);

      *indexBuf++ = i * (numSlices + 1) + j;
      *indexBuf++ = (i + 1) * (numSlices + 1) + (j + 1);
      *indexBuf++ = i * (numSlices + 1) + (j + 1);
    }
  }

  Mesh* mesh = Mesh::create(vertices, numVertices, indices, numIndices);

  delete [] vertices;
  delete [] indices;

  return mesh;
}

Mesh* createTorus( float innerRadius, float outerRadius, unsigned int numSides, unsigned numFaces )
{
  GLushort numVertices;
  GLushort numIndices;

  if ((numSides<3) || (numFaces<3)) { return NULL; }

  float tIncr = 1.0f/(float)numFaces;
  float sIncr = 1.0f/(float)numSides;

  numVertices = (numFaces+1) * (numSides+1);
  numIndices  = numFaces * numSides * 2 * 3;

  VertexData* vertices = new VertexData[numVertices];
  if (!vertices) { return NULL; }

  GLushort* indices = new GLushort[numIndices];
  if (!indices) { return NULL; }

  float s = 0.0f;
  for (unsigned i = 0; i <= numSides; i++, s+=sIncr) {
    float cos2PIs = (float)cosf(2.0f*M_PI*s);
    float sin2PIs = (float)sinf(2.0f*M_PI*s);

    float t = 0.0f;
    for (unsigned j = 0; j <= numFaces; j++, t+=tIncr) {
      float cos2PIt = (float)cosf(2.0f*M_PI*t);
      float sin2PIt = (float)sinf(2.0f*M_PI*t);
      unsigned index = ((i * (numFaces +1)) + j);

      vertices[index].position = QVector3D(
          (outerRadius + innerRadius * cos2PIt) * cos2PIs,
          innerRadius * sin2PIt,
          (outerRadius + innerRadius * cos2PIt) * sin2PIs );

      vertices[index].normal = QVector3D(
          cos2PIs * cos2PIt,
          sin2PIt,
          sin2PIs * cos2PIt );

      vertices[index].texcoord = QVector2D(s, t);
    }
  }

  unsigned indexIndices = 0;
  for (unsigned i = 0; i < numSides; ++i) {
    for (unsigned j = 0; j < numFaces; ++j) {
      float v0 = ((i * (numFaces +1)) + j);
      float v1 = ((i * (numFaces +1)) + (j+1));
      float v2 = (((i+1) * (numFaces +1)) + (j+1));
      float v3 = (((i+1) * (numFaces +1)) + j);

      indices[indexIndices++] = v0;
      indices[indexIndices++] = v1;
      indices[indexIndices++] = v2;

      indices[indexIndices++] = v0;
      indices[indexIndices++] = v2;
      indices[indexIndices++] = v3;
    }
  }
  Mesh* mesh = Mesh::create(vertices, numVertices, indices, numIndices);

  delete [] vertices;
  delete [] indices;

  return mesh;
}

Mesh* createCapsule( float radius, float length, unsigned int numSlices )
{
  GLushort numParallels = numSlices;
  GLushort numVertices = ( numParallels + 2 ) * ( numSlices + 1 );
  GLushort numIndices = (numParallels+1) * numSlices * 6;
  float angleStep = (2.0f * M_PI) / ((float) numSlices);
  float l = length * 0.5;

  VertexData* vertices = new VertexData[numVertices];
  if (!vertices) { return NULL; }

  GLushort* indices = new GLushort[numIndices];
  if (!indices) { return NULL; }

  unsigned index = 0;
  for (unsigned i=0; i<numParallels/2; ++i) {
    // cylinder top cap
    for (unsigned j=0; j<numSlices+1; ++j) {
      vertices[index].position = QVector3D(
          radius * sinf(0.5f*angleStep * (float)i) * sinf(angleStep * (float)j),
          radius * cosf(0.5f*angleStep * (float)i) + l,
          radius * sinf(0.5f*angleStep * (float)i) * cosf(angleStep * (float)j) );

      vertices[index].normal = QVector3D(
          sinf(0.5f*angleStep * (float)i) * sinf(angleStep * (float)j),
          cosf(0.5f*angleStep * (float)i),
          sinf(0.5f*angleStep * (float)i) * cosf(angleStep * (float)j) );

      vertices[index].texcoord = QVector2D(
          sinf(0.5f*angleStep * (float)i) * sinf(angleStep * (float)j),
          sinf(0.5f*angleStep * (float)i) * cosf(angleStep * (float)j) );
      ++index;
    }
  }
  {
    // cylinder body
    for (unsigned j=0; j<numSlices+1; ++j) {
      vertices[index].position = QVector3D(
          radius * sinf(angleStep*(float)j),
          l,
          radius * cosf(angleStep*(float)j) );

      vertices[index].normal = QVector3D(
          sinf(angleStep*(float)j),
          0.0f,
          cosf(angleStep*(float)j) );

      vertices[index].texcoord = QVector2D(
          sinf(angleStep*(float)j),
          cosf(angleStep*(float)j) );
      ++index;
    }
    for (unsigned j=0; j<numSlices+1; ++j) {
      vertices[index].position = QVector3D(
          radius * sinf(angleStep*(float)j),
          -l,
          radius * cosf(angleStep*(float)j) );

      vertices[index].normal = QVector3D(
          sinf(angleStep*(float)j),
          0.0f,
          cosf(angleStep*(float)j) );

      vertices[index].texcoord = QVector2D(
          sinf(angleStep*(float)j),
          cosf(angleStep*(float)j) );

      ++index;
    }
  }
  for (unsigned i=numParallels/2+1; i<(unsigned)numParallels+1; ++i) {
    // cylinder bottom cap
    for (unsigned j=0; j<numSlices+1; ++j) {
      vertices[index].position = QVector3D(
          radius * sinf(0.5f*angleStep*(float)i) * sinf(angleStep*(float)j),
          radius * cosf(0.5f*angleStep*(float)i) - l,
          radius * sinf(0.5f*angleStep*(float)i) * cosf(angleStep*(float)j) );

      vertices[index].normal = QVector3D(
          sinf(0.5f*angleStep*(float)i) * sinf(angleStep*(float)j),
          cosf(0.5f*angleStep*(float)i),
          sinf(0.5f*angleStep*(float)i) * cosf(angleStep*(float)j) );

      vertices[index].texcoord = QVector2D(
          sinf(0.5f*angleStep*(float)i) * sinf(angleStep*(float)j),
          sinf(0.5f*angleStep*(float)i) * cosf(angleStep*(float)j) );

      ++index;
    }
  }

  GLushort* indexBuf = indices;
  for (unsigned i=0; i<(unsigned)numParallels+1; ++i) {
    for (unsigned j=0; j<numSlices; ++j) {
      *indexBuf++ = i       * (numSlices + 1) + j;
      *indexBuf++ = (i + 1) * (numSlices + 1) + j;
      *indexBuf++ = (i + 1) * (numSlices + 1) + (j + 1);

      *indexBuf++ = i       * (numSlices + 1) + j;
      *indexBuf++ = (i + 1) * (numSlices + 1) + (j + 1);
      *indexBuf++ = i       * (numSlices + 1) + (j + 1);
    }
  }

  Mesh* mesh = Mesh::create(vertices, numVertices, indices, numIndices);

  delete [] vertices;
  delete [] indices;

  return mesh;
}


Mesh* createCylinder( float radius, float length, unsigned int numSlices )
{
  unsigned int numVertices = 1 + (numSlices+1)*4 + 1;
  unsigned int numIndices = (numSlices + numSlices*4 + numSlices) * 3;
  float angleStep = (2.0f * M_PI) / ((float) numSlices);
  float l = length * 0.5;

  VertexData* vertices = new VertexData[numVertices];
  if (!vertices) { return NULL; }

  GLushort* indices = new GLushort[numIndices];
  if (!indices) { return NULL; }


  unsigned int index = 0;
  {
    // cylinder top cap
    {
      // center
      vertices[index].position = QVector3D(0.0f, l, 0.0f);
      vertices[index].normal = QVector3D(0.0f, 1.0f, 0.0f);
      vertices[index].texcoord = QVector2D(0.0f, 0.0f);
      ++index;
    }
    for (unsigned j=0; j<numSlices+1; ++j) {
      vertices[index].position = QVector3D(
          radius * sinf(angleStep * (float)j),
          l,
          radius * cosf(angleStep * (float)j) );

      vertices[index].normal = QVector3D(0.0f, 1.0f, 0.0f);

      vertices[index].texcoord = QVector2D(
          sinf(angleStep * (float)j),
          cosf(angleStep * (float)j) );

      ++index;
    }
  }
  {
    // cylinder body (top)
    for (unsigned j=0; j<numSlices+1; ++j) {
      vertices[index].position = QVector3D(
          radius * sinf(angleStep * (float)j),
          l,
          radius * cosf(angleStep * (float)j) );

      vertices[index].normal = QVector3D(
          sinf(angleStep * (float)j),
          0.0f,
          cosf(angleStep * (float)j) );

      vertices[index].texcoord = QVector2D(
          sinf(angleStep * (float)j),
          cosf(angleStep * (float)j) );

      ++index;
    }
    // cylinder body (bottom)
    for (unsigned j=0; j<numSlices+1; ++j) {
      vertices[index].position = QVector3D(
          radius * sinf(angleStep * (float)j),
          -l,
          radius * cosf(angleStep * (float)j) );

      vertices[index].normal = QVector3D(
          sinf(angleStep * (float)j),
          0.0f,
          cosf(angleStep * (float)j) );

      vertices[index].texcoord = QVector2D(
          sinf(angleStep * (float)j),
          cosf(angleStep * (float)j) );

      ++index;
    }
  }
  {
    // cylinder bottom cap

    for (unsigned j=0; j<numSlices+1; ++j) {
      vertices[index].position = QVector3D(
          radius * sinf(angleStep * (float)j),
          -l,
          radius * cosf(angleStep * (float)j) );

      vertices[index].normal = QVector3D(0.0f, -1.0f, 0.0f);

      vertices[index].texcoord = QVector2D(
          sinf(angleStep * (float)j),
          cosf(angleStep * (float)j) );

      ++index;
    }
    {
      // center
      vertices[index].position = QVector3D(0.0f, -l, -0.0f);
      vertices[index].normal =  QVector3D(0.0f, -1.0f, 0.0f);
      vertices[index].texcoord = QVector2D(0.0f, 0.0f);
      ++index;
    }
  }

  GLushort* indexBuf = indices;
  {
    // cylinder top cap
    unsigned center = 0;
    unsigned offset = 1;
    for (unsigned j=0; j<numSlices; ++j) {
      *indexBuf++ = center;
      *indexBuf++ = offset + j;
      *indexBuf++ = offset + (j + 1);
    }
  }
  {
    // cylinder body
    unsigned offset = 1 + (numSlices+1);
    for (unsigned j=0; j<numSlices; ++j) {
      *indexBuf++ = offset + j;
      *indexBuf++ = offset + (numSlices + 1) + j;
      *indexBuf++ = offset + (numSlices + 1) + (j + 1);

      *indexBuf++ = offset + j;
      *indexBuf++ = offset + (numSlices + 1) + (j + 1);
      *indexBuf++ = offset + (j + 1);
    }
  }
  {
    // cylinder bottom cap
    unsigned center = 1 + (numSlices+1)*4;
    unsigned offset = 1 + (numSlices+1)*3;
    // cylinder top cap
    for (unsigned j=0; j<numSlices; ++j) {
      *indexBuf++ = center;
      *indexBuf++ = offset + (j + 1);
      *indexBuf++ = offset + j;
    }
  }

  Mesh* mesh = Mesh::create(vertices, numVertices, indices, numIndices);

  delete [] vertices;
  delete [] indices;

  return mesh;
}



Mesh* createCone( float radius, float length, unsigned int numSlices )
{
  unsigned int numVertices = 1 + (numSlices+1)*2 + 1;
  unsigned int numIndices = (numSlices + numSlices*2 + numSlices) * 3;
  float angleStep = (2.0f * M_PI) / ((float) numSlices);
  float l = length * 0.5;

  VertexData* vertices = new VertexData[numVertices];
  if (!vertices) { return NULL; }

  GLushort* indices = new GLushort[numIndices];
  if (!indices) { return NULL; }

  unsigned int index = 0;
  {
    // cylinder top cap
    {
      // center
      vertices[index].position = QVector3D(0.0f, l, 0.0f);
      vertices[index].normal = QVector3D(0.0f, 1.0f, 0.0f);
      vertices[index].texcoord = QVector2D(0.0f, 0.0f);
      ++index;
    }
    // cylinder body (bottom)
    for (unsigned j=0; j<numSlices+1; ++j) {
      vertices[index].position = QVector3D(
          radius * sinf(angleStep * (float)j),
          -l,
          radius * cosf(angleStep * (float)j) );

      vertices[index].normal = QVector3D(
          sinf(angleStep * (float)j),
          0.0f,
          cosf(angleStep * (float)j) );

      vertices[index].texcoord = QVector2D(
          sinf(angleStep * (float)j),
          cosf(angleStep * (float)j) );

      ++index;
    }
  }
  {
    // cylinder bottom cap
    for (unsigned j=0; j<numSlices+1; ++j) {
      vertices[index].position = QVector3D(
          radius * sinf(angleStep * (float)j),
          -l,
          radius * cosf(angleStep * (float)j) );

      vertices[index].normal = QVector3D(0.0f, -1.0f, 0.0f);

      vertices[index].texcoord = QVector2D(
          sinf(angleStep * (float)j),
          cosf(angleStep * (float)j) );

      ++index;
    }
    {
      // center
      vertices[index].position = QVector3D(0.0f, -l, 0.0f);
      vertices[index].normal = QVector3D(0.0f, -1.0f, 0.0f);
      vertices[index].texcoord = QVector2D(0.0f, 0.0f);
      ++index;
    }
  }

  GLushort* indexBuf = indices;
  {
    // cylinder top cap
    unsigned center = 0;
    unsigned offset = 1;
    for (unsigned j=0; j<numSlices; ++j) {
      *indexBuf++ = center;
      *indexBuf++ = offset + j;
      *indexBuf++ = offset + (j + 1);
    }
  }
  {
    // cylinder bottom cap
    unsigned center = 1 + (numSlices+1)*2;
    unsigned offset = 1 + (numSlices+1)*1;
    // cylinder top cap
    for (unsigned j=0; j<numSlices; ++j) {
      *indexBuf++ = center;
      *indexBuf++ = offset + (j + 1);
      *indexBuf++ = offset + j;
    }
  }

  Mesh* mesh = Mesh::create(vertices, numVertices, indices, numIndices);

  delete [] vertices;
  delete [] indices;

  return mesh;
}


