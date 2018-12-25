#pragma once

#include "../prelude.hpp"

#include "../math/alg.hpp"

namespace pcl {

template <typename T, T MOD>
class modint {
  private:
    T value;

    static inline T inv(T a) { return inv_impl(a, MOD); }
    static inline T inv_impl(T a, T b) { return (a == 1 ? 1 : (1 - b * inv_impl(b % a, a)) / a + b); }

    inline void canonicalize() {
        while (value < 0) value += MOD;
        value %= MOD;
    }

  public:
    modint()
        : value() {}

    modint(modint const &init)
        : value(init.value) {}

    modint(T init)
        : value(init) {
        canonicalize();
    }

    explicit operator T() const { return value; }

    modint &operator+=(modint const &other) {
        value += other.value;
        if (value >= MOD) value -= MOD;
        return *this;
    }

    modint &operator+=(T other) { return *this += modint(other); }

    modint &operator-=(modint const &other) {
        if (value < other.value) value += MOD;
        value -= other.value;
        return *this;
    }

    modint &operator-=(T other) { return *this -= modint(other); }

    modint &operator*=(modint const &other) {
        value *= other.value;
        value %= MOD;
        return *this;
    }

    modint &operator*=(T other) { return *this *= modint(other); }

    modint &operator/=(modint const &other) {
        T i = inv(other.value);
        *this *= i;
        return *this;
    }

    modint &operator/=(T other) { return *this /= modint(other); }

    bool operator==(modint const &other) const { return value == other.value; }
    bool operator==(T other) const { return *this == modint(other); };
    bool operator!=(modint const &other) const { return !(*this == other); }
    bool operator!=(T other) const { return *this != modint(other); };
    bool operator<(modint const &other) const { return value < other.value; }
    bool operator<(T other) const { return *this < modint(other); };
    bool operator>(modint const &other) const { return other < *this; }
    bool operator>(T other) const { return *this > modint(other); };

    bool operator<=(modint const &other) const { return *this < other || *this == other; }
    bool operator<=(T other) const { return *this <= modint(other); }
    bool operator>=(modint const &other) const { return other <= *this; }
    bool operator>=(T other) const { return *this >= modint(other); }

    modint &operator=(modint const &other) {
        value = other.value;
        return *this;
    }

    modint &operator=(T other) { return *this = modint(other); }

    modint &operator++() {
        value++;
        if (value == MOD) value = 0;
        return *this;
    }

    modint &operator--() {
        if (value == 0) value = MOD;
        value--;
        return *this;
    }
};

template <typename T, T MOD>
modint<T, MOD> operator+(modint<T, MOD> lhs, modint<T, MOD> const &rhs) {
    return lhs += rhs;
}

template <typename T, T MOD, typename U, typename std::enable_if<std::is_convertible<U, T>::value, std::nullptr_t>::type = nullptr>
modint<T, MOD> operator+(modint<T, MOD> lhs, U rhs) {
    return lhs += rhs;
}

template <typename T, T MOD, typename U, typename std::enable_if<std::is_convertible<U, T>::value, std::nullptr_t>::type = nullptr>
modint<T, MOD> operator+(U lhs, modint<T, MOD> rhs) {
    return rhs += lhs;
}

template <typename T, T MOD>
modint<T, MOD> operator-(modint<T, MOD> lhs, modint<T, MOD> const &rhs) {
    return lhs -= rhs;
}

template <typename T, T MOD, typename U, typename std::enable_if<std::is_convertible<U, T>::value, std::nullptr_t>::type = nullptr>
modint<T, MOD> operator-(modint<T, MOD> lhs, U rhs) {
    return lhs -= rhs;
}

template <typename T, T MOD, typename U, typename std::enable_if<std::is_convertible<U, T>::value, std::nullptr_t>::type = nullptr>
modint<T, MOD> operator-(U lhs, modint<T, MOD> const &rhs) {
    return modint<T, MOD>(lhs) -= rhs;
}

template <typename T, T MOD>
modint<T, MOD> operator*(modint<T, MOD> lhs, modint<T, MOD> const &rhs) {
    return lhs *= rhs;
}

template <typename T, T MOD, typename U, typename std::enable_if<std::is_convertible<U, T>::value, std::nullptr_t>::type = nullptr>
modint<T, MOD> operator*(modint<T, MOD> lhs, U rhs) {
    return lhs *= rhs;
}

template <typename T, T MOD, typename U, typename std::enable_if<std::is_convertible<U, T>::value, std::nullptr_t>::type = nullptr>
modint<T, MOD> operator*(U lhs, modint<T, MOD> rhs) {
    return rhs *= lhs;
}

template <typename T, T MOD>
modint<T, MOD> operator/(modint<T, MOD> lhs, modint<T, MOD> const &rhs) {
    return lhs /= rhs;
}

template <typename T, T MOD, typename U, typename std::enable_if<std::is_convertible<U, T>::value, std::nullptr_t>::type = nullptr>
modint<T, MOD> operator/(modint<T, MOD> lhs, U rhs) {
    return lhs /= rhs;
}

template <typename T, T MOD, typename U, typename std::enable_if<std::is_convertible<U, T>::value, std::nullptr_t>::type = nullptr>
modint<T, MOD> operator/(U lhs, modint<T, MOD> const &rhs) {
    return modint<T, MOD>(lhs) /= rhs;
}

template <typename T, T MOD>
std::ostream &operator<<(std::ostream &os, modint<T, MOD> const &x) {
    return os << static_cast<T>(x);
}

template <typename T, T MOD>
std::istream &operator>>(std::istream &is, modint<T, MOD> &x) {
    T v;
    is >> v, x = v;
    return is;
}

using mint7 = modint<ll, 1'000'000'007>;
using mint9 = modint<ll, 1'000'000'009>;
using mint  = mint7;

} // namespace pcl
