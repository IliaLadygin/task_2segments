#include "vector3D.h"
#include "QDebug"

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


Vector3D Vector3D::operator- (const Vector3D vector)
{
    Vector3D ans(this->X - vector.X, this->Y - vector.Y, this->Z - vector.Z, this->Name + "-" + vector.Name);
    return ans;
}
Vector3D Vector3D::operator+ (const Vector3D vector)
{
    Vector3D ans(this->X + vector.X, this->Y - vector.Y, this->Z - vector.Z, this->Name + "+" + vector.Name);
    return ans;
}

double Vector3D::scalar_mult(const Vector3D vector)
{
    return (this->X * vector.X + this->Y * vector.Y + this->Z * vector.Z);
}
Vector3D Vector3D::vector_mult(const Vector3D vector)
{
    double **mat;
    mat = new double*[2];
    for (unsigned int i = 0; i < 2; i++) {
        mat[i] = new double[2];
    }
    // Vector_mult_x
    mat[0][0] = this->Y;
    mat[0][1] = this->Z;
    mat[1][0] = vector.Y;
    mat[1][1] = vector.Z;
    double x = det(mat, 2);
    // Vector_mult_y
    mat[0][0] = this->X;
    mat[0][1] = this->Z;
    mat[1][0] = vector.X;
    mat[1][1] = vector.Z;
    double y = -det(mat, 2);
    // Vector_mult_z
    mat[0][0] = this->X;
    mat[0][1] = this->Y;
    mat[1][0] = vector.X;
    mat[1][1] = vector.Y;
    double z = det(mat, 2);
    for (unsigned int i = 0; i < 2; i++) {
        delete [] mat[i];
    }
    delete [] mat;
    return Vector3D(x, y, z, this->Name + "cross" + vector.Name);
}
double Vector3D::norm()
{
    return std::pow(scalar_mult(*this), 0.5);
}

bool Vector3D::is_collinear_with(Vector3D vector)
{
    if (this->norm() < eps || vector.norm() < eps) return true; // TODO подумать, что лучше в таком случае возвращать
    qDebug() << this->scalar_mult(vector);
    qDebug() << this->norm();
    qDebug() << vector.norm();
    return std::abs(std::abs(this->scalar_mult(vector)) / (this->norm() * vector.norm()) - 1) < eps;
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
