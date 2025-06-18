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

    Vector3D operator-(const Vector3D vector);
    Vector3D operator+(const Vector3D vector);
    Vector3D operator*(const double scalar);

    std::string get_string_to_show();

    double norm();
    double scalar_mult(const Vector3D vector);
    Vector3D vector_mult(const Vector3D vector);

    struct Collinear{
        bool m_is_collinear;
        int m_det_number;
        double m_det = 0;
    };
    bool is_collinear_with(const Vector3D vector);
    Collinear get_absmax();
    // Getters
    double x();
    double y();
    double z();

    // Setter
    void setName(std::string name);

    static const inline double eps = std::pow(10, -12); // для сравнивания с нулём (машинная точность)
};

#endif // VECTOR3D_H
