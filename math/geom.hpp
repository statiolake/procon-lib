#ifndef GEOM_HPP
#define GEOM_HPP

#include <iostream>

#include "../struct/vec.hpp"
#include "mat.hpp"

namespace pcl {
class segment {
  protected:
    double len_;
  public:
    coord const start;
    vec const dir;

    segment(segment const &o) : len_(o.len_), start(o.start), dir(o.dir) {}
    segment(coord const &s, coord const &e)
      : len_((e - s).len()),  start(s), dir((e - s).normalized()) {}

    virtual bool is_line() const { return false; }
    double len() const { return len_; }
    double distance_from(coord const &from) const { return cross(from - start, dir).len(); }
    vec normal_from(coord const &from) const {
      double t = dot(from - start, dir); return start + t * dir - from;
    }
};

class line : public segment {
  public:
    virtual bool is_line() const { return true; }
    line(line const &o) : segment(o.start, o.start + o.dir) { len_ = DNF; }
    line(coord const &start, coord const &end) : segment(start, end) { len_ = DNF; }
};

class sphere {
  private:
    coord center;
    double radius;

  public:
    sphere() {}
    sphere(coord const &center, double radius) : center(center), radius(radius) {}
};

double distance(coord const &a, coord const &b) { return (a - b).len(); }

bool on_same_plane(segment const &lhs, segment const &rhs) {
    auto a = lhs.dir;
    auto b = rhs.start - lhs.start;
    auto c = rhs.start + rhs.dir - lhs.start;
    mat<double> coords = { {a.x, a.y, a.z},
                           {b.x, b.y, b.z},
                           {c.x, c.y, c.z}, };
    return eqdbl(coords.det(), 0);
}

bool has_intersection(segment const &lhs, segment const &rhs) {
    if (!on_same_plane(lhs, rhs)) return false;
    if (is_parallel(lhs.dir, rhs.dir)) return false;

    auto check = [&](auto const &base, auto const &target) {
        if (target.is_line()) { return true; }
        PD_LIB(std::cerr << "[has_intersection] checking " << base << " and "
                         << target << std::endl);
        auto rela = target.start - base.start;
        auto relb = target.len() * target.dir + rela;
        auto c1   = cross(base.dir, rela);
        auto c2   = cross(base.dir, relb);

        ASSERT(is_parallel(c1, c2),
               "cross product not returned parallel vectors.");

        for (std::size_t i = 0; i < 3; i++) if (c1[i] * c2[i] > 0) return false;
        return true;
    };

    if (!check(lhs, rhs)) return false;
    if (!check(rhs, lhs)) return false;
    return true;
}

bool has_intersection(segment const &lhs, sphere const &rhs) {
    auto vec_normal = lhs.normal_from(rhs.center);
    if (eqdbl(vec_normal.len(), 0)) {
        PD_LIB(std::cerr << "[has_intersection] vec_normal is 0; maybe the "
                            "center of sphere is on the same line."
                         << std::endl);
        return ledbl(distance(rhs.center, lhs.start), lhs.len());
    } else if (vec_normal.len() > rhs.radius) {
        PD_LIB(
            std::cerr << "[has_intersection] len of vec_normal is larger "
                         "than radius. they can't have intersection."
                      << std::endl);
        return false;
    } else {
        PD_LIB(std::cerr << "[has_intersection] vec_normal: " << vec_normal << std::endl);
        vec_normal *= 2;
        segment seg_normal(rhs.center, rhs.center + vec_normal);
        return has_intersection(lhs, seg_normal);
    }
}

bool has_intersection(sphere const &lhs, segment const &rhs) {
    return has_intersection(rhs, lhs);
}

coord intersection(segment const &lhs, segment const &rhs) {
    ASSERT(has_intersection(lhs, rhs), "these segments have no intersection.");
    coord result;
    segment const *base   = &lhs;
    segment const *target = &rhs;

    if (base->is_line() && target->is_line()) {
        ASSERT(false, "line-line intersection is not yet implemented.");
    } else {
        if (target->is_line()) {
            ASSERT(!base->is_line(), "base must not be line here.");
            std::swap(base, target);
        }
        double d1 = base->distance_from(target->start);
        double d2 = base->distance_from(target->start + target->dir * target->len());
        double t  = d1 / (d1 + d2);
        return target->start + t * target->dir;
    }
}

std::ostream &operator<<(std::ostream &os, segment const &seg) {
    os << "segment { start: " << seg.start << ", direction: " << seg.dir << ", len: " << seg.len() << " }";
    return os;
}

std::ostream &operator<<(std::ostream &os, line const &lin) {
    os << "line { start: " << lin.start << ", direction: " << lin.dir << " }";
    return os;
}

std::ostream &operator<<(std::ostream &os, sphere const &sph) {
    os << "sphere { center: " << sph.center << ", radius: " << sph.radius << " }";
    return os;
}

} // namespace pcl
#endif /* GEOM_HPP */
