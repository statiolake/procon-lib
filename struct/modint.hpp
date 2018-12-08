#pragma once

#include "alg.hpp"
namespace pcl {

template <typename T = ll, T MOD = 1'000'000'007>
class modint_t {
  private:
    T value;

    static inline T inv(T a) { return inv_impl(a, MOD); }
    static inline T inv_impl(T a, T b) {
        return (a == 1 ? 1 : (1 - b * inv_impl(b % a, a)) / a + b);
    }

    inline void canonicalize() {
        while (value < 0) value += MOD;
        value %= MOD;
    }

  public:
    modint_t()
        : value() {}

    modint_t(modint_t const &init)
        : value(init.value) {}

    modint_t(T init)
        : value(init) {
        canonicalize();
    }

    operator T() const { return value; }

    modint_t &operator+=(modint_t const &other) {
        value += other.value;
        if (value >= MOD) value -= MOD;
        return *this;
    }

    modint_t &operator+=(T other) { return *this += modint_t(other); }

    modint_t &operator-=(modint_t const &other) {
        if (value < other.value) value += MOD;
        value -= other.value;
        return *this;
    }

    modint_t &operator-=(T other) { return *this -= modint_t(other); }

    modint_t &operator*=(modint_t const &other) {
        value *= other.value;
        value %= MOD;
        return *this;
    }

    modint_t &operator*=(T other) { return *this *= modint_t(other); }

    modint_t &operator/=(modint_t const &other) {
        T i = inv(other.value);
        *this *= i;
        return *this;
    }

    modint_t &operator/=(T other) { return *this /= modint_t(other); }

    bool operator==(modint_t const &other) const {
        return value == other.value;
    }
    bool operator==(T other) const { return *this == modint_t(other); };
    bool operator!=(modint_t const &other) const { return !(*this == other); }
    bool operator!=(T other) const { return *this != modint_t(other); };
    bool operator<(modint_t const &other) const {
        return value < other.value;
    }
    bool operator<(T other) const { return *this < modint_t(other); };
    bool operator>(modint_t const &other) const { return other < *this; }
    bool operator>(T other) const { return *this > modint_t(other); };

    bool operator<=(modint_t const &other) const {
        return *this < other || *this == other;
    }
    bool operator<=(T other) const { return *this <= modint_t(other); }
    bool operator>=(modint_t const &other) const { return other <= *this; }
    bool operator>=(T other) const { return *this >= modint_t(other); }

    modint_t &operator=(modint_t const &other) {
        value = other.value;
        return *this;
    }

    modint_t &operator=(T other) { return *this = modint_t(other); }

    modint_t &operator++() {
        value++;
        if (value == MOD) value = 0;
        return *this;
    }

    modint_t &operator--() {
        if (value == 0) value = MOD;
        value--;
        return *this;
    }
};

template <typename T, T MOD>
modint_t<T, MOD> operator+(modint_t<T, MOD> lhs,
                           modint_t<T, MOD> const &rhs) {
    return lhs += rhs;
}

template <typename T, T MOD, typename U,
          typename std::enable_if<std::is_convertible<U, T>::value,
                                  nullptr_t>::type = nullptr>
modint_t<T, MOD> operator+(modint_t<T, MOD> lhs, U rhs) {
    return lhs += rhs;
}

template <typename T, T MOD, typename U,
          typename std::enable_if<std::is_convertible<U, T>::value,
                                  nullptr_t>::type = nullptr>
modint_t<T, MOD> operator+(U lhs, modint_t<T, MOD> rhs) {
    return rhs += lhs;
}

template <typename T, T MOD>
modint_t<T, MOD> operator-(modint_t<T, MOD> lhs,
                           modint_t<T, MOD> const &rhs) {
    return lhs -= rhs;
}

template <typename T, T MOD, typename U,
          typename std::enable_if<std::is_convertible<U, T>::value,
                                  nullptr_t>::type = nullptr>
modint_t<T, MOD> operator-(modint_t<T, MOD> lhs, U rhs) {
    return lhs -= rhs;
}

template <typename T, T MOD, typename U,
          typename std::enable_if<std::is_convertible<U, T>::value,
                                  nullptr_t>::type = nullptr>
modint_t<T, MOD> operator-(U lhs, modint_t<T, MOD> const &rhs) {
    return modint_t<T, MOD>(lhs) -= rhs;
}

template <typename T, T MOD>
modint_t<T, MOD> operator*(modint_t<T, MOD> lhs,
                           modint_t<T, MOD> const &rhs) {
    return lhs *= rhs;
}

template <typename T, T MOD, typename U,
          typename std::enable_if<std::is_convertible<U, T>::value,
                                  nullptr_t>::type = nullptr>
modint_t<T, MOD> operator*(modint_t<T, MOD> lhs, U rhs) {
    return lhs *= rhs;
}

template <typename T, T MOD, typename U,
          typename std::enable_if<std::is_convertible<U, T>::value,
                                  nullptr_t>::type = nullptr>
modint_t<T, MOD> operator*(U lhs, modint_t<T, MOD> rhs) {
    return rhs *= lhs;
}

template <typename T, T MOD>
modint_t<T, MOD> operator/(modint_t<T, MOD> lhs,
                           modint_t<T, MOD> const &rhs) {
    return lhs /= rhs;
}

template <typename T, T MOD, typename U,
          typename std::enable_if<std::is_convertible<U, T>::value,
                                  nullptr_t>::type = nullptr>
modint_t<T, MOD> operator/(modint_t<T, MOD> lhs, U rhs) {
    return lhs /= rhs;
}

template <typename T, T MOD, typename U,
          typename std::enable_if<std::is_convertible<U, T>::value,
                                  nullptr_t>::type = nullptr>
modint_t<T, MOD> operator/(U lhs, modint_t<T, MOD> const &rhs) {
    return modint_t<T, MOD>(lhs) /= rhs;
}

template <typename T, T MOD>
std::ostream &operator<<(std::ostream &os, modint_t<T, MOD> const &x) {
    return os << static_cast<T>(x);
}

template <typename T, T MOD>
std::istream &operator>>(std::istream &is, modint_t<T, MOD> &x) {
    T v;
    is >> v, x = v;
    return is;
}

using mint_t  = modint_t<ll, 1'000'000'007>;
using mint9_t = modint_t<ll, 1'000'000'009>;

} // namespace pcl
