#include "segment3D.h"

#include <QDebug.h> // TODO Delete when end

Segment3D::Segment3D(Vector3D Start, Vector3D End, std::string Name)
{
    // Vector3D a_point = Vector3D(Start.x(), Start.y(), Start.z());
    this->start = Start;
    this->end = End;
    this->name = Name;
}

Segment3D::Segment3D()
{
    this->start = Vector3D(0, 0, 0, "-");
    this->end = Vector3D(0, 0, 0, "-");
    this->name = "undefined";
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

/*
    /note Здесь выбираются пары координат, которые "имеют наибольший по модулю определитель"
*/
Segment3D::Collinear Segment3D::is_collinear_to_segment(Segment3D segment)
{
    Collinear ans;
    ans.m_det = 0;
    ans.m_is_collinear = true;
    ans.m_det_number = 0;
    double **mat;
    mat = new double*[2];
    for (unsigned int i = 0; i < 2; i++) {
        mat[i] = new double[2];
    }
    double cur_det = 0;
    // TODO можно оптимизировать: вычисляя определители, останавливать процесс при нахождении ненулевого
    // x and y
    mat[0][0] = this->start.x() - this->end.x();
    mat[0][1] = this->start.y() - this->end.y();
    mat[1][0] = segment.start.x() - segment.end.x();
    mat[1][1] = segment.start.y() - segment.end.y();
    cur_det = std::abs(det(mat, 2));
    if (cur_det > eps)
    {
        ans.m_det_number = 1;
        ans.m_is_collinear = false;
        ans.m_det = cur_det;
    }
    // x and z
    mat[0][0] = this->start.x() - this->end.x();
    mat[0][1] = this->start.z() - this->end.z();
    mat[1][0] = segment.start.x() - segment.end.x();
    mat[1][1] = segment.start.z() - segment.end.z();
    cur_det = std::abs(det(mat, 2));
    if (cur_det > eps)
    {
        if (cur_det > ans.m_det)
        {
            ans.m_det_number = 2;
            ans.m_det = cur_det;
        }
        ans.m_is_collinear = false;
    }
    // y and z
    mat[0][0] = this->start.z() - this->end.z();
    mat[0][1] = this->start.y() - this->end.y();
    mat[1][0] = segment.start.z() - segment.end.z();
    mat[1][1] = segment.start.y() - segment.end.y();
    cur_det = std::abs(det(mat, 2));
    if (cur_det > eps)
    {
        if (cur_det > ans.m_det)
        {
            ans.m_det_number = 3;
            ans.m_det = cur_det;
        }
        ans.m_is_collinear = false;
    }
    for (unsigned int i = 0; i < 2; i++) {
        delete [] mat[i];
    }
    delete [] mat;
    return ans;
}

double Segment3D::calc_u_to_segments(Segment3D seg1, Segment3D seg2, double eps, int non_zero_det)
{
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
    switch (non_zero_det)
    {
    case 1:
    {
        // Denominator
        mat1[0][0] = seg1.getStart().x() - seg1.getEnd().x(); // x_A - x_B
        mat1[0][1] = seg2.getEnd().x() - seg2.getStart().x(); // x_D - x_C
        mat1[1][0] = seg1.getStart().y() - seg1.getEnd().y(); // y_A - y_B
        mat1[1][1] = seg2.getEnd().y() - seg2.getStart().y(); // y_D - y_C
        // Numerator
        mat2[0][0] = seg2.getEnd().x() - seg1.getEnd().x(); // x_D - x_B
        mat2[0][1] = seg2.getEnd().x() - seg2.getStart().x(); // x_D - x_C
        mat2[1][0] = seg2.getEnd().y() - seg1.getEnd().y(); // y_D - y_B
        mat2[1][1] = seg2.getEnd().y() - seg2.getStart().y(); // y_D - y_C
        break;
    }
    case 2:
    {
        // Calculate another denominator
        mat1[0][0] = seg1.getStart().z() - seg1.getEnd().z(); // z_A - z_B
        mat1[0][1] = seg2.getEnd().z() - seg2.getStart().z(); // z_D - z_C
        mat1[1][0] = seg1.getStart().x() - seg1.getEnd().x(); // x_A - x_B
        mat1[1][1] = seg2.getEnd().x() - seg2.getStart().x(); // x_D - x_C
        // Calculate another numerator (for denominator upper)
        mat2[0][0] = seg2.getEnd().z() - seg1.getEnd().z(); // z_D - z_B
        mat2[0][1] = seg2.getEnd().z() - seg2.getStart().z(); // z_D - z_C
        mat2[1][0] = seg2.getEnd().x() - seg1.getEnd().x(); // x_D - x_B
        mat2[1][1] = seg2.getEnd().x() - seg2.getStart().x(); // x_D - x_C
        break;
    }
    case 3:
    {
        // Calculate another denominator
        mat1[0][0] = seg1.getStart().z() - seg1.getEnd().z(); // z_A - z_B
        mat1[0][1] = seg2.getEnd().z() - seg2.getStart().z(); // z_D - z_C
        mat1[1][0] = seg1.getStart().y() - seg1.getEnd().y(); // y_A - y_B
        mat1[1][1] = seg2.getEnd().y() - seg2.getStart().y(); // y_D - y_C
        // Calculate another numerator (for denominator upper)
        mat2[0][0] = seg2.getEnd().z() - seg1.getEnd().z(); // z_D - z_B
        mat2[0][1] = seg2.getEnd().z() - seg2.getStart().z(); // z_D - z_C
        mat2[1][0] = seg2.getEnd().y() - seg1.getEnd().y(); // y_D - y_B
        mat2[1][1] = seg2.getEnd().y() - seg2.getStart().y(); // y_D - y_C
        break;
    }
    default: throw "CALC V: Num of det with non-like zero det is undefined";
    }
    u = det(mat2, 2) / det(mat1, 2);
    for (unsigned int i = 0; i < 2; i++) {
        delete [] mat1[i];
        delete [] mat2[i];
    }
    delete [] mat1;
    delete [] mat2;
    return u;
}

double Segment3D::calc_v_to_segments(Segment3D seg1, Segment3D seg2, double eps, int non_zero_det)
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
    switch (non_zero_det)
    {
    case 1:
    {

        // Denominator
        mat1[0][0] = seg1.getStart().x() - seg1.getEnd().x(); // x_A - x_B
        mat1[0][1] = seg2.getEnd().x() - seg2.getStart().x(); // x_D - x_C
        mat1[1][0] = seg1.getStart().y() - seg1.getEnd().y(); // y_A - y_B
        mat1[1][1] = seg2.getEnd().y() - seg2.getStart().y(); // y_D - y_C
        // Numerator
        mat2[0][0] = seg1.getStart().x() - seg1.getEnd().x(); // x_A - x_B
        mat2[0][1] = seg2.getEnd().x() - seg1.getEnd().x(); // x_D - x_B
        mat2[1][0] = seg1.getStart().y() - seg1.getEnd().y(); // y_A - y_B
        mat2[1][1] = seg2.getEnd().y() - seg1.getEnd().y(); // y_D - y_B
        break;
    }
    case 2:
    {

        // Calculate another denominator
        mat1[0][0] = seg1.getStart().z() - seg1.getEnd().z(); // z_A - z_B
        mat1[0][1] = seg2.getEnd().z() - seg2.getStart().z(); // z_D - z_C
        mat1[1][0] = seg1.getStart().x() - seg1.getEnd().x(); // x_A - x_B
        mat1[1][1] = seg2.getEnd().x() - seg2.getStart().x(); // x_D - x_C
        // Calculate another numerator (for denominator upper)
        mat2[0][0] = seg1.getStart().z() - seg1.getEnd().z(); // z_A - z_B
        mat2[0][1] = seg2.getEnd().z() - seg1.getEnd().z(); // z_D - z_B
        mat2[1][0] = seg1.getStart().x() - seg1.getEnd().x(); // x_A - x_B
        mat2[1][1] = seg2.getEnd().x() - seg1.getEnd().x(); // x_D - x_B
        break;
    }
    case 3:
    {
        // Calculate another denominator
        mat1[0][0] = seg1.getStart().z() - seg1.getEnd().z(); // z_A - z_B
        mat1[0][1] = seg2.getEnd().z() - seg2.getStart().z(); // z_D - z_C
        mat1[1][0] = seg1.getStart().y() - seg1.getEnd().y(); // y_A - y_B
        mat1[1][1] = seg2.getEnd().y() - seg2.getStart().y(); // y_D - y_C
        // Calculate another numerator (for denominator upper)
        mat2[0][0] = seg1.getStart().z() - seg1.getEnd().z(); // z_A - z_B
        mat2[0][1] = seg2.getEnd().z() - seg1.getEnd().z(); // z_D - z_B
        mat2[1][0] = seg1.getStart().y() - seg1.getEnd().y(); // y_A - y_B
        mat2[1][1] = seg2.getEnd().y() - seg1.getEnd().y(); // y_D - y_B
        break;
    }
    default: throw "CALC V: Num of det with non-like zero det is undefined";
    }
    v = det(mat2, 2) / det(mat1, 2);
    for (unsigned int i = 0; i < 2; i++) {
        delete [] mat1[i];
        delete [] mat2[i];
    }
    delete [] mat1;
    delete [] mat2;
    return v;
}

