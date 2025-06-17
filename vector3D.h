#include <QtCore/QString>
#include <cmath>

#ifndef VECTOR3D_H
#define VECTOR3D_H

class Vector3D
{
private:
    double X, Y, Z;
    std::string Name;

public:
    Vector3D(double x, double y, double z, std::string name);
    Vector3D();
    std::string get_string_to_show();
    static inline double eps = std::pow(10, -12); // для сравнивания с нулём (машинная точность)

    // Getters
    double x();
    double y();
    double z();



};

#endif // VECTOR3D_H
