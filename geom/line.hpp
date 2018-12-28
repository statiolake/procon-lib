#pragma once

#include "../prelude.hpp"

#include "../struct/mat.hpp"
#include "../struct/vec.hpp"
#include "../wrapper/../wrapper/dbl.hpp"
#include "point.hpp"

#include <cassert>
#include <iostream>

namespace pcl {

template <int DIM>
class line {
  private:
    coord<DIM> const start_, end_;
    vec<DIM> const direction_;

  public:
    line(coord<DIM> const &a, coord<DIM> const &b)
        : start_(a)
        , end_(b)
        , direction_((b - a).normalized()) {
    }

    coord<DIM> const &start() const {
        return start_;
    }

    coord<DIM> const &end() const {
        return end_;
    }

    coord<DIM> const &direction() const {
        return direction_;
    }

    dbl distance_from(point<DIM> const &f) const {
        return cross(f - start(), direction()).length();
    }

    vec<DIM> normal_from(point<DIM> const &f) const {
        assert(!has(f));
        return start() + dot(f - start(), direction()) * direction() - f;
    }

    bool has(point<DIM> const &p) const {
        return is_parallel(start() - p, end() - p);
    }
};

template <int DIM>
class segment : public line<DIM> {
  private:
    dbl const length_;

  public:
    segment(coord<DIM> const &s, coord<DIM> const &e)
        : line<DIM>(s, e)
        , length_((e - s).length()) {
    }

    dbl length() const {
        return length_;
    }

    // intended to hide line's has() function.
    bool has(point<DIM> const &p) const {
        // triangle inequality
        return length() ==
               (p - this->start()).length() + (p - this->end()).length();
    }
};

template <int DIM>
bool operator==(line<DIM> const &a, line<DIM> const &b) {
    if (!is_parallel(a.direction(), b.direction())) return false;
    auto const &diff = a.start() - b.start();
    auto const &dir  = a.direction();
    return is_parallel(diff, dir);
}

template <int DIM>
bool operator==(line<DIM> const &, segment<DIM> const &) {
    return false;
}

template <int DIM>
bool operator==(segment<DIM> const &s, line<DIM> const &a) {
    return a == s;
}

template <int DIM>
bool operator==(segment<DIM> const &a, segment<DIM> const &b) {
    return a.start() == b.start() && a.end() == b.end();
}

template <int DIM>
bool on_plane(line<DIM> const &a, line<DIM> const &b) {
    return on_plane(a.start(), a.end(), b.start(), a.end());
}

template <int DIM>
bool have_intersection(line<DIM> const &a, line<DIM> const &b) {
    if (!on_plane(a, b)) return false;

    // if a and b is parallel AND a and b are NOT the same line, they
    // have intersection.
    if (a.direction() == b.direction() && a.distance_from(b.start()) == 0)
        return false;

    return true;
}

template <int DIM>
bool have_intersection(line<DIM> const &a, segment<DIM> const &s,
                       bool inclusive) {
    if (!on_plane(a, s)) return false;

    auto ds = vecarg_of_points(a.start(), a.end(), s.start());
    auto de = vecarg_of_points(a.start(), a.end(), s.end());

    if (is_rot_rev(ds, de)) return true;

    if (inclusive) {
        if (ds == vecarg::a_zero) return true;
        if (ds == vecarg::b_zero) return true;
        if (ds == vecarg::b_longer) return true;
        if (ds == vecarg::same) return true;
        if (ds == vecarg::b_shorter) return true;

        if (de == vecarg::b_longer) return true;
        if (de == vecarg::same) return true;
        if (de == vecarg::b_shorter) return true;
        if (de == vecarg::a_zero) return true;
        if (de == vecarg::b_zero) return true;
    }

    return false;
}

template <int DIM>
bool have_intersection(segment<DIM> const &a, line<DIM> const &b,
                       bool inclusive) {
    return have_intersection(b, a, inclusive);
}

template <int DIM>
bool have_intersection(segment<DIM> const &a, segment<DIM> const &b,
                       bool inclusive) {
    line<DIM> const &ll = a;
    line<DIM> const &rr = b;
    return on_plane(a, b) && have_intersection(ll, b, inclusive) &&
           have_intersection(a, rr, inclusive);
}

template <int DIM>
coord<DIM> intersection_of(line<DIM> const &, line<DIM> const &, bool) {
    // line-line intersection is not yet supported.
    assert(false);
}

template <int DIM>
coord<DIM> intersection_of(line<DIM> const &a, segment<DIM> const &b,
                           bool inclusive) {
    // assert these segments have an intersection.
    assert(have_intersection(a, b, inclusive));

    if (inclusive) {
        if (a.has(b.start())) return b.start();
        if (a.has(b.end())) return b.end();
    }

    dbl d1 = a.distance_from(b.start());
    dbl d2 = a.distance_from(b.end());

    dbl t = d1 / (d1 + d2);
    dbl d = t * b.length();
    return b.start() + d * b.direction();
}

template <int DIM>
coord<DIM> intersection_of(segment<DIM> const &a, line<DIM> const &b,
                           bool inclusive) {
    return intersection_of(b, a, inclusive);
}

template <int DIM>
coord<DIM> intersection_of(segment<DIM> const &a, segment<DIM> const &b,
                           bool inclusive) {
    assert(have_intersection(a, b, inclusive));

    return intersection_of(static_cast<line<DIM> const &>(a), b, inclusive);
}

template <int DIM>
std::ostream &operator<<(std::ostream &os, segment<DIM> const &s) {
    os << "segment { start: " << s.start() << ", end: " << s.end()
       << ", length: " << s.length() << " }";
    return os;
}

template <int DIM>
std::ostream &operator<<(std::ostream &os, line<DIM> const &l) {
    os << "line { start: " << l.start() << ", direction: " << l.direction()
       << " }";
    return os;
}

} // namespace pcl
