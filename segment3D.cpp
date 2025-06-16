#include "segment3D.h"

Segment3D::Segment3D(Vector3D Start, Vector3D End)
{
    // Vector3D a_point = Vector3D(Start.x(), Start.y(), Start.z());
    this->start = Start;
    this->end = End;
}
