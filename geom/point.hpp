#pragma once

#include "../prelude.hpp"

#include "../struct/dbl.hpp"
#include "../struct/vec.hpp"

namespace pcl {
template <int DIM>
using point = coord<DIM>;

template <int DIM>
dbl distance(point<DIM> const &a, point<DIM> const &b) {
    return (a - b).length();
}

enum class vec_argument {
    b_is_longer      = +1007,
    b_is_shorter     = +1003,
    is_same          = +997,
    a_is_zero        = +993,
    b_is_zero        = +991,
    counterclockwise = +1,
    clockwise        = -1,
    opposite         = +3,
};

// only works when on the same plane.
template <int DIM>
vec_argument vec_argument_of_vecs(vec<DIM> const &a, vec<DIM> const &b) {
    if (a == b) return vec_argument::is_same;
    if (a.length() == 0) return vec_argument::a_is_zero;
    if (b.length() == 0) return vec_argument::b_is_zero;

    auto c = cross(a, b);
    dbl p  = c[0] != 0 ? c[0] : c[1] != 0 ? c[1] : c[2];
    dbl d  = dot(a, b);
    if (p > 0) return vec_argument::counterclockwise;
    if (p < 0) return vec_argument::clockwise;
    if (d < 0) return vec_argument::opposite;
    if (a.length() < b.length()) return vec_argument::b_is_longer;
    return vec_argument::b_is_shorter;
}

template <int DIM>
vec_argument vec_argument_of_points(point<DIM> const &base,
                                    point<DIM> const &a,
                                    point<DIM> const &b) {
    return vec_argument_of_vecs(a - base, b - base);
}

bool is_opposite_rotation(vec_argument a, vec_argument b) {
    return static_cast<int>(a) * static_cast<int>(b) == -1;
}

bool is_same_rotation(vec_argument a, vec_argument b) {
    return static_cast<int>(a) * static_cast<int>(b) == 1;
}

bool on_the_same_plane(point<2> const &, point<2> const &, point<2> const &,
                       point<2> const &) {
    return true;
}

bool on_the_same_plane(point<3> const &a, point<3> b, point<3> c,
                       point<3> d) {
    b -= a, c -= a, d -= a;

    mat<dbl> coords = {
        {b[0], b[1], b[2]},
        {c[0], c[1], c[2]},
        {d[0], d[1], d[2]},
    };

    return coords.det() == 0;
}
} // namespace pcl
