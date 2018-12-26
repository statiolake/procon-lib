/**
 * @file wrapper/dbl.hpp
 * @brief 誤差を許容する比較を定義した浮動小数点数。
 */
#pragma once

#include "../prelude.hpp"

#include <cmath>
#include <iostream>
#include <type_traits>

namespace pcl {

/**
 * @brief 誤差を許容する比較を定義した浮動小数点数。
 * @details プリミティブの double とできるだけ同じ操作感を得ることを目指してい
 * る。オーバーロードを用意したため dbl と double の比較も可能。このとき
 * double は dbl 型に変換される。
 */
class dbl {
  private:
    /// 値
    double v;

    friend bool operator==(dbl const &a, dbl const &b);
    friend bool operator!=(dbl const &a, dbl const &b);
    friend bool operator<(dbl const &a, dbl const &b);
    friend bool operator>(dbl const &a, dbl const &b);
    friend bool operator<=(dbl const &a, dbl const &b);
    friend bool operator>=(dbl const &a, dbl const &b);

  public:
    /// デフォルトコンストラクタ
    dbl()
        : v() {
    }

    /// 指定された値で初期化するコンストラクタ
    dbl(double init)
        : v(init) {
    }

    /// コピーコンストラクタ
    dbl(dbl const &o) = default;

    /// double へのキャスト演算子
    explicit operator double() const {
        return v;
    }

    inline dbl &operator+=(dbl const &o) {
        v += o.v;
        return *this;
    }

    inline dbl &operator-=(dbl const &o) {
        v -= o.v;
        return *this;
    }

    inline dbl &operator*=(dbl const &o) {
        v *= o.v;
        return *this;
    }

    inline dbl &operator/=(dbl const &o) {
        v /= o.v;
        return *this;
    }

    inline dbl &operator=(dbl const &o) {
        v = o.v;
        return *this;
    }
};

inline dbl operator+(dbl a, dbl const &b) {
    return (a += b);
}

inline dbl operator-(dbl a, dbl const &b) {
    return (a -= b);
}

inline dbl operator*(dbl a, dbl const &b) {
    return (a *= b);
}

inline dbl operator/(dbl a, dbl const &b) {
    return (a /= b);
}

/**
 * @brief 二者が誤差を許容して等しければ真となる。
 * @details 二者の絶対値の差が `EPS` より小さければ真となる。
 */
inline bool operator==(dbl const &a, dbl const &b) {
    return std::abs(a.v - b.v) < EPS;
}

/// 単に `==` を反転したもの。
inline bool operator!=(dbl const &a, dbl const &b) {
    return !(a == b);
}

/// 真に小さいか、二者が誤差を許容して等しければ真となる。
inline bool operator<=(dbl const &a, dbl const &b) {
    return a.v < b.v || a == b;
}

/// 真に大きいか、二者が誤差を許容して等しければ真となる。
inline bool operator>=(dbl const &a, dbl const &b) {
    return a.v > b.v || a == b;
}

/**
 * @brief 単に `>=` を反転したもの。
 * @details 真に小さく、かつ、二者が誤差を許容しても等しくなければ真となる。
 */
inline bool operator<(dbl const &a, dbl const &b) {
    return !(a >= b);
}

/**
 * @brief 単に `<=` を反転したもの。
 * @details 真に大きく、かつ、二者が誤差を許容しても等しくなければ真となる。
 */
inline bool operator>(dbl const &a, dbl const &b) {
    return !(a <= b);
}

inline dbl operator+(dbl const &a, double b) {
    return a + dbl(b);
}

inline dbl operator-(dbl const &a, double b) {
    return a - dbl(b);
}

inline dbl operator*(dbl const &a, double b) {
    return a * dbl(b);
}

inline dbl operator/(dbl const &a, double b) {
    return a / dbl(b);
}

inline bool operator==(dbl const &a, double b) {
    return a == dbl(b);
}

inline bool operator!=(dbl const &a, double b) {
    return a != dbl(b);
}

inline bool operator<(dbl const &a, double b) {
    return a < dbl(b);
}

inline bool operator>(dbl const &a, double b) {
    return a > dbl(b);
}

inline bool operator<=(dbl const &a, double b) {
    return a <= dbl(b);
}

inline bool operator>=(dbl const &a, double b) {
    return a >= dbl(b);
}

inline dbl operator+(double a, dbl const &b) {
    return dbl(a) + b;
}

inline dbl operator-(double a, dbl const &b) {
    return dbl(a) - b;
}

inline dbl operator*(double a, dbl const &b) {
    return dbl(a) * b;
}

inline dbl operator/(double a, dbl const &b) {
    return dbl(a) / b;
}

inline bool operator==(double a, dbl const &b) {
    return dbl(a) == b;
}

inline bool operator!=(double a, dbl const &b) {
    return dbl(a) != b;
}

inline bool operator<(double a, dbl const &b) {
    return dbl(a) < b;
}

inline bool operator>(double a, dbl const &b) {
    return dbl(a) > b;
}

inline bool operator<=(double a, dbl const &b) {
    return dbl(a) <= b;
}

inline bool operator>=(double a, dbl const &b) {
    return dbl(a) >= b;
}

/// ストリーム入力イテレータ
std::istream &operator>>(std::istream &is, dbl &d) {
    double v;
    is >> v;
    d = v;
    return is;
}

/// ストリーム出力イテレータ
std::ostream &operator<<(std::ostream &os, dbl const &d) {
    os << (double)d;
    return os;
}

} // namespace pcl

namespace std {

/// 平方根を求める。
pcl::dbl sqrt(pcl::dbl const &a) {
    return pcl::dbl(sqrt(static_cast<double>(a)));
}

/// 最小値を求める。
pcl::dbl min(pcl::dbl const &a, pcl::dbl const &b) {
    return a < b ? a : b;
}

/// 最大値を求める。
pcl::dbl max(pcl::dbl const &a, pcl::dbl const &b) {
    return a < b ? b : a;
}

} // namespace std
