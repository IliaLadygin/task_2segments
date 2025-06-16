#include "vector3D.h"
#include "minorcalcs.cpp"

#ifndef SEGMENT3D_H
#define SEGMENT3D_H

class Segment3D : Vector3D
{
private:
    Vector3D start;
    Vector3D end;
    std::string name;
    // TODO можно оптимизировать всю программу добавив вычисление направляющих векторов

public:
    Segment3D(Vector3D Start, Vector3D End, std::string Name);

    std::string get_string_to_show();
    // Getters
    Vector3D getStart();
    Vector3D getEnd();
    // Intersection helps
    bool is_exists_equal_surface_to(Segment3D segment);
    bool is_collinear_to_segment(Segment3D segment);

    static double calc_u_to_segments(Segment3D seg1, Segment3D seg2);
    static double calc_v_to_segments(Segment3D seg1, Segment3D seg2);
    static Vector3D calc_intersection_point_by_uv_and_seg(double u, double v, Segment3D AB);

    // static calc_det3(Segment3D f_segment, Segment3D s_segment);
};

#endif // SEGMENT3D_H
