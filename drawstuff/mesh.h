#ifndef MESH_H
#define MESH_H

#include <QtOpenGL>
#include <QVector3D>
#include <QVector2D>


struct VertexData {
  QVector3D position;
  QVector3D normal;
  QVector2D texcoord;
};

struct Mesh
{
  VertexData * vertices;
  GLushort   * indices;

  GLuint numVertices;
  GLuint numIndices;

  Mesh() :
    vertices(NULL),
    indices(NULL),
    numVertices(0),
    numIndices(0)
  {}

  ~Mesh()
  {
      destroy();
  }

  static Mesh* create(VertexData *vertices, GLuint numVertices, GLushort *indices, GLuint numIndices)
  {
      Mesh *mesh = new Mesh;
      if (!mesh) { return NULL; }
      mesh->numVertices = numVertices;
      mesh->numIndices = numIndices;

      mesh->vertices = new VertexData[numVertices];
      if(!mesh->vertices) { return NULL; }
      for (unsigned i=0; i<numVertices; i++) {
          mesh->vertices[i] = vertices[i];
      }

      mesh->indices = new GLushort[numIndices];
      if (!mesh->indices) { return NULL; }
      for (unsigned i=0; i<numIndices; i++) {
          mesh->indices[i] = indices[i];
      }
      return mesh;
  }

  void destroy() {
      if (vertices) {
          delete [] vertices;
          vertices = NULL;
      }
      if (indices) {
          delete [] indices;
          indices = NULL;
      }
      numVertices = 0;
      numIndices = 0;
  }
};

#endif // MESH_H
