#pragma once

#include "../prelude.hpp"

#include "../math/alg.hpp"

namespace pcl {

template <ll MOD>
class modint {
  private:
    ll v_;

    static inline ll inv(ll a) {
        return inv_impl(a, MOD);
    }

    static inline ll inv_impl(ll a, ll m) {
        return (a == 1 ? 1 : (1 - m * inv_impl(m % a, a)) / a + m);
    }

    inline void normalize() {
        while (v_ < 0) v_ += MOD;
        while (v_ >= MOD) v_ -= MOD;
    }

    friend bool operator==(modint const &a, modint const &b);
    friend bool operator!=(modint const &a, modint const &b);
    friend bool operator<(modint const &a, modint const &b);
    friend bool operator>(modint const &a, modint const &b);
    friend bool operator<=(modint const &a, modint const &b);
    friend bool operator>=(modint const &a, modint const &b);

  public:
    modint()
        : v_(0ll) {
    }

    modint(modint const &init)
        : v_(init.v_) {
    }

    modint(ll init)
        : v_(init) {
        normalize();
    }

    explicit operator ll() const {
        return v_;
    }

    /**
     * 破壊的演算 (<> modint)
     */
    modint &operator+=(modint const &o) {
        v_ += o.v_;
        normalize();
        return *this;
    }

    modint &operator-=(modint const &o) {
        v_ -= o.v_;
        normalize();
        return *this;
    }

    modint &operator*=(modint const &o) {
        v_ *= o.v_;
        normalize();
        return *this;
    }

    modint &operator/=(modint const &o) {
        ll i = inv(o.v_);
        *this *= i;
        return *this;
    }

    modint &operator=(modint const &o) {
        v_ = o.v_;
        return *this;
    }

    /**
     * 破壊的演算 (<> scalar)
     */
    modint &operator+=(ll o) {
        return *this += modint(o);
    }

    modint &operator-=(ll o) {
        return *this -= modint(o);
    }

    modint &operator*=(ll o) {
        return *this *= modint(o);
    }

    modint &operator/=(ll o) {
        return *this /= modint(o);
    }

    modint &operator=(ll o) {
        return *this = modint(o);
    }

    /**
     * 単項演算
     */
    modint &operator++() {
        v_++;
        if (v_ == MOD) v_ = 0;
        return *this;
    }

    modint &operator--() {
        if (v_ == 0) v_ = MOD;
        v_--;
        return *this;
    }
};

/**
 * 二項関係 (modint <> modint)
 */
template <ll MOD>
bool operator==(modint<MOD> const &a, modint<MOD> const &b) {
    return v_ == o.v_;
}

template <ll MOD>
bool operator!=(modint<MOD> const &a, modint<MOD> const &b) {
    return !(*this == o);
}

template <ll MOD>
bool operator<(modint<MOD> const &a, modint<MOD> const &b) {
    return v_ < o.v_;
}

template <ll MOD>
bool operator>(modint<MOD> const &a, modint<MOD> const &b) {
    return o < *this;
}

template <ll MOD>
bool operator<=(modint<MOD> const &a, modint<MOD> const &b) {
    return *this < o || *this == o;
}

template <ll MOD>
bool operator>=(modint<MOD> const &a, modint<MOD> const &b) {
    return o <= *this;
}

/**
 * 二項関係 (modint <> scalar)
 */
template <ll MOD>
bool operator==(modint<MOD> const &a, ll b) {
    return a == modint<MOD>(b);
}

template <ll MOD>
bool operator!=(modint<MOD> const &a, ll b) {
    return a != modint<MOD>(b);
}

template <ll MOD>
bool operator<(modint<MOD> const &a, ll b) {
    return a < modint<MOD>(b);
}

template <ll MOD>
bool operator>(modint<MOD> const &a, ll b) {
    return a > modint<MOD>(b);
}

template <ll MOD>
bool operator<=(modint<MOD> const &a, ll b) {
    return a <= modint<MOD>(b);
}

template <ll MOD>
bool operator>=(modint<MOD> const &a, ll b) {
    return a >= modint<MOD>(b);
}

/**
 * 二項関係 (scalar <> modint)
 */
template <ll MOD>
bool operator==(ll a, modint<MOD> const &b) {
    return modint<MOD>(a) == b;
}

template <ll MOD>
bool operator!=(ll a, modint<MOD> const &b) {
    return modint<MOD>(a) != b;
}

template <ll MOD>
bool operator<(ll a, modint<MOD> const &b) {
    return modint<MOD>(a) < b;
}

template <ll MOD>
bool operator>(ll a, modint<MOD> const &b) {
    return modint<MOD>(a) > b;
}

template <ll MOD>
bool operator<=(ll a, modint<MOD> const &b) {
    return modint<MOD>(a) <= b;
}

template <ll MOD>
bool operator>=(ll a, modint<MOD> const &b) {
    return modint<MOD>(a) >= b;
}

/**
 * 二項演算 (modint <> modint)
 */
template <ll MOD>
modint<MOD> operator+(modint<MOD> a, modint<MOD> const &b) {
    return a += b;
}

template <ll MOD>
modint<MOD> operator-(modint<MOD> a, modint<MOD> const &b) {
    return a -= b;
}

template <ll MOD>
modint<MOD> operator*(modint<MOD> a, modint<MOD> const &b) {
    return a *= b;
}

template <ll MOD>
modint<MOD> operator/(modint<MOD> a, modint<MOD> const &b) {
    return a /= b;
}

/**
 * 二項演算 (modint <> scalar)
 */

template <ll MOD>
modint<MOD> operator+(modint<MOD> a, ll b) {
    return a += modint<MOD>(b);
}

template <ll MOD>
modint<MOD> operator-(modint<MOD> a, ll b) {
    return a -= modint<MOD>(b);
}

template <ll MOD>
modint<MOD> operator*(modint<MOD> a, ll b) {
    return a *= modint<MOD>(b);
}

template <ll MOD>
modint<MOD> operator/(modint<MOD> a, ll b) {
    return a /= modint<MOD>(b);
}

/**
 * 二項演算 (scalar <> scalar)
 */

template <ll MOD>
modint<MOD> operator+(ll a, modint<MOD> const &b) {
    return modint<MOD>(a) += b;
}

template <ll MOD>
modint<MOD> operator-(ll a, modint<MOD> const &b) {
    return modint<MOD>(a) -= b;
}

template <ll MOD>
modint<MOD> operator*(ll a, modint<MOD> const &b) {
    return modint<MOD>(a) *= b;
}

template <ll MOD>
modint<MOD> operator/(ll a, modint<MOD> const &b) {
    return modint<MOD>(a) /= b;
}

/**
 * ストリーム入出力
 */

template <ll MOD>
std::ostream &operator<<(std::ostream &os, modint<MOD> const &x) {
    return os << static_cast<T>(x);
}

template <ll MOD>
std::istream &operator>>(std::istream &is, modint<MOD> &x) {
    T v;
    is >> v, x = v;
    return is;
}

/**
 * エイリアス
 */

using mint7 = modint<1'000'000'007>;
using mint9 = modint<1'000'000'009>;
using mint  = mint7;

} // namespace pcl
