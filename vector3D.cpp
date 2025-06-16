#include "vector3D.h"

Vector3D::Vector3D(double x, double y, double z, QString name)
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

QString Vector3D::get_string_to_show()
{
    return this->Name + "(" + QString::number(this->x()) + ", " + QString::number(this->y()) + ", " + QString::number(this->x()) + ")";
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
