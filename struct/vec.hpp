#pragma once

#include "../prelude.hpp"

#include "../util/alias.hpp"
#include "dbl.hpp"

#include <array>
#include <cassert>
#include <cmath>
#include <type_traits>

namespace pcl {

template <int DIM>
class vec {
  private:
    std::array<dbl, DIM> elems_;

  public:
    vec()
        : elems_({0.0}) {
    }

    template <typename... Args>
    vec(Args... args)
        : elems_({args...}) {
    }

    vec(vec const &other)
        : elems_(other.elems_) {
    }

    vec &operator=(vec const &other) {
        elems_ = other.elems_;
        return *this;
    }

    dbl &operator[](int i) {
        assert(in_range(0, i, DIM));
        return elems_[i];
    }

    dbl operator[](int i) const {
        assert(in_range(0, i, DIM));
        return elems_[i];
    }

    dbl len() const {
        dbl len = 0;
        for (dbl x : *this) len += x * x;
        return std::sqrt(len);
    }

    vec normalized() const {
        vec res = *this;
        dbl l   = len();
        for (dbl &x : res) x /= l;
        return res;
    }

    auto begin() {
        return elems_.begin();
    }
    auto end() {
        return elems_.end();
    }
    auto begin() const {
        return cbegin();
    }
    auto end() const {
        return cend();
    }
    auto cbegin() const {
        return elems_.begin();
    }
    auto cend() const {
        return elems_.cend();
    }

    vec &operator+=(vec const &other) {
        for (int i = 0; i < DIM; i++) elems_[i] += other[i];
        return *this;
    }

    vec &operator-=(vec const &other) {
        for (int i = 0; i < DIM; i++) elems_[i] -= other[i];
        return *this;
    }

    vec &operator*=(dbl b) {
        for (dbl &x : *this) x *= b;
        return *this;
    }

    vec &operator/=(dbl b) {
        for (dbl &x : *this) x /= b;
        return *this;
    }
};

template <int DIM>
vec<DIM> operator+(vec<DIM> a, vec<DIM> const &b) {
    return a += b;
}

template <int DIM>
vec<DIM> operator-(vec<DIM> a, vec<DIM> const &b) {
    return a -= b;
}

template <int DIM>
vec<DIM> operator*(vec<DIM> a, dbl b) {
    return a *= b;
}

template <int DIM>
vec<DIM> operator*(dbl a, vec<DIM> b) {
    return b *= a;
}

template <int DIM>
vec<DIM> operator/(vec<DIM> a, dbl b) {
    return a /= b;
}

template <int DIM>
bool operator==(vec<DIM> const &a, vec<DIM> const &b) {
    for (int i = 0; i < DIM; i++)
        if (a[i] != b[i]) return false;
    return true;
}

template <int DIM>
inline bool operator!=(vec<DIM> const &a, vec<DIM> const &b) {
    return !(a == b);
}

template <int DIM>
dbl dot(vec<DIM> const &a, vec<DIM> const &b) {
    dbl res = 0.0;
    for (int i = 0; i < DIM; i++) res += a[i] * b[i];
    return res;
}

vec<3> cross(vec<2> const &a, vec<2> const &b) {
    return {0, 0, a[0] * b[1] - a[1] * b[0]};
}

vec<3> cross(vec<3> const &a, vec<3> const &b) {
    return {a[1] * b[2] - a[2] * b[1], a[2] * b[0] - a[0] * b[2],
            a[0] * b[1] - a[1] * b[0]};
}

template <int DIM>
bool is_par(vec<DIM> const &a, vec<DIM> const &b) {
    return cross(a, b).len() == 0;
}

// @brief check if the two parallel vectors directs the same direction. this
//        means that the sign of each element is the same
template <int DIM>
bool is_same_dir(vec<DIM> const &a, vec<DIM> const &b) {
    // this function can only be applied with parallel vecs.
    assert(is_par(a, b));

    for (std::size_t i = 0; i < DIM; i++)
        // a[i] * b[i] < 0 means a[i] and b[i] has the opposite sign.
        if (a[i] * b[i] < 0) return false;

    return true;
}

template <int DIM>
std::istream &operator>>(std::istream &is, vec<DIM> &v) {
    for (int i = 0; i < DIM; i++) is >> v[i];
    return is;
}

template <int DIM>
std::ostream &operator<<(std::ostream &os, vec<DIM> const &v) {
    os << '(';
    for (int i = 0; i < DIM; i++) {
        if (i != 0) os << ',';
        os << v[i];
    }
    os << ')';
    return os;
}

using vec2 = vec<2>;
using vec3 = vec<3>;

template <int DIM>
using crd = vec<DIM>;

using crd2 = vec<2>;
using crd3 = vec<3>;
} // namespace pcl
