/**
 * @file wrapper/modint.hpp
 * @brief 自動的に剰余をとる整数型。
 */
#pragma once

#include "../prelude.hpp"

#include "../math/alg.hpp"

namespace pcl {

/**
 * @brief 自動的に剰余をとる整数型。
 * @details 自動的に `MOD` で割ったあまりをキープする。 `MOD` は素数であればよ
 * い (厳密には割り算をする全ての数字と互いに素であればよい) 。
 */
template <ll MOD>
class modint {
  private:
    /// 値
    ll v_;

    /// a の逆元を求める。除算で内部的に用いる。
    static inline ll inv(ll a) {
        return inv_impl(a, MOD);
    }

    /// a の逆元を求めるのに内部的に使える。
    static inline ll inv_impl(ll a, ll m) {
        return (a == 1 ? 1 : (1 - m * inv_impl(m % a, a)) / a + m);
    }

    /// `v_` の値を `0 <= v_ < MOD` にキープする関数。
    inline void normalize() {
        // v_ の符号にかかわらず、符号を保ったまま、絶対値だけ剰余をとったよう
        // な挙動をする。これは C++03 までは implementation-defined で、
        // (a/b)*b + a%b = a を満たしさえすればよかった。 C++11 で除算 (a/b)の
        // 結果が切り捨て (ゼロ方向に丸め) られることが規定されたので先の挙動
        // が保証された。
        v_ %= MOD;
        if (v_ < 0) v_ += MOD;
    }

    template <ll MOD_>
    friend bool operator==(modint<MOD_> const &a, modint<MOD_> const &b);

    template <ll MOD_>
    friend bool operator!=(modint<MOD_> const &a, modint<MOD_> const &b);

    template <ll MOD_>
    friend bool operator<(modint<MOD_> const &a, modint<MOD_> const &b);

    template <ll MOD_>
    friend bool operator>(modint<MOD_> const &a, modint<MOD_> const &b);

    template <ll MOD_>
    friend bool operator<=(modint<MOD_> const &a, modint<MOD_> const &b);

    template <ll MOD_>
    friend bool operator>=(modint<MOD_> const &a, modint<MOD_> const &b);

  public:
    /// デフォルトコンストラクタ
    modint()
        : v_(0ll) {
    }

    /// コピーコンストラクタ
    modint(modint const &init)
        : v_(init.v_) {
    }

    /**
     * @brief 指定された値で初期化するコンストラクタ。
     * @param[in] init 初期化する値
     * @details 指定された値は勝手に正規化されるため、 `0 <= init < MOD`
     * を満た していなくてもよい。
     */
    modint(ll init)
        : v_(init) {
        normalize();
    }

    /// `ll` へのキャスト演算子。
    explicit operator ll() const {
        return v_;
    }

    /*
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

    /*
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

    /*
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

/*
 * 二項関係 (modint <> modint)
 */

template <ll MOD>
bool operator==(modint<MOD> const &a, modint<MOD> const &b) {
    return a.v_ == b.v_;
}

template <ll MOD>
bool operator!=(modint<MOD> const &a, modint<MOD> const &b) {
    return !(a == b);
}

template <ll MOD>
bool operator<(modint<MOD> const &a, modint<MOD> const &b) {
    return a.v_ < b.v_;
}

template <ll MOD>
bool operator>(modint<MOD> const &a, modint<MOD> const &b) {
    return b < a;
}

template <ll MOD>
bool operator<=(modint<MOD> const &a, modint<MOD> const &b) {
    return a < b || a == b;
}

template <ll MOD>
bool operator>=(modint<MOD> const &a, modint<MOD> const &b) {
    return b <= a;
}

/*
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

/*
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

/*
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

/*
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

/*
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

/*
 * ストリーム入出力
 */

/// ストリーム出力演算子
template <ll MOD>
std::ostream &operator<<(std::ostream &os, modint<MOD> const &x) {
    return os << static_cast<ll>(x);
}

/// ストリーム入力演算子
template <ll MOD>
std::istream &operator>>(std::istream &is, modint<MOD> &x) {
    ll v;
    is >> v, x = v;
    return is;
}

/*
 * エイリアス
 */

/// 1,000,000,007 で割った余りに保たれる整数型。
using mint7 = modint<1'000'000'007>;

/// 1,000,000,009 で割った余りに保たれる整数型。
using mint9 = modint<1'000'000'009>;

/// `mint7` はよく用いられるため、最も使いやすいエイリアスを設定する。
using mint = mint7;

} // namespace pcl
