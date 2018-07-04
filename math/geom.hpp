#ifndef GEOM_HPP
#define GEOM_HPP

#include <iostream>

#include "../struct/vec.hpp"
#include "dbl.hpp"
#include "mat.hpp"
namespace pcl {
template <std::size_t D>
using vecdbl = vec<dbl, D>;

template <std::size_t D>
using coorddbl = vecdbl<D>;

template <std::size_t D>
class segment {
  private:
    std::pair<dbl, dbl> range;

  public:
    coorddbl<D> start;
    vecdbl<D> dir;

    segment(segment const &other)
        : range(other.range)
        , start(other.start)
        , dir(other.dir) {}

    segment(coorddbl<D> const &start, coorddbl<D> const &end)
        : range(0, (end - start).length())
        , start(start)
        , dir((end - start).normalized()) {}

    virtual bool is_line() const { return false; }
    virtual dbl length() const { return range.second - range.first; }
    virtual dbl range_begin() const { return range.first; }
    virtual dbl range_end() const { return range.second; }

    dbl distance_from(coorddbl<D> const &from) {
        vecdbl<D> a = from - start;
        return cross(a, dir);
    }

    vecdbl<D> normal_from(coorddbl<D> const &from) const {
        dbl t = dot(from - start, dir);
        return start + t * dir - from;
    }
};

template <std::size_t D>
class line : public segment<D> {
  public:
    line(line const &other)
        : segment<D>(other.start, other.start + other.dir) {}
    line(coorddbl<D> const &start, coorddbl<D> const &end)
        : segment<D>(start, end) {}

    virtual bool is_line() const override { return true; }
    virtual dbl length() const override { return DNF; }
    virtual dbl range_begin() const override { return -DNF; }
    virtual dbl range_end() const override { return DNF; }
};

template <std::size_t D>
struct sphere {
    coorddbl<D> center;
    dbl radius;

    sphere() {}
    sphere(coorddbl<D> const &center, dbl radius)
        : center(center)
        , radius(radius) {}
    sphere(coorddbl<D> &&center, dbl radius)
        : center(center)
        , radius(radius) {}
};

template <std::size_t D>
dbl distance(coorddbl<D> const &a, coorddbl<D> const &b) {
    return std::sqrt(dot(a, b));
}

bool on_same_plane(segment<2> const &, segment<2> const &) { return true; }

bool on_same_plane(segment<3> const &lhs, segment<3> const &rhs) {
    auto a = lhs.dir;
    auto b = rhs.start - lhs.start;
    auto c = rhs.start + rhs.dir - lhs.start;

    mat<dbl> coords = {
        {a.x, a.y, a.z},
        {b.x, b.y, b.z},
        {c.x, c.y, c.z},
    };
    return coords.det() == 0;
}

template <std::size_t D>
bool has_intersection(segment<D> const &lhs, segment<D> const &rhs) {
    if (!on_same_plane(lhs, rhs)) return false;
    if (is_parallel(lhs.dir, rhs.dir)) return false;

    auto check = [&](auto const &base, auto const &target) {
        if (target.is_line()) { return true; }
        PD_LIB(std::cerr << "[has_intersection] checking " << base << " and "
                         << target << std::endl);
        ASSERT(
            in_range(-DNF, {target.range_begin(), target.range_end()}, DNF),
            "internal error: there must not be half-line in current "
            "implementation.");
        auto rela = target.start - base.start;
        auto relb = target.length() * target.dir + rela;
        auto c1   = cross(base.dir, rela);
        auto c2   = cross(base.dir, relb);

        ASSERT(is_parallel(c1, c2),
               "cross product not returned parallel vectors.");

        for (std::size_t i = 0; i < D; i++) {
            if (c1[i] * c2[i] > 0) return false;
        }
        return true;
    };

    if (!check(lhs, rhs)) return false;
    if (!check(rhs, lhs)) return false;
    return true;
}

template <std::size_t D>
bool has_intersection(segment<D> const &lhs, sphere<D> const &rhs) {
    auto vec_normal = lhs.normal_from(rhs.center);
    if (vec_normal.length() == 0) {
        PD_LIB(std::cerr << "[has_intersection] vec_normal is 0; maybe the "
                            "center of sphere is on the same line."
                         << std::endl);
        return distance(rhs.center, lhs.start) <= lhs.length();
    } else if (vec_normal.length() > rhs.radius) {
        PD_LIB(
            std::cerr << "[has_intersection] length of vec_normal is larger "
                         "than radius. they can't have intersection."
                      << std::endl);
        return false;
    } else {
        PD_LIB(std::cerr << "[has_intersection] vec_normal: " << vec_normal
                         << std::endl);
        vec_normal *= dbl(2);
        segment<D> seg_normal(rhs.center, rhs.center + vec_normal);
        return has_intersection(lhs, seg_normal);
    }
}

template <std::size_t D>
bool has_intersection(sphere<D> const &lhs, segment<D> const &rhs) {
    return has_intersection(rhs, lhs);
}

template <std::size_t D>
coorddbl<D> intersection(segment<D> const &lhs, segment<D> const &rhs) {
    ASSERT(has_intersection(lhs, rhs),
           "these segments have no intersection.");
    coorddbl<D> result;
    segment<D> const *base   = &lhs;
    segment<D> const *target = &rhs;

    if (base->is_line() && target->is_line()) {
        ASSERT(false, "line-line intersection is not yet implemented.");
    } else {
        if (target->is_line()) {
            ASSERT(!base->is_line(), "base must not be line here.");
            std::swap(base, target);
        }
        dbl d1 = base->distance_from(target.start);
        dbl d2 = base->distance_from(target->start +
                                     target->dir * target.length());
        dbl t  = d1 / (d1 + d2);
        return target->start + t * target->dir;
    }
}

template <std::size_t D>
std::ostream &operator<<(std::ostream &os, segment<D> const &seg) {
    os << "segment { start: " << seg.start << ", direction: " << seg.dir
       << ", length: " << seg.length() << " }";
    return os;
}

template <std::size_t D>
std::ostream &operator<<(std::ostream &os, line<D> const &lin) {
    os << "line { start: " << lin.start << ", direction: " << lin.dir << " }";
    return os;
}

template <std::size_t D>
std::ostream &operator<<(std::ostream &os, sphere<D> const &sph) {
    os << "sphere { center: " << sph.center << ", radius: " << sph.radius
       << " }";
    return os;
}

using vec2d     = vecdbl<2>;
using vec3d     = vecdbl<3>;
using coord2d   = coorddbl<2>;
using coord3d   = coorddbl<3>;
using segment2d = segment<2>;
using segment3d = segment<3>;
using line2d    = line<2>;
using line3d    = line<3>;
using sphere2d  = sphere<2>;
using sphere3d  = sphere<3>;

} // namespace pcl
#endif /* GEOM_HPP */
