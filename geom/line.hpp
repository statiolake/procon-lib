#pragma once

#include "../prelude.hpp"

#include "../wrapper/../wrapper/dbl.hpp"
#include "../struct/mat.hpp"
#include "../struct/vec.hpp"
#include "point.hpp"

#include <cassert>
#include <iostream>

namespace pcl {

template <int DIM>
class line {
  private:
    crd<DIM> const beg_, end_;
    vec<DIM> const dir_;

  public:
    line(crd<DIM> const &a, crd<DIM> const &b)
        : beg_(a)
        , end_(b)
        , dir_((b - a).normalized()) {
    }

    crd<DIM> const &beg() const {
        return beg_;
    }
    crd<DIM> const &end() const {
        return end_;
    }
    crd<DIM> const &dir() const {
        return dir_;
    }

    dbl dist_from(point<DIM> const &f) const {
        return cross(f - beg(), dir()).len();
    }

    vec<DIM> normal_from(point<DIM> const &f) const {
        assert(!has(f));
        return beg() + dot(f - beg(), dir()) * dir() - f;
    }

    bool has(point<DIM> const &p) const {
        return is_par(beg() - p, end() - p);
    }
};

template <int DIM>
class segment : public line<DIM> {
  private:
    dbl const len_;

  public:
    segment(crd<DIM> const &s, crd<DIM> const &e)
        : line<DIM>(s, e)
        , len_((e - s).len()) {
    }

    dbl len() const {
        return len_;
    }

    // intended to hide line's has() function.
    bool has(point<DIM> const &p) const {
        // triangle inequality
        return len() == (p - this->beg()).len() + (p - this->end()).len();
    }
};

template <int DIM>
bool operator==(line<DIM> const &a, line<DIM> const &b) {
    if (!is_par(a.dir(), b.dir())) return false;
    auto const &diff = a.beg() - b.beg();
    auto const &dir  = a.dir();
    return is_par(diff, dir);
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
    return a.beg() == b.beg() && a.end() == b.end();
}

template <int DIM>
bool on_plane(line<DIM> const &a, line<DIM> const &b) {
    return on_plane(a.beg(), a.end(), b.beg(), a.end());
}

template <int DIM>
bool have_itsc(line<DIM> const &a, line<DIM> const &b) {
    if (!on_plane(a, b)) return false;

    // if a and b is parallel AND a and b are NOT the same line, they
    // have intersection.
    if (a.dir() == b.dir() && a.dist_from(b.beg()) == 0) return false;

    return true;
}

template <int DIM>
bool have_itsc(line<DIM> const &a, segment<DIM> const &s, bool inclusive) {
    if (!on_plane(a, s)) return false;

    auto ds = vecarg_of_points(a.beg(), a.end(), s.beg());
    auto de = vecarg_of_points(a.beg(), a.end(), s.end());

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
bool have_itsc(segment<DIM> const &a, line<DIM> const &b, bool inclusive) {
    return have_itsc(b, a, inclusive);
}

template <int DIM>
bool have_itsc(segment<DIM> const &a, segment<DIM> const &b, bool inclusive) {
    line<DIM> const &ll = a;
    line<DIM> const &rr = b;
    return on_plane(a, b) && have_itsc(ll, b, inclusive) &&
           have_itsc(a, rr, inclusive);
}

template <int DIM>
crd<DIM> itsc(line<DIM> const &, line<DIM> const &, bool) {
    // line-line intersection is not yet supported.
    assert(false);
}

template <int DIM>
crd<DIM> itsc(line<DIM> const &a, segment<DIM> const &b, bool inclusive) {
    // assert these segments have an intersection.
    assert(have_itsc(a, b, inclusive));

    if (inclusive) {
        if (a.has(b.beg())) return b.beg();
        if (a.has(b.end())) return b.end();
    }

    dbl d1 = a.dist_from(b.beg());
    dbl d2 = a.dist_from(b.end());

    dbl t    = d1 / (d1 + d2);
    dbl dist = t * b.len();
    return b.beg() + dist * b.dir();
}

template <int DIM>
crd<DIM> itsc(segment<DIM> const &a, line<DIM> const &b, bool inclusive) {
    return itsc(b, a, inclusive);
}

template <int DIM>
crd<DIM> itsc(segment<DIM> const &a, segment<DIM> const &b, bool inclusive) {
    assert(have_itsc(a, b, inclusive));

    return itsc(static_cast<line<DIM> const &>(a), b, inclusive);
}

template <int DIM>
std::ostream &operator<<(std::ostream &os, segment<DIM> const &seg) {
    os << "segment { beg: " << seg.beg() << ", end: " << seg.end()
       << ", len: " << seg.len() << " }";
    return os;
}

template <int DIM>
std::ostream &operator<<(std::ostream &os, line<DIM> const &lin) {
    os << "line { beg: " << lin.beg() << ", dir: " << lin.dir() << " }";
    return os;
}

} // namespace pcl
