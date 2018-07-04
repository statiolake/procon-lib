#ifndef VEC_HPP
#define VEC_HPP

#include <cassert>
#include <cmath>
#include <type_traits>
#include <valarray>

namespace pcl {

template <typename T, std::size_t D>
class _vec_common;

template <typename T, std::size_t D>
class vec;

template <typename T, std::size_t D>
T dot(_vec_common<T, D> const &lhs, _vec_common<T, D> const &rhs);

template <typename T>
vec<T, 1> cross(vec<T, 2> const &lhs, vec<T, 2> const &rhs);

template <typename T>
vec<T, 3> cross(vec<T, 3> const &lhs, vec<T, 3> const &rhs);

template <typename T, std::size_t D>
bool is_parallel(vec<T, D> const &lhs, vec<T, D> const &rhs);

template <typename T, std::size_t D>
struct _vec_common {
    std::valarray<T> v;
    _vec_common()
        : v(D) {}
    _vec_common(std::initializer_list<T> init)
        : v(init) {
        ASSERT_EQ(init.size(), D,
                  "the length of initializer_list is invalid.");
    }
    _vec_common(_vec_common const &other)
        : v(other.v) {}
    _vec_common(_vec_common &&other)
        : v(std::move(other.v)) {}

    _vec_common &operator=(_vec_common const &other) {
        v = other.v;
        return *this;
    }

    _vec_common &operator=(_vec_common &&other) {
        v = std::move(other.v);
        return *this;
    }

    T &operator[](std::size_t at) {
        ASSERT_RANGE(0u, at, D, "_vec_common subscription out of range.");
        return v[at];
    }

    T const &at(std::size_t at) const {
        ASSERT_RANGE(0u, at, D, "_vec_common subscription out of range.");
        return v[at];
    }

