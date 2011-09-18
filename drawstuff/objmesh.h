#ifndef OBJMESH_H
#define OBJMESH_H

#include <QtOpenGL>
//#include <QVector3D>
//#include <QVector2D>


struct VertexData;
struct MaterialData;
struct GroupData;

class QFile;

//struct VertexData {
//  QVector3D position;
//  QVector3D normal;
//  QVector2D texcoord;
//};

class ObjMesh
{
protected:
  unsigned char  m_name[256];

  VertexData   * m_vertices;
  GLuint         m_numVertices;

  GLushort     * m_indices;
  GLuint         m_numIndices;

  MaterialData * m_materials;
  GLuint         m_numMaterials;

  GroupData    * m_groups;
  GLuint         m_numGroups;

  bool           m_hasNormals;
  bool           m_hasTexcoords;


public:
  ObjMesh();

  void load(QFile &file);


};

#endif // OBJMESH_H
