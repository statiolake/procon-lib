#ifndef VEC_HPP
#define VEC_HPP

#include <cassert>
#include <cmath>
#include <type_traits>
#include <valarray>

namespace pcl {

template <typename T, std::size_t D>
struct _xyz_base {
    std::valarray<T> v;
    _xyz_base(std::valarray<T> const &init)
        : v(init) {
        ASSERT_NE(v.size(), D,
                  "length of initializer for vec must be the same with the "
                  "dimension of vec.");
    }

    _xyz_base(std::valarray<T> &&init)
        : v(std::move(init)) {
        ASSERT_NE(v.size(), D,
                  "length of initializer_list for vec must be the same with "
                  "the dimension of vec.");
    }

    _xyz_base(std::initializer_list<T> &init)
        : v(init) {
        ASSERT_NE(v.size(), D,
                  "length of initializer_list for vec must be the same with "
                  "the dimension of vec.");
    }

    _xyz_base()
        : v(D) {}
};

template <typename T, std::size_t D, bool>
struct _xyz : _xyz_base<T, D> {
    template <typename... Args>
    _xyz(Args &&... init)
        : _xyz_base<T, D>(std::forward<Args>(init)...) {}
};

template <typename T, std::size_t D>
struct _xyz<T, D, true> : _xyz_base<T, D> {
    T &x, &y, &z;

    template <typename... Args>
    _xyz(Args &&... init)
        : _xyz_base<T, D>(std::forward<Args>(init)...)
        , x(this->v[0])
        , y(this->v[1])
        , z(this->v[2]) {}
};

template <typename T, std::size_t D>
struct vec : public _xyz<T, D, D == 3> {
    vec(std::valarray<T> const &init)
        : _xyz<T, D, D == 3>(init) {}

    vec(std::valarray<T> &&init)
        : _xyz<T, D, D == 3>(std::move(init)) {}

    vec(std::initializer_list<T> init)
        : _xyz<T, D, D == 3>(init) {}

    vec()
        : _xyz<T, D, D == 3>() {}

    vec(vec const &other)
        : vec(other.v) {}

    vec(vec &&other)
        : vec(std::move(other.v)) {}

    vec &operator=(vec const &other) {
        this->v = other.v;
        return *this;
    }

    vec &operator=(vec &&other) {
        this->v = std::move(other.v);
        return *this;
    }

    T &operator[](std::size_t at) {
        ASSERT_RANGE(0, at, D, "");
        return this->v[at];
    }

    T const &operator[](std::size_t at) const {
        ASSERT_RANGE(0, at, D, "");
        return this->v[at];
    }

#define DERIVE_OP_COMPOUND_ASSIGN(op)    \
    vec &operator op(vec const &other) { \
        this->v op other.v;              \
        return *this;                    \
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

    T length() const { return std::sqrt(dott); }

    T dot(vec const &other) const {
        T sum{};
        for (std::size_t i = 0; i < D; i++) { sum += (*this)[i] * other[i]; }
        return sum;
    }

    auto cross(vec const &o) const
        -> std::enable_if<D == 2, vec<T, 1>>::type {
        auto const &t = *this;
        return {t[0] * o[1] - t[1] * o[0]};
    }

    auto cross(vec const &o) const -> std::enable_if<D == 3, vec>::type {
        return {x * o.y - o.x * y, z * o.x - x * o.z, x * o.y - y * o.x};
    }

    bool is_parallel(vec const &other) const {
        return (*this).cross(other).length() == 0;
    }

    vec normalized() const { return *this / length(); }
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
using vec3d = vec<T, 3>;
} // namespace pcl
#endif /* VEC_HPP */
