#include "vector3D.h"

#ifndef SEGMENT3D_H
#define SEGMENT3D_H

class Segment3D : Vector3D
{
private:
    Vector3D start;
    Vector3D end;
    std::string name;
    // TODO можно оптимизировать всю программу добавив вычисление направляющих векторов при инициализации

public:
    Segment3D(Vector3D Start, Vector3D End, std::string Name);
    Segment3D();

    std::string get_string_to_show();
    // Getters
    Vector3D getStart();
    Vector3D getEnd();

    // Setter
    void setName(std::string Name);
    // Intersection helps
    bool is_exists_equal_surface_to(Segment3D segment);
    double norm();
    struct Collinear{
        bool m_is_collinear;
        int m_det_number;
        double m_det = 0;
    };
    Collinear is_collinear_to_segment(Segment3D segment);
    bool is_consist_point(Vector3D point);
    bool is_line_with_segment_consist_point(Vector3D point);
    static double calc_u_to_segments(Segment3D seg1, Segment3D seg2, double eps, int non_zero_det);
    static double calc_v_to_segments(Segment3D seg1, Segment3D seg2, double eps, int non_zero_det);

    static Vector3D calc_intersection_point_by_uv_and_seg(double u, double v, Segment3D AB);

    // static calc_det3(Segment3D f_segment, Segment3D s_segment);
};

#endif // SEGMENT3D_H
