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
    std::array<dbl, DIM> arr;

  public:
    vec()
        : arr({0.0}) {}

    template <typename... Args>
    vec(Args... args)
        : arr({args...}) {}

    vec(vec const &other)
        : arr(other.arr) {}

    vec &operator=(vec const &other) { arr = other.arr; }

    dbl &operator[](int idx) {
        assert(in_range(0, idx, DIM));
        return arr[idx];
    }

    dbl operator[](int idx) const {
        assert(in_range(0, idx, DIM));
        return arr[idx];
    }

    dbl length() const {
        dbl len = 0;
        for (dbl x : *this) len += x * x;
        return std::sqrt(len);
    }

    vec normalized() const {
        vec result = *this;
        dbl len    = length();
        for (dbl &x : result) x /= len;
        return result;
    }

    auto begin() { return arr.begin(); }
    auto end() { return arr.end(); }
    auto begin() const { return cbegin(); }
    auto end() const { return cend(); }
    auto cbegin() const { return arr.begin(); }
    auto cend() const { return arr.cend(); }

    vec &operator+=(vec const &other) {
        for (int i = 0; i < DIM; i++) arr[i] += other[i];
        return *this;
    }

    vec &operator-=(vec const &other) {
        for (int i = 0; i < DIM; i++) arr[i] -= other[i];
        return *this;
    }

    vec &operator*=(dbl r) {
        for (dbl &x : *this) x *= r;
        return *this;
    }

    vec &operator/=(dbl r) {
        for (dbl &x : *this) x /= r;
        return *this;
    }
};

template <int DIM>
vec<DIM> operator+(vec<DIM> lhs, vec<DIM> const &rhs) {
    return lhs += rhs;
}

template <int DIM>
vec<DIM> operator-(vec<DIM> lhs, vec<DIM> const &rhs) {
    return lhs -= rhs;
}

template <int DIM>
vec<DIM> operator*(vec<DIM> lhs, dbl rhs) {
    return lhs *= rhs;
}

template <int DIM>
vec<DIM> operator*(dbl lhs, vec<DIM> rhs) {
    return rhs *= lhs;
}

template <int DIM>
vec<DIM> operator/(vec<DIM> lhs, dbl rhs) {
    return lhs /= rhs;
}

template <int DIM>
bool operator==(vec<DIM> const &lhs, vec<DIM> const &rhs) {
    for (int i = 0; i < DIM; i++)
        if (lhs[i] != rhs[i]) return false;
    return true;
}

template <int DIM>
inline bool operator!=(vec<DIM> const &lhs, vec<DIM> const &rhs) {
    return !(lhs == rhs);
}

template <int DIM>
dbl dot(vec<DIM> const &lhs, vec<DIM> const &rhs) {
    dbl result = 0.0;
    for (int i = 0; i < DIM; i++) result += lhs[i] * rhs[i];
    return result;
}

vec<3> cross(vec<2> const &lhs, vec<2> const &rhs) {
    return {0, 0, lhs[0] * rhs[1] - lhs[1] * rhs[0]};
}

vec<3> cross(vec<3> const &lhs, vec<3> const &rhs) {
    return {lhs[1] * rhs[2] - lhs[2] * rhs[1],
            lhs[2] * rhs[0] - lhs[0] * rhs[2],
            lhs[0] * rhs[1] - lhs[1] * rhs[0]};
}

template <int DIM>
bool is_parallel(vec<DIM> const &lhs, vec<DIM> const &rhs) {
    return cross(lhs, rhs).length() == 0;
}

// @brief check if the two parallel vectors directs the same direction. this
//        means that the sign of each element is the same
template <int DIM>
bool is_parallel_vecs_same_direction(vec<DIM> const &lhs,
                                     vec<DIM> const &rhs) {
    // this function can only be applied with parallel vecs.
    assert(is_parallel(lhs, rhs));

    for (std::size_t i = 0; i < DIM; i++)
        // lhs[i] * rhs[i] < 0 means lhs[i] and rhs[i] has the opposite sign.
        if (lhs[i] * rhs[i] < 0) return false;

    return true;
}

template <int DIM>
std::istream &operator>>(std::istream &is, vec<DIM> &v) {
    for (int i = 0; i < DIM; i++) is >> v[i];
    return is;
}

template <int DIM>
std::ostream &operator<<(std::ostream &os, vec<DIM> const &v) {
    for (int i = 0; i < DIM; i++) {
        if (i != 0) os << ' ';
        os << v[i];
    }
    return os;
}

using vec2 = vec<2>;
using vec3 = vec<3>;

template <int DIM>
using coord = vec<DIM>;

using coord2 = vec<2>;
using coord3 = vec<3>;
} // namespace pcl
