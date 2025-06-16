#include "vector3D.h"

Vector3D::Vector3D(double x, double y, double z, std::string name)
{
    this->X = x;
    this->Y = y;
    this->Z = z;
    this->Name = name;
}

Vector3D::Vector3D()
{
    this->X = 0;
    this->Y = 0;
    this->Z = 0;
    this->Name = "indefined";
}

std::string Vector3D::get_string_to_show()
{
    return this->Name + "(" + std::to_string(this->x()) + ", " + std::to_string(this->y()) + ", " + std::to_string(this->z()) + ")";
}

double Vector3D::x()
{
    return this->X;
}

double Vector3D::y()
{
    return this->Y;
}

double Vector3D::z()
{
    return this->Z;
}
