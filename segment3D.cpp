#include "segment3D.h"

// #include <QDebug.h> // Delete when end

Segment3D::Segment3D(Vector3D Start, Vector3D End, std::string Name)
{
    // Vector3D a_point = Vector3D(Start.x(), Start.y(), Start.z());
    this->start = Start;
    this->end = End;
    this->name = Name;
}


Vector3D Segment3D::getStart()
{
    return this->start;
}
Vector3D Segment3D::getEnd()
{
    return this->end;
}

std::string Segment3D::get_string_to_show()
{
    return this->name + ": " + this->start.get_string_to_show() + "-" + this->end.get_string_to_show();
}

bool Segment3D::is_exists_equal_surface_to(Segment3D segment)
{
    double **mat3;
    mat3 = new double*[3];
    for (unsigned int i =0; i < 3; i++)
    {
        mat3[i] = new double[3];
    }
    mat3[0][0] = this->end.x() - this->start.x();
    mat3[0][1] = this->end.y() - this->start.y();
    mat3[0][2] = this->end.z() - this->start.z();

    mat3[1][0] = segment.start.x() - this->start.x();
    mat3[1][1] = segment.start.y() - this->start.y();
    mat3[1][2] = segment.start.z() - this->start.z();

    mat3[2][0] = segment.end.x() - this->start.x();
    mat3[2][1] = segment.end.y() - this->start.y();
    mat3[2][2] = segment.end.z() - this->start.z();
    // qInfo() << det(mat3, 3);
    double delta = det(mat3, 3);
    for (unsigned int i =0; i < 3; i++) {
        delete [] mat3[i];
    }
    delete [] mat3;
    return (std::abs(delta) < eps);
}


bool Segment3D::is_collinear_to_segment(Segment3D segment)
{
    double **mat;
    mat = new double*[2];
    for (unsigned int i = 0; i < 2; i++) {
        mat[i] = new double[2];
    }
    double delta_sum = 0;
    // TODO можно оптимизировать вычисляя определители, пока не найден не нулевой
    // x and y
    mat[0][0] = this->start.x() - this->end.x();
    mat[0][1] = this->start.y() - this->end.y();
    mat[1][0] = segment.start.x() - segment.end.x();
    mat[1][1] = segment.start.y() - segment.end.y();
    delta_sum += std::pow(det(mat, 2), 2);
    // x and z
    mat[0][0] = this->start.x() - this->end.x();
    mat[0][1] = this->start.z() - this->end.z();
    mat[1][0] = segment.start.x() - segment.end.x();
    mat[1][1] = segment.start.z() - segment.end.z();
    delta_sum += std::pow(det(mat, 2), 2);
    // y and z
    mat[0][0] = this->start.z() - this->end.z();
    mat[0][1] = this->start.y() - this->end.y();
    mat[1][0] = segment.start.z() - segment.end.z();
    mat[1][1] = segment.start.y() - segment.end.y();
    delta_sum += std::pow(det(mat, 2), 2);
    for (unsigned int i = 0; i < 2; i++) {
        delete [] mat[i];
    }
    delete [] mat;
    if (delta_sum <= 3 * std::pow(eps, 2)) return true;
    else return false;
}

double Segment3D::calc_u_to_segments(Segment3D seg1, Segment3D seg2)
{
    // TODO переделать, чтобы при нулевом определителе считал другие координаты
    double u;
    // Kramer's method
    double **mat2, **mat1;
    mat1 = new double*[2];
    mat2 = new double*[2];
    for (unsigned int i = 0; i < 2; i++)
    {
        mat1[i] = new double[2];
        mat2[i] = new double[2];
    }
    // Denominator
    mat1[0][0] = seg1.getStart().x() - seg1.getEnd().x(); // x_A - x_B
    mat1[0][1] = seg2.getEnd().x() - seg2.getStart().x(); // x_D - x_C
    mat1[1][0] = seg1.getStart().y() - seg1.getEnd().y(); // y_A - y_B
    mat1[1][1] = seg2.getEnd().y() - seg2.getStart().y(); // y_D - y_C
    if (std::abs(det(mat1, 2)) < std::pow(10, -12)) // TODO eps брать из Vector3D
    {
        throw "Denominator u is zero-like.";
        u = -1;
    }
    else
    {
        // Numerator
        mat2[0][0] = seg2.getEnd().x() - seg1.getEnd().x(); // x_D - x_B
        mat2[0][1] = seg2.getEnd().x() - seg2.getStart().x(); // x_D - x_C
        mat2[1][0] = seg2.getEnd().y() - seg1.getEnd().y(); // y_D - y_B
        mat2[1][1] = seg2.getEnd().y() - seg2.getStart().y(); // y_D - y_C
        u = det(mat2, 2) / det(mat1, 2);
        for (unsigned int i = 0; i < 2; i++) {
            delete [] mat1[i];
            delete [] mat2[i];
        }
        delete [] mat1;
        delete [] mat2;
    }
    return u;
}

double Segment3D::calc_v_to_segments(Segment3D seg1, Segment3D seg2)
{
    double v;
    // Kramer's method
    double **mat2, **mat1;
    mat1 = new double*[2];
    mat2 = new double*[2];
    for (unsigned int i = 0; i < 2; i++) {
        mat1[i] = new double[2];
        mat2[i] = new double[2];
    }
    // Denominator
    mat1[0][0] = seg1.getStart().x() - seg1.getEnd().x(); // x_A - x_B
    mat1[0][1] = seg2.getEnd().x() - seg2.getStart().x(); // x_D - x_C
    mat1[1][0] = seg1.getStart().y() - seg1.getEnd().y(); // y_A - y_B
    mat1[1][1] = seg2.getEnd().y() - seg2.getStart().y(); // y_D - y_C
    if (std::abs(det(mat1, 2)) < std::pow(10, -12)) // TODO eps брать из Vector3D
    {
        throw "Denominator v is zero-like." + std::to_string(det(mat1, 2));
        v = -1;
    }
    else
    {
        // Numerator
        mat2[0][0] = seg1.getStart().x() - seg1.getEnd().x(); // x_A - x_B
        mat2[0][1] = seg2.getEnd().x() - seg1.getEnd().x(); // x_D - x_B
        mat2[1][0] = seg1.getStart().y() - seg1.getEnd().y(); // y_A - y_B
        mat2[1][1] = seg2.getEnd().y() - seg1.getEnd().y(); // y_D - y_B
        v = det(mat2, 2) / det(mat1, 2);
        for (unsigned int i = 0; i < 2; i++) {
            delete [] mat1[i];
            delete [] mat2[i];
        }
        delete [] mat1;
        delete [] mat2;
    }
    return v;
}

Vector3D Segment3D::calc_intersection_point_by_uv_and_seg(double u, double v, Segment3D AB)
{
    double x = u * (AB.getStart().x() - AB.getEnd().x()) + AB.getEnd().x();
    double y = u * (AB.getStart().y() - AB.getEnd().y()) + AB.getEnd().y();
    double z = u * (AB.getStart().z() - AB.getEnd().z()) + AB.getEnd().z();
    Vector3D final_point = Vector3D(x, y, z, "P");
    return final_point;
}
