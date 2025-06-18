#include <QtCore/QString>
#include <cmath>
#include "minorcalcs.cpp"

#ifndef VECTOR3D_H
#define VECTOR3D_H

class Vector3D
{
private:
    double X, Y, Z;
    std::string Name;

public:
    Vector3D(double x, double y, double z, std::string name);
    Vector3D(double x, double y, double z);
    Vector3D();
    std::string get_string_to_show();
    static const inline double eps = std::pow(10, -12); // для сравнивания с нулём (машинная точность)
    Vector3D operator-(const Vector3D vector);
    Vector3D operator+(const Vector3D vector);
    Vector3D operator*(const double scalar);
    double scalar_mult(const Vector3D vector);
    double norm();
    Vector3D vector_mult(const Vector3D vector);

    bool is_collinear_with(const Vector3D vector);
    // Getters
    double x();
    double y();
    double z();

    // Setter
    void setName(std::string name);


};

#endif // VECTOR3D_H
