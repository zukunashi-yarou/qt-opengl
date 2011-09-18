#include "objmesh.h"

#include <QFile>
#include <QString>
#include <QTextStream>
#include <QVector>


struct VertexData {
  QVector3D position;
  QVector3D normal;
  QVector2D texcoord;
};

struct MaterialData {
  unsigned char name[256];
  QVector3D ambient;   // Ka
  QVector3D diffuse;   // Kd
  QVector3D specular;  // Ks
  GLfloat   shininess; // Ns
};

struct GroupData {
    int offset;
    int size;
    int materialIdx;
};


ObjMesh::ObjMesh() :
    m_vertices(NULL),
    m_numVertices(0),
    m_indices(NULL),
    m_numIndices(0),
    m_hasNormals(false),
    m_hasTexcoords(false)
{
}


inline QVector3D computeNormal(QVector3D pos[3])
{
    QVector3D normal;
    normal = QVector3D::crossProduct(pos[2]-pos[1], pos[0]-pos[1]);
    return normal;
}


void ObjMesh::load(QFile& file)
{
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    return;

  QVector<QVector3D> positions;
  QVector<QVector3D> normals;
  QVector<QVector2D> texcoords;

  QVector<GLuint> vindices;
  QVector<GLuint> tindices;
  QVector<GLuint> nindices;

  int faceCount(0);

  QTextStream in(&file);
  while (!in.atEnd()) {
    QString line = in.readLine();
    QString str = line.replace(QRegExp("#.*"),"");
    QStringList list = str.split(" ", QString::SkipEmptyParts);

    if (list.size() < 2)
        continue; // skip

    QString prefix( list.front() );
    list.pop_front();

    if (prefix == "o") {
        //qDebug() << "Name : " << list.at(0);
    }
    else if (prefix == "v") {
        QVector3D v(0,0,0);
        if (list.size() >= 3) {
            v = QVector3D( list.at(0).toDouble(), list.at(1).toDouble(), list.at(2).toDouble() );
        }
        if (list.size() == 4) {
            double w = list.at(3).toDouble();
            if (w != 0.0)
                v /= w;
        }
        positions << v;
    }
    else if (prefix == "vt") {
        QVector2D vt(0,0);
        if (list.size() >= 2) {
            vt = QVector2D( list.at(0).toDouble(), list.at(1).toDouble() );
        }
        if (list.size() == 3) {
            double w = list.at(2).toDouble();
            if (w != 0.0)
                vt /= w;
        }
        texcoords << vt;
    }
    else if (prefix == "vn") {
        QVector3D vn(0,0,0);
        if (list.size() >= 3) {
            vn = QVector3D( list.at(0).toDouble(), list.at(1).toDouble(), list.at(2).toDouble() );
        }
        if (list.size() == 4) {
            double w = list.at(3).toDouble();
            if (w != 0.0)
                vn /= w;
        }
        normals << vn;
    }
    else if (prefix == "f") {
        int fv[3] = {-1};
        int ft[3] = {-1};
        int fn[3] = {-1};
        int idx = 0;

        for (QStringList::const_iterator it = list.begin(); it != list.end(); ++it) {

            QStringList faceList = (*it).split("/");
            QStringList::const_iterator fit = faceList.begin();

            if (faceList.size() == 1) { // v only
                fv[idx] = (*fit == "") ? -1 : (*fit).toDouble();
                ft[idx] = -1;
                fn[idx] = -1;
            }
            else if (faceList.size() == 2) { // v & t
                fv[idx] = (*fit == "") ? -1 : (*fit).toDouble(); ++fit;
                ft[idx] = (*fit == "") ? -1 : (*fit).toDouble(); ++fit;
                fn[idx] = -1;
            }
            else if (faceList.size() == 3) { // (v & t & n) or (v & 0 & n)
                fv[idx] = (*fit == "") ? -1 : (*fit).toDouble(); ++fit;
                ft[idx] = (*fit == "") ? -1 : (*fit).toDouble(); ++fit;
                fn[idx] = (*fit == "") ? -1 : (*fit).toDouble();
            }

            if (idx >= 2) {
                if ((fv[0] >= 0) && (fv[1] >= 0) && (fv[2] >= 0)) {
                    vindices << (fv[0]-1) << (fv[1]-1) << (fv[2]-1);
                }
                if ((ft[0] >= 0) && (ft[1] >= 0) && (ft[2] >= 0)) {
                    tindices << (ft[0]-1) << (ft[1]-1) << (ft[2]-1);
                }
                if ((fn[0] >= 0) && (fn[1] >= 0) && (fn[2] >= 0)) {
                    nindices << (fn[0]-1) << (fn[1]-1) << (fn[2]-1);
                }
                faceCount++;
            }

            idx++;
            if (idx > 2) idx = 2; // Hint: covert from polygon to triangle
        }
    }
  } // while (!in.atEnd())


  ///////////////////////////////////////////////////////////////
  // create Model
  if ((positions.size() == 0) || vindices.size())
      return;

  this->m_numVertices = positions.size();
  this->m_numIndices = vindices.size();

  //
  // generate index list
  //
  this->m_indices = new GLushort[this->m_numIndices];
  for (unsigned i=0; i<this->m_numIndices; i++) {
      this->m_indices[i] = vindices[i];
  }

  //
  // generate vertex list
  //
  this->m_vertices = new VertexData[this->m_numVertices];

  // position
  for (unsigned i=0; i<this->m_numVertices; i++) {
      this->m_vertices[i].position = positions[i];
  }

  // normal
  if (nindices.size() == 0) {
      m_hasNormals = false;
  }
  else {
      m_hasNormals = true;
      // convert
      for (unsigned i=0; i<this->m_numVertices; i++) {
          QVector3D sum(0,0,0);
          for (unsigned j=0; j<this->m_numIndices; j++) {
              if (i==vindices[j]) {
                  sum += normals[nindices[j]];
              }
          }
          this->m_vertices[i].normal = sum.normalized();
      }
  }

  // texcoords
  if (tindices.size() == 0) {
    m_hasTexcoords = false;
  }
  else {
    m_hasTexcoords = true;
    for (unsigned i=0; i<this->m_numVertices; i++) {
        QVector2D ret(0,0);
        for (unsigned j=0; j<this->m_numIndices; j++) {
            if (i==vindices[j]) {
                ret = texcoords[tindices[j]];
                break;
            }
        }
        this->m_vertices[i].texcoord = ret;
    }
  }

//  qDebug() << "positions=" << positions;
//  qDebug() << "texcoords=" << texcoords;
//  qDebug() << "normals  =" << normals;
  qDebug() << this->m_vertices;
}