/*
    \note Подстановка в каноническое уравнение прямой
    \note Дополнительная проверка от деления на ноль
*/
bool Segment3D::is_point_belongs_to_line(Vector3D point)
{
    double x, y, z;
    bool flag_x, flag_y, flag_z;
    if ((std::abs((this->start.x() - this->end.x())) < eps) && (std::abs(point.x() - this->start.x()) > eps))   return false;
    else flag_x = std::abs((this->start.x() - this->end.x())) < eps;
    if ((std::abs((this->start.y() - this->end.y())) < eps) && (std::abs(point.y() - this->start.y()) > eps))   return false;
    else flag_y = std::abs((this->start.y() - this->end.y())) < eps;
    if ((std::abs((this->start.z() - this->end.z())) < eps) && (std::abs(point.z() - this->start.z()) > eps))   return false;
    else flag_z = std::abs((this->start.z() - this->end.z())) < eps;
    x = flag_x < eps ? (point.x() - this->start.x()) : (point.x() - this->start.x()) / (this->start.x() - this->end.x());
    y = flag_y < eps ? (point.y() - this->start.y()) : (point.y() - this->start.y()) / (this->start.y() - this->end.y());
    z = flag_z < eps ? (point.z() - this->start.z()) : (point.z() - this->start.z()) / (this->start.z() - this->end.z());
    qDebug() << x << y << z;
    if (flag_x || flag_y || flag_z)
    {
        if (flag_x && flag_y || flag_x && flag_z || flag_z && flag_y) return true;
        if (flag_x) return std::abs(y - z) < eps;
        if (flag_y) return std::abs(x - z) < eps;
        if (flag_z) return std::abs(y - x) < eps;
    }
    return (std::abs(x - y) < eps && std::abs(y - z) < eps);
}

