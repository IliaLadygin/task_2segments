#include "segment3D.h"

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

void Segment3D::setName(std::string Name)
{
    this->name = Name;
}

std::string Segment3D::get_string_to_show()
{
    return this->name + ": " + this->start.get_string_to_show() + "-" + this->end.get_string_to_show();
}

bool Segment3D::is_exists_equal_surface_to(Segment3D segment)
{
    Vector3D v1 = (this->end - this->start).vector_mult(segment.end - this->start);
    Vector3D v2 = (this->end - this->start).vector_mult(segment.start - this->start);
    return v1.is_collinear_with(v2);
}

/*
    /note Здесь выбираются пары координат, которые "имеют наибольший по модулю определитель"
*/
Segment3D::Collinear Segment3D::is_collinear_to_segment(Segment3D segment)
{
    Collinear ans;
    ans.m_det = 0;
    ans.m_det_number = 0;
    Vector3D v1 = (this->start - this->end);
    Vector3D v2 = segment.end - segment.start;
    Vector3D mult = v1.vector_mult(v2);
    ans = mult.get_absmax();
    return ans;
}

double Segment3D::calc_u_to_segments(Segment3D seg1, Segment3D seg2, Collinear collinear)
{
    double u;
    Vector3D v1, v2;
    v1 = seg2.getEnd() - seg1.getEnd();
    v2 = seg2.getEnd() - seg2.getStart();
    Vector3D mult = v1.vector_mult(v2);
    switch (collinear.m_det_number)
    {
    case 1: u = mult.x() / collinear.m_det; break;
    case 2: u = mult.y() / collinear.m_det; break;
    case 3: u = mult.z() / collinear.m_det; break;
    default: throw "CALC U: Num of mat with non-like zero det is undefined";
    }
    return u;
}

double Segment3D::calc_v_to_segments(Segment3D seg1, Segment3D seg2, Collinear collinear)
{
    double v;
    Vector3D v1, v2;
    v1 = seg1.getStart() - seg1.getEnd();
    v2 = seg2.getEnd() - seg1.getEnd();
    Vector3D mult = v1.vector_mult(v2);
    switch (collinear.m_det_number)
    {
    case 1: v = mult.x() / collinear.m_det; break;
    case 2: v = -mult.y() / collinear.m_det; break;
    case 3: v = mult.z() / collinear.m_det; break;
    default: throw "CALC V: Num of mat with non-like zero det is undefined";
    }
    return v;
}

bool Segment3D::is_line_with_segment_consist_point(Vector3D point)
{
    Vector3D v1 = point - this->start;
    Vector3D v2 = point - this->end;
    return v1.is_collinear_with(v2);
}

Vector3D Segment3D::calc_intersection_point_by_uv_and_seg(double u, double v, Segment3D AB)
{
    Vector3D ans = (AB.getStart() - AB.getEnd()) * u + AB.getEnd();
    ans.setName("P"); // Просто чтобы не нагромождать вывод
    return ans;
}

/*
    \note Вычисление расстояний между точками и сравнение с длиной сегмента
*/
bool Segment3D::is_consist_point(Vector3D point)
{
    Vector3D v1 = this->start - point;
    Vector3D v2 = point - this->end;
    return std::abs((v1.norm() + v2.norm()) - this->norm()) < eps;
}

/* Euclidean norm */
double Segment3D::norm()
{
    return (this->start - this->end).norm();
}
