#include "vector3D.h"

#ifndef SEGMENT3D_H
#define SEGMENT3D_H

class Segment3D : Vector3D
{
private:
    Vector3D start;
    Vector3D end;

public:
    Segment3D(Vector3D Start, Vector3D End);

};

#endif // SEGMENT3D_H
