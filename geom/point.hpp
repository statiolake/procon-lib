#pragma once

#include "../prelude.hpp"

#include "../struct/vec.hpp"
#include "../wrapper/../wrapper/dbl.hpp"

namespace pcl {
template <int DIM>
using point = coord<DIM>;

template <int DIM>
dbl distance(point<DIM> const &a, point<DIM> const &b) {
    return (a - b).length();
}

enum class vecarg {
    b_longer     = +1007,
    b_shorter    = +1003,
    same         = +997,
    a_zero       = +993,
    b_zero       = +991,
    counterclock = +1,
    clock        = -1,
    opposite     = +3,
};

// only works when on the same plane.
template <int DIM>
vecarg vecarg_of_vecs(vec<DIM> const &a, vec<DIM> const &b) {
    if (a == b) return vecarg::same;
    if (a.length() == 0) return vecarg::a_zero;
    if (b.length() == 0) return vecarg::b_zero;

    auto c = cross(a, b);
    dbl p  = c[0] != 0 ? c[0] : c[1] != 0 ? c[1] : c[2];
    dbl d  = dot(a, b);
    if (p > 0) return vecarg::counterclock;
    if (p < 0) return vecarg::clock;
    if (d < 0) return vecarg::opposite;
    if (a.length() < b.length()) return vecarg::b_longer;
    return vecarg::b_shorter;
}

template <int DIM>
vecarg vecarg_of_points(point<DIM> const &x, point<DIM> const &a,
                        point<DIM> const &b) {
    return vecarg_of_vecs(a - x, b - x);
}

bool is_rot_rev(vecarg a, vecarg b) {
    return static_cast<int>(a) * static_cast<int>(b) == -1;
}

bool is_rot_same(vecarg a, vecarg b) {
    return static_cast<int>(a) * static_cast<int>(b) == 1;
}

bool on_plane(point<2> const &, point<2> const &, point<2> const &,
              point<2> const &) {
    return true;
}

bool on_plane(point<3> const &a, point<3> b, point<3> c, point<3> d) {
    b -= a, c -= a, d -= a;

    mat<dbl> coords = {
        {b[0], b[1], b[2]},
        {c[0], c[1], c[2]},
        {d[0], d[1], d[2]},
    };

    return coords.det() == 0;
}

} // namespace pcl