Vector3D Segment3D::calc_intersection_point_by_uv_and_seg(double u, double v, Segment3D AB)
{
    double x = u * (AB.getStart().x() - AB.getEnd().x()) + AB.getEnd().x();
    double y = u * (AB.getStart().y() - AB.getEnd().y()) + AB.getEnd().y();
    double z = u * (AB.getStart().z() - AB.getEnd().z()) + AB.getEnd().z();
    Vector3D final_point = Vector3D(x, y, z, "P");
    return final_point;
}

/*
    \note Вычисление расстояний между точками
*/
bool Segment3D::is_consist_point(Vector3D point)
{
    Segment3D seg1(Vector3D(this->start.x(), this->start.y(), this->start.z(), "AddVector1"), Vector3D(point.x(), point.y(), point.z(), "AddVector2"), "AddSegment1");
    Segment3D seg2(Vector3D(point.x(), point.y(), point.z(), "AddVector3"), Vector3D(this->end.x(), this->end.y(), this->end.z(), "AddVector4"), "AddSegment2");
    return std::abs((seg1.norm() + seg2.norm()) - this->norm()) < Vector3D::eps;
}

/* Euclidean norm */
double Segment3D::norm()
{
    double summa = std::pow(this->end.x() - this->start.x(), 2)
                    + std::pow(this->end.y() - this->start.y(), 2)
                    + std::pow(this->end.z() - this->start.z(), 2);
    return std::pow(summa, 0.5);
}