    T length() const { return std::sqrt(dot(*this, *this)); }

#define DERIVE_OP_COMPOUND_ASSIGN(op)                    \
    _vec_common &operator op(_vec_common const &other) { \
        ASSERT_EQ(v.size(), other.v.size(),              \
                  "dimension of _vec_common differs.");  \
        this->v op other.v;                              \
        return *this;                                    \
    }

#define DERIVE_OP_COMPOUND_ASSIGN_SCALAR(op)   \
    _vec_common &operator op(T const &other) { \
        this->v op other;                      \
        return *this;                          \
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

#define DERIVE_OP(op)                                             \
    template <typename T, std::size_t D>                          \
    _vec_common<T, D> operator op(_vec_common<T, D> lhs,          \
                                  _vec_common<T, D> const &rhs) { \
        return lhs op## = rhs;                                    \
    }

#define DERIVE_OP_SCALAR(op)                                             \
    template <typename T, std::size_t D>                                 \
    _vec_common<T, D> operator op(_vec_common<T, D> lhs, T const &rhs) { \
        return lhs op## = rhs;                                           \
    }

#define DERIVE_OP_SCALAR_REV(op)                                         \
    template <typename T, std::size_t D>                                 \
    _vec_common<T, D> operator op(T const &lhs, _vec_common<T, D> rhs) { \
        return lhs op## = rhs;                                           \
    }

DERIVE_OP(+)
DERIVE_OP(-)
DERIVE_OP(*)
DERIVE_OP(/)
DERIVE_OP_SCALAR(*)
DERIVE_OP_SCALAR(/)
DERIVE_OP_SCALAR_REV(*)

#undef DERIVE_OP
#undef DERIVE_OP_SCALAR
#undef DERIVE_OP_SCALAR_REV

template <typename T, std::size_t D>
struct vec {};

template <typename T>
struct vec<T, 1> : _vec_common<T, 1> {
    T &x = this->v[0];
    using _vec_common<T, 1>::_vec_common;
    vec(vec const &other)
        : vec<T, 1>(other) {}
    vec(vec &&other)
        : vec<T, 1>(std::move(other)) {}

    vec &operator=(vec const &other) {
        vec<T, 1>::operator=(other);
        return *this;
    }

    vec &operator=(vec &&other) {
        vec<T, 1>::operator=(std::move(other));
        return *this;
    }

    vec normalized() const { return *this / _vec_common<T, 1>::length(); }

#define DERIVE_OP_COMPOUND_ASSIGN(op)    \
    vec &operator op(vec const &other) { \
        vec<T, 1>::operator op(other);   \
        return *this;                    \
    }

#define DERIVE_OP_COMPOUND_ASSIGN_SCALAR(op) \
    vec &operator op(T const &other) {       \
        vec<T, 1>::operator op(other);       \
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

template <typename T>
struct vec<T, 2> : _vec_common<T, 2> {
    T &x = this->v[0], &y = this->v[1];
    using _vec_common<T, 2>::_vec_common;
    vec(vec const &other)
        : _vec_common<T, 2>(other) {}
    vec(vec &&other)
        : _vec_common<T, 2>(std::move(other)) {}

    vec &operator=(vec const &other) {
        _vec_common<T, 2>::operator=(other);
        return *this;
    }

    vec &operator=(vec &&other) {
        _vec_common<T, 2>::operator=(std::move(other));
        return *this;
    }

    vec normalized() const { return *this / _vec_common<T, 2>::length(); }

#define DERIVE_OP_COMPOUND_ASSIGN(op)          \
    vec &operator op(vec const &other) {       \
        _vec_common<T, 2>::operator op(other); \
        return *this;                          \
    }

#define DERIVE_OP_COMPOUND_ASSIGN_SCALAR(op)   \
    vec &operator op(T const &other) {         \
        _vec_common<T, 2>::operator op(other); \
        return *this;                          \
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

template <typename T>
struct vec<T, 3> : _vec_common<T, 3> {
    T &x = this->v[0], &y = this->v[1], &z = this->v[2];
    using _vec_common<T, 3>::_vec_common;
    vec(vec const &other)
        : _vec_common<T, 3>(other) {}
    vec(vec &&other)
        : _vec_common<T, 3>(std::move(other)) {}

    vec &operator=(vec const &other) {
        _vec_common<T, 3>::operator=(other);
        return *this;
    }

    vec &operator=(vec &&other) {
        _vec_common<T, 3>::operator=(std::move(other));
        return *this;
    }

    vec normalized() const { return *this / _vec_common<T, 3>::length(); }

#define DERIVE_OP_COMPOUND_ASSIGN(op)          \
    vec &operator op(vec const &other) {       \
        _vec_common<T, 3>::operator op(other); \
        return *this;                          \
    }

#define DERIVE_OP_COMPOUND_ASSIGN_SCALAR(op)   \
    vec &operator op(T const &other) {         \
        _vec_common<T, 3>::operator op(other); \
        return *this;                          \
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

template <typename T, std::size_t D>
T dot(_vec_common<T, D> const &lhs, _vec_common<T, D> const &rhs) {
    T sum{};
    for (std::size_t i = 0; i < D; i++) sum += lhs.at(i) * rhs.at(i);
    return sum;
}

template <typename T>
vec<T, 1> cross(vec<T, 2> const &lhs, vec<T, 2> const &rhs) {
    return {lhs.x * rhs.y - lhs.y * rhs.x};
}

template <typename T>
vec<T, 3> cross(vec<T, 3> const &lhs, vec<T, 3> const &rhs) {
    T nx = lhs.y * rhs.z - lhs.z * rhs.y;
    T ny = lhs.z * rhs.x - lhs.x * rhs.z;
    T nz = lhs.x * rhs.y - lhs.y * rhs.x;

    return {std::move(nx), std::move(ny), std::move(nz)};
}

template <typename T, std::size_t D>
bool is_parallel(vec<T, D> const &lhs, vec<T, D> const &rhs) {
    return cross(lhs, rhs).length() == 0;
}

#define DEFINE_OP(op)                                            \
    template <typename T, std::size_t D>                         \
    vec<T, D> operator op(vec<T, D> lhs, vec<T, D> const &rhs) { \
        return lhs op## = rhs;                                   \
    }

#define DEFINE_OP_SCALAR(op)                             \
    template <typename T, std::size_t D>                 \
    vec<T, D> operator op(vec<T, D> lhs, T const &rhs) { \
        return lhs op## = rhs;                           \
    }

#define DEFINE_OP_SCALAR_REV(op)                         \
    template <typename T, std::size_t D>                 \
    vec<T, D> operator op(T const &lhs, vec<T, D> rhs) { \
        return rhs op## = lhs;                           \
    }

#define DEFINE_OP_COMP(op)                                         \
    template <typename T, std::size_t D>                           \
    bool operator op(vec<T, D> const &lhs, vec<T, D> const &rhs) { \
        auto res = lhs.v op rhs.v;                                 \
        for (std::size_t i = 0; i < D; i++)                        \
            if (!res[i]) return false;                             \
        return true;                                               \
    }

DEFINE_OP(+)
DEFINE_OP(-)
DEFINE_OP(*)
DEFINE_OP(/)
DEFINE_OP_SCALAR(*)
DEFINE_OP_SCALAR(/)
DEFINE_OP_SCALAR_REV(*)
DEFINE_OP_COMP(==)
DEFINE_OP_COMP(!=)

#undef DEFINE_OP
#undef DEFINE_OP_SCALAR
#undef DEFINE_OP_COMP

template <typename T, std::size_t D>
std::ostream &operator<<(std::ostream &os, vec<T, D> const &v) {
    os << "(";
    for (std::size_t i = 0; i < D; i++) {
        if (i != 0) os << ", ";
        os << v.at(i);
    }
    os << ")";
    return os;
}
} // namespace pcl
#endif /* VEC_HPP */
