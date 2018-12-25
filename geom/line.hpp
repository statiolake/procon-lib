#pragma once

#include "../prelude.hpp"

#include "../struct/dbl.hpp"
#include "../struct/mat.hpp"
#include "../struct/vec.hpp"
#include "point.hpp"

#include <cassert>
#include <iostream>

namespace pcl {

template <int DIM>
class line {
  private:
    coord<DIM> const start_, end_;
    vec<DIM> const dir_;

  public:
    line(coord<DIM> const &a, coord<DIM> const &b)
        : start_(a)
        , end_(b)
        , dir_((b - a).normalized()) {}

    coord<DIM> const &start() const { return start_; }
    coord<DIM> const &end() const { return end_; }
    coord<DIM> const &dir() const { return dir_; }

    dbl distance_from(point<DIM> const &from) const { return cross(from - start(), dir()).length(); }

    vec<DIM> normal_from(point<DIM> const &from) const {
        assert(!has(from));
        dbl t = dot(from - start(), dir());
        return start() + t * dir() - from;
    }

    bool has(point<DIM> const &p) const { return is_parallel(start() - p, end() - p); }
};

template <int DIM>
class segment : public line<DIM> {
  private:
    dbl const length_;

  public:
    segment(coord<DIM> const &s, coord<DIM> const &e)
        : line<DIM>(s, e)
        , length_((e - s).length()) {}

    dbl length() const { return length_; }

    // intended to hide line's has() function.
    bool has(point<DIM> const &p) const {
        // triangle inequality
        return length() == (p - this->start()).length() + (p - this->end()).length();
    }
};

template <int DIM>
bool operator==(line<DIM> const &lhs, line<DIM> const &rhs) {
    if (!is_parallel(lhs.dir(), rhs.dir())) return false;
    auto const &diff = lhs.start() - rhs.start();
    auto const &dir  = lhs.dir();
    return is_parallel(diff, dir);
}

template <int DIM>
bool operator==(line<DIM> const &, segment<DIM> const &) {
    return false;
}

template <int DIM>
bool operator==(segment<DIM> const &s, line<DIM> const &l) {
    return l == s;
}

template <int DIM>
bool operator==(segment<DIM> const &lhs, segment<DIM> const &rhs) {
    return lhs.start() == rhs.start() && lhs.end() == rhs.end();
}

template <int DIM>
bool on_the_same_plane(line<DIM> const &lhs, line<DIM> const &rhs) {
    return on_the_same_plane(lhs.start(), lhs.end(), rhs.start(), lhs.end());
}

template <int DIM>
bool have_intersection(line<DIM> const &lhs, line<DIM> const &rhs) {
    if (!on_the_same_plane(lhs, rhs)) return false;

    // if lhs and rhs is parallel AND lhs and rhs are NOT the same line, they
    // have intersection.
    if (lhs.dir() == rhs.dir() && lhs.distance_from(rhs.start()) == 0) return false;

    return true;
}

template <int DIM>
bool have_intersection(line<DIM> const &l, segment<DIM> const &s, bool endpoints) {
    if (!on_the_same_plane(l, s)) return false;

    auto ds = vec_argument_of_points(l.start(), l.end(), s.start());
    auto de = vec_argument_of_points(l.start(), l.end(), s.end());

    if (is_opposite_rotation(ds, de)) return true;

    if (endpoints) {
        if (ds == vec_argument::a_is_zero) return true;
        if (ds == vec_argument::b_is_zero) return true;
        if (ds == vec_argument::b_is_longer) return true;
        if (ds == vec_argument::is_same) return true;
        if (ds == vec_argument::b_is_shorter) return true;

        if (de == vec_argument::b_is_longer) return true;
        if (de == vec_argument::is_same) return true;
        if (de == vec_argument::b_is_shorter) return true;
        if (de == vec_argument::a_is_zero) return true;
        if (de == vec_argument::b_is_zero) return true;
    }

    return false;
}

template <int DIM>
bool have_intersection(segment<DIM> const &lhs, line<DIM> const &rhs, bool endpoints) {
    return have_intersection(rhs, lhs, endpoints);
}

template <int DIM>
bool have_intersection(segment<DIM> const &lhs, segment<DIM> const &rhs, bool endpoints) {
    line<DIM> const &llhs = lhs;
    line<DIM> const &rrhs = rhs;
    return on_the_same_plane(lhs, rhs) && have_intersection(llhs, rhs, endpoints) && have_intersection(lhs, rrhs, endpoints);
}

template <int DIM>
coord<DIM> intersection(line<DIM> const &, line<DIM> const &, bool) {
    // line-line intersection is not yet supported.
    assert(false);
}

template <int DIM>
coord<DIM> intersection(line<DIM> const &lhs, segment<DIM> const &rhs, bool endpoints) {
    // assert these segments have an intersection.
    assert(have_intersection(lhs, rhs, endpoints));

    if (endpoints) {
        if (lhs.has(rhs.start())) return rhs.start();
        if (lhs.has(rhs.end())) return rhs.end();
    }

    dbl d1 = lhs.distance_from(rhs.start());
    dbl d2 = lhs.distance_from(rhs.end());

    dbl t    = d1 / (d1 + d2);
    dbl dist = t * rhs.length();
    return rhs.start() + dist * rhs.dir();
}

template <int DIM>
coord<DIM> intersection(segment<DIM> const &lhs, line<DIM> const &rhs, bool endpoints) {
    return intersection(rhs, lhs, endpoints);
}

template <int DIM>
coord<DIM> intersection(segment<DIM> const &lhs, segment<DIM> const &rhs, bool endpoints) {
    assert(have_intersection(lhs, rhs, endpoints));

    return intersection(static_cast<line<DIM> const &>(lhs), rhs, endpoints);
}

template <int DIM>
std::ostream &operator<<(std::ostream &os, segment<DIM> const &seg) {
    os << "segment { start: " << seg.start() << ", end: " << seg.end() << ", length: " << seg.length() << " }";
    return os;
}

template <int DIM>
std::ostream &operator<<(std::ostream &os, line<DIM> const &lin) {
    os << "line { start: " << lin.start() << ", dir: " << lin.dir() << " }";
    return os;
}
} // namespace pcl
