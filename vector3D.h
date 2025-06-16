#include <QtCore/QString>

#ifndef VECTOR3D_H
#define VECTOR3D_H

class Vector3D
{
private:
    double X, Y, Z;
    QString Name;

public:
    Vector3D(double x, double y, double z, QString name);
    Vector3D();
    QString get_string_to_show();
    // Getters
    double x();
    double y();
    double z();



};

#endif // VECTOR3D_H
