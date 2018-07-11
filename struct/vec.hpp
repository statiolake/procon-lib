#ifndef VEC_HPP
#define VEC_HPP

#include <cassert>
#include <cmath>
#include <type_traits>
#include <valarray>

namespace pcl {

struct _vec {};

struct vec;

double dot(vec const &lhs, vec const &rhs);
vec cross(vec const &lhs, vec const &rhs);
bool is_parallel(vec const &lhs, vec const &rhs);
vec operator+(vec lhs, vec const &rhs);
vec operator-(vec lhs, vec const &rhs);
vec operator*(vec lhs, vec const &rhs);
vec operator/(vec lhs, vec const &rhs);
vec operator*(double lhs, vec rhs);
vec operator+(vec lhs, double rhs);
vec operator-(vec lhs, double rhs);
vec operator*(vec lhs, double rhs);
vec operator/(vec lhs, double rhs);

struct vec : public _vec {
  double x, y, z;

  vec()
      : x(0.0)
      , y(0.0)
      , z(0.0) {}
  vec(vec const &other)
      : x(other.x)
      , y(other.y)
      , z(other.z) {}
  vec(double x, double y, double z = 0.0)
      : x(x)
      , y(y)
      , z(z) {}
  vec &operator=(vec const &other) {
    x = other.x, y = other.y, z = other.z;
    return *this;
  }
  double &operator[](std::size_t at) {
    ASSERT_RANGE(0u, at, 3u, "vec subscription out of range.");
    switch (at) {
      case 0: return x;
      case 1: return y;
      case 2: return z;
    }
    return x; // unreachable, but stop warning.
  }
  double at(std::size_t at) const {
    double a = (*const_cast<vec *>(this))[at];
    return a;
  }
  double length() const { return std::sqrt(dot(*this, *this)); }
  vec normalized() const { return *this / length(); }
#define DERIVE_OP_COMPOUND_ASSIGN(op)         \
  vec &operator op(vec const &other) {        \
    x op other.x, y op other.y, z op other.z; \
    return *this;                             \
  }
#define DERIVE_OP_COMPOUND_ASSIGN_SCALAR(op) \
  vec &operator op(double const &other) {    \
    x op other, y op other, z op other;      \
    return *this;                            \
  }
  DERIVE_OP_COMPOUND_ASSIGN(+=)
  DERIVE_OP_COMPOUND_ASSIGN(-=)
  DERIVE_OP_COMPOUND_ASSIGN(*=)
  DERIVE_OP_COMPOUND_ASSIGN(/=)
  DERIVE_OP_COMPOUND_ASSIGN_SCALAR(+=)
  DERIVE_OP_COMPOUND_ASSIGN_SCALAR(-=)
  DERIVE_OP_COMPOUND_ASSIGN_SCALAR(*=)
  DERIVE_OP_COMPOUND_ASSIGN_SCALAR(/=)
#undef DERIVE_OP_COMPOUND_ASSIGN
#undef DERIVE_OP_COMPOUND_ASSIGN_SCALAR
};

#define DERIVE_OP(op) \
  vec operator op(vec lhs, vec const &rhs) { return lhs op## = rhs; }
#define DERIVE_OP_SCALAR_LHS(op) \
  vec operator op(double lhs, vec rhs) { return rhs op## = lhs; }
#define DERIVE_OP_SCALAR_RHS(op) \
  vec operator op(vec lhs, double rhs) { return lhs op## = rhs; }
DERIVE_OP(+)
DERIVE_OP(-)
DERIVE_OP(*)
DERIVE_OP(/)
DERIVE_OP_SCALAR_LHS(*)
DERIVE_OP_SCALAR_RHS(+)
DERIVE_OP_SCALAR_RHS(-)
DERIVE_OP_SCALAR_RHS(*)
DERIVE_OP_SCALAR_RHS(/)
#undef DERIVE_OP
#undef DERIVE_OP_SCALAR_LHS
#undef DERIVE_OP_SCALAR_RHS

bool operator==(vec const &lhs, vec const &rhs) {
  return eqdbl(lhs.x, rhs.x) && eqdbl(lhs.y, rhs.y) && eqdbl(lhs.z, rhs.z);
}
bool operator!=(vec const &lhs, vec const &rhs) { return !(lhs == rhs); }

double dot(vec const &lhs, vec const &rhs) {
  return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z);
}

vec cross(vec const &lhs, vec const &rhs) {
  return {lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z,
          lhs.x * rhs.y - lhs.y * rhs.x};
}

bool is_parallel(vec const &lhs, vec const &rhs) {
  return eqdbl(cross(lhs, rhs).length(), 0);
}

bool is_parallel_vecs_same_direction(vec const &lhs, vec const &rhs) {
  ASSERT(is_parallel(lhs, rhs), "only for parallel vecs.");
  for (std::size_t i = 0; i < 3; i++) {
    if (!ledbl(lhs.at(i) * rhs.at(i), 0)) return false;
  }
  return true;
}

std::ostream &operator<<(std::ostream &os, vec const &v) {
  return (os << "(" << v.x << ", " << v.y << ", " << v.z << ")");
}
using coord = vec;
} // namespace pcl
#endif /* VEC_HPP */
