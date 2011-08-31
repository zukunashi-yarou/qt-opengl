#ifndef BASICMESH_H
#define BASICMESH_H

#include "mesh.h"


Mesh* createPlane( float halfX, float halfY );
Mesh* createCube( float size );
Mesh* createBox( float x, float y, float z );
Mesh* createSphere( float radius, unsigned int numberSlices );
Mesh* createTorus( float innerRadius, float outerRadius, unsigned int numberSides, unsigned int numberFaces );
Mesh* createCapsule( float radius, float length, unsigned int numberSlices );
Mesh* createCylinder( float radius, float length, unsigned int numberSlices );
Mesh* createCone( float radius, float length, unsigned int numberSlices );

#endif // BASICMESH_H
