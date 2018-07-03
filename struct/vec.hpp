#ifndef VEC_HPP
#define VEC_HPP

#include <cassert>
#include <cmath>
#include <type_traits>
#include <valarray>

namespace pcl {

template <typename T, std::size_t D>
struct vec {
    std::valarray<T> v;
    vec()
        : v(D) {}
    vec(std::initializer_list<T> init)
        : v(init) {
        ASSERT_EQ(init.size(), D,
                  "the length of initializer_list is invalid.");
    }
    vec(vec const &other)
        : v(other.v) {}
    vec(vec &&other)
        : v(std::move(other.v)) {}

    vec &operator=(vec const &other) {
        v = other.v;
        return *this;
    }

    vec &operator=(vec &&other) {
        v = std::move(other.v);
        return *this;
    }

    T &operator[](std::size_t at) {
        ASSERT_RANGE(0, at, D, "vec subscription out of range.");
        return v[at];
    }

    T const &at(std::size_t at) const {
        ASSERT_RANGE(0, at, D, "vec subscription out of range.");
        return v[at];
    }

    T length() const { return std::sqrt(dot(*this)); }

    T dot(vec const &other) const {
        T sum{};
        for (std::size_t i = 0; i < D; i++) sum += at(i) * other.at(i);
        return sum;
    }

    bool is_parallel(vec const &other) const {
        return cross(other).length() == 0;
    }

    vec normalized() const { return *this / length(); }

#define DERIVE_OP_COMPOUND_ASSIGN(op)                                     \
    vec &operator op(vec const &other) {                                  \
        ASSERT_EQ(v.size(), other.v.size(), "dimension of vec differs."); \
        this->v op other.v;                                               \
        return *this;                                                     \
    }

#define DERIVE_OP_COMPOUND_ASSIGN_SCALAR(op) \
    vec &operator op(T const &other) {       \
        this->v op other;                    \
        return *this;                        \
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

#define DERIVE_OP(op)                                            \
    template <typename T, std::size_t D>                         \
    vec<T, D> operator op(vec<T, D> lhs, vec<T, D> const &rhs) { \
        return lhs op## = rhs;                                   \
    }

#define DERIVE_OP_SCALAR(op)                             \
    template <typename T, std::size_t D>                 \
    vec<T, D> operator op(vec<T, D> lhs, T const &rhs) { \
        return lhs op## = rhs;                           \
    }

DERIVE_OP(+)
DERIVE_OP(-)
DERIVE_OP(*)
DERIVE_OP(/)
DERIVE_OP_SCALAR(+)
DERIVE_OP_SCALAR(-)
DERIVE_OP_SCALAR(*)
DERIVE_OP_SCALAR(/)

#undef DERIVE_OP
#undef DERIVE_OP_SCALAR

template <typename T>
struct vec2d : vec<T, 2> {
    T &x = this->v[0], &y = this->v[1];
    using vec<T, 2>::vec;
    vec2d(vec2d const &other)
        : vec<T, 2>(other) {}
    vec2d(vec2d &&other)
        : vec<T, 2>(std::move(other)) {}

    vec2d &operator=(vec2d const &other) {
        vec<T, 2>::operator=(other);
        return *this;
    }

    vec2d &operator=(vec2d &&other) {
        vec<T, 2>::operator=(std::move(other));
        return *this;
    }

    T cross(vec2d const &other) const { return x * other.y - y * other.x; }

    vec2d normalized() const override { return vec<T, 2>::normalized(); }

#define DERIVE_OP_COMPOUND_ASSIGN(op)        \
    vec2d &operator op(vec2d const &other) { \
        vec<T, 2>::operator op(other);       \
        return *this;                        \
    }

#define DERIVE_OP_COMPOUND_ASSIGN_SCALAR(op) \
    vec2d &operator op(T const &other) {     \
        vec<T, 2>::operator op(other);       \
        return *this;                        \
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

#define DERIVE_OP(op)                                         \
    template <typename T>                                     \
    vec2d<T> operator op(vec2d<T> lhs, vec2d<T> const &rhs) { \
        return lhs op## = rhs;                                \
    }

#define DERIVE_OP_SCALAR(op)                           \
    template <typename T>                              \
    vec2d<T> operator op(vec2d<T> lhs, T const &rhs) { \
        return lhs op## = rhs;                         \
    }

DERIVE_OP(+)
DERIVE_OP(-)
DERIVE_OP(*)
DERIVE_OP(/)
DERIVE_OP_SCALAR(+)
DERIVE_OP_SCALAR(-)
DERIVE_OP_SCALAR(*)
DERIVE_OP_SCALAR(/)

#undef DERIVE_OP
#undef DERIVE_OP_SCALAR

template <typename T>
struct vec3d : vec<T, 3> {
    T &x = this->v[0], &y = this->v[1], &z = this->v[2];
    using vec<T, 3>::vec;
    vec3d(vec3d const &other)
        : vec<T, 3>(other) {}
    vec3d(vec3d &&other)
        : vec<T, 3>(std::move(other)) {}

    vec3d &operator=(vec3d const &other) {
        vec<T, 3>::operator=(other);
        return *this;
    }

    vec3d &operator=(vec3d &&other) {
        vec<T, 3>::operator=(std::move(other));
        return *this;
    }

    vec3d cross(vec3d const &other) const {
        T nx = x * other.y - other.x * y;
        T ny = z * other.x - x * other.z;
        T nz = x * other.y - y * other.x;

        return {std::move(nx), std::move(ny), std::move(nz)};
    }

    vec3d normalized() const { return vec<T, 3>::normalized(); }

#define DERIVE_OP_COMPOUND_ASSIGN(op)        \
    vec3d &operator op(vec3d const &other) { \
        vec<T, 3>::operator op(other);       \
        return *this;                        \
    }

#define DERIVE_OP_COMPOUND_ASSIGN_SCALAR(op) \
    vec3d &operator op(T const &other) {     \
        vec<T, 3>::operator op(other);       \
        return *this;                        \
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

#define DERIVE_OP(op)                                         \
    template <typename T>                                     \
    vec3d<T> operator op(vec3d<T> lhs, vec3d<T> const &rhs) { \
        return lhs op## = rhs;                                \
    }

#define DERIVE_OP_SCALAR(op)                           \
    template <typename T>                              \
    vec3d<T> operator op(vec3d<T> lhs, T const &rhs) { \
        return lhs op## = rhs;                         \
    }

DERIVE_OP(+)
DERIVE_OP(-)
DERIVE_OP(*)
DERIVE_OP(/)
DERIVE_OP_SCALAR(+)
DERIVE_OP_SCALAR(-)
DERIVE_OP_SCALAR(*)
DERIVE_OP_SCALAR(/)

#undef DERIVE_OP
#undef DERIVE_OP_SCALAR

} // namespace pcl
#endif /* VEC_HPP */
