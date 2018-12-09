#pragma once

#include "../prelude.hpp"

#include "../util/alias.hpp"

#include <array>
#include <cassert>
#include <cmath>
#include <type_traits>

namespace pcl {

template <int DIM>
class vec_t {
  private:
    std::array<double, DIM> arr;

  public:
    vec_t()
        : arr({0.0}) {}

    template <typename... Args>
    vec_t(Args... args)
        : arr({args...}) {}

    vec_t(vec_t const &other)
        : arr(other.arr) {}

    vec_t &operator=(vec_t const &other) { arr = other.arr; }

    double &operator[](int idx) {
        assert(in_range(0, idx, DIM));
        return arr[idx];
    }

    double operator[](int idx) const {
        assert(in_range(0, idx, DIM));
        return arr[idx];
    }

    double length() const {
        double len = 0;
        for (double x : *this) len += x * x;
        return sqrt(len);
    }

    vec_t normalized() const {
        vec_t result = *this;
        double len   = length();
        for (double &x : result) x /= len;
        return result;
    }

    auto begin() { return arr.begin(); }
    auto end() { return arr.end(); }
    auto begin() const { return cbegin(); }
    auto end() const { return cend(); }
    auto cbegin() const { return arr.begin(); }
    auto cend() const { return arr.cend(); }

    vec_t &operator+=(vec_t const &other) {
        for (int i = 0; i < DIM; i++) arr[i] += other[i];
        return *this;
    }

    vec_t &operator-=(vec_t const &other) {
        for (int i = 0; i < DIM; i++) arr[i] -= other[i];
        return *this;
    }

    vec_t &operator*=(double r) {
        for (double &x : *this) x *= r;
        return *this;
    }

    vec_t &operator/=(double r) {
        for (double &x : *this) x /= r;
        return *this;
    }
};

template <int DIM>
vec_t<DIM> operator+(vec_t<DIM> lhs, vec_t<DIM> const &rhs) {
    return lhs += rhs;
}

template <int DIM>
vec_t<DIM> operator-(vec_t<DIM> lhs, vec_t<DIM> const &rhs) {
    return lhs -= rhs;
}

template <int DIM>
vec_t<DIM> operator*(vec_t<DIM> lhs, double rhs) {
    return lhs *= rhs;
}

template <int DIM>
vec_t<DIM> operator*(double lhs, vec_t<DIM> rhs) {
    return rhs *= lhs;
}

template <int DIM>
vec_t<DIM> operator/(vec_t<DIM> lhs, double rhs) {
    return lhs /= rhs;
}

template <int DIM>
bool operator==(vec_t<DIM> const &lhs, vec_t<DIM> const &rhs) {
    for (int i = 0; i < DIM; i++)
        if (nedbl(lhs[i], rhs[i])) return false;
    return true;
}

template <int DIM>
inline bool operator!=(vec_t<DIM> const &lhs, vec_t<DIM> const &rhs) {
    return !(lhs == rhs);
}

template <int DIM>
double dot(vec_t<DIM> const &lhs, vec_t<DIM> const &rhs) {
    double result = 0.0;
    for (int i = 0; i < DIM; i++) result += lhs[i] * rhs[i];
    return result;
}

vec_t<3> cross(vec_t<3> const &lhs, vec_t<3> const &rhs) {
    return {lhs[1] * rhs[2] - lhs[2] * rhs[1],
            lhs[2] * rhs[0] - lhs[0] * rhs[2],
            lhs[0] * rhs[1] - lhs[1] * rhs[0]};
}

template <int DIM>
bool is_parallel(vec_t<DIM> const &lhs, vec_t<DIM> const &rhs) {
    return eqdbl(cross(lhs, rhs).length(), 0);
}

// @brief check if the two parallel vectors directs the same direction. this
//        means that the sign of each element is the same
template <int DIM>
bool is_parallel_vecs_same_direction(vec_t<DIM> const &lhs,
                                     vec_t<DIM> const &rhs) {
    // this function can only be applied with parallel vecs.
    assert(is_parallel(lhs, rhs));

    for (std::size_t i = 0; i < DIM; i++)
        // lhs[i] * rhs[i] < 0 means lhs[i] and rhs[i] has the opposite sign.
        if (ltdbl(lhs[i] * rhs[i], 0)) return false;

    return true;
}

template <int DIM>
std::istream &operator>>(std::istream &is, vec_t<DIM> &v) {
    for (int i = 0; i < DIM; i++) is >> v[i];
    return is;
}

template <int DIM>
std::ostream &operator<<(std::ostream &os, vec_t<DIM> const &v) {
    for (int i = 0; i < DIM; i++) {
        if (i != 0) os << ' ';
        os << v[i];
    }
    return os;
}

using vec2_t = vec_t<2>;
using vec3_t = vec_t<3>;

using coord_t = vec_t<2>;
} // namespace pcl
