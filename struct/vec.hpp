/**
 * @file struct/vec.hpp
 * @brief N 次元ベクトル
 */
#pragma once

#include "../prelude.hpp"

#include "../util/alias.hpp"
#include "../wrapper/dbl.hpp"

#include <array>
#include <cassert>
#include <cmath>
#include <type_traits>

namespace pcl {

/// DIM 次元ベクトル
template <int DIM>
class vec {
  private:
    /// 各成分
    std::array<dbl, DIM> elems_;

  public:
    /// デフォルトコンストラクタ
    vec()
        : elems_({}) {
    }

    /// コンストラクタ。各成分をそのまま引数に渡す (可変長) 。
    template <typename... Args>
    vec(Args... args)
        : elems_({args...}) {
    }

    /// コピーコンストラクタ。
    vec(vec const &other) = default;

    /// 代入演算子。
    vec &operator=(vec const &other) {
        elems_ = other.elems_;
        return *this;
    }

    /**
     * @brief 添字アクセサ (参照版 - 代入可能) 。
     * @param[in] i インデックス
     * @return i 番目の成分
     * @details x 成分、 y 成分ではなく [0] や [1] を使う。範囲外アクセスはチ
     * ェックされる。
     */
    dbl &operator[](int i) {
        assert(in_range(0, i, DIM));
        return elems_[i];
    }

    /**
     * @brief 添字アクセサ (コピー版 - const 使用可能) 。
     * @param[in] i インデックス
     * @return i 番目の成分
     * @details x 成分、 y 成分ではなく [0] や [1] を使う。範囲外アクセスはチ
     * ェックされる。
     */
    dbl operator[](int i) const {
        assert(in_range(0, i, DIM));
        return elems_[i];
    }

    /**
     * @brief ベクトルの長さ。
     * @return 長さ
     */
    dbl len() const {
        dbl len = 0;
        for (dbl x : *this) len += x * x;
        return std::sqrt(len);
    }

    /**
     * @brief 正規化されたベクトル (同じ向きの単位ベクトル) を作って返す。
     * @return 正規化されたベクトル
     * @details コピーを作って返すので自身を破壊しない。 const 使用可能。
     */
    vec normalized() const {
        vec res = *this;
        dbl l   = len();
        for (dbl &x : res) x /= l;
        return res;
    }

    /// 各要素へのイテレータを返す。
    auto begin() {
        return elems_.begin();
    }

    /// 各要素へのイテレータを返す。
    auto end() {
        return elems_.end();
    }

    /// 各要素へのイテレータを返す。
    auto begin() const {
        return cbegin();
    }

    /// 各要素へのイテレータを返す。
    auto end() const {
        return cend();
    }

    /// 各要素へのイテレータを返す。
    auto cbegin() const {
        return elems_.begin();
    }

    /// 各要素へのイテレータを返す。
    auto cend() const {
        return elems_.cend();
    }

    vec &operator+=(vec const &other) {
        for (int i = 0; i < DIM; i++) elems_[i] += other[i];
        return *this;
    }

    vec &operator-=(vec const &other) {
        for (int i = 0; i < DIM; i++) elems_[i] -= other[i];
        return *this;
    }

    vec &operator*=(dbl b) {
        for (dbl &x : *this) x *= b;
        return *this;
    }

    vec &operator/=(dbl b) {
        for (dbl &x : *this) x /= b;
        return *this;
    }
};

template <int DIM>
vec<DIM> operator+(vec<DIM> a, vec<DIM> const &b) {
    return a += b;
}

template <int DIM>
vec<DIM> operator-(vec<DIM> a, vec<DIM> const &b) {
    return a -= b;
}

template <int DIM>
vec<DIM> operator*(vec<DIM> a, dbl b) {
    return a *= b;
}

template <int DIM>
vec<DIM> operator*(dbl a, vec<DIM> b) {
    return b *= a;
}

template <int DIM>
vec<DIM> operator/(vec<DIM> a, dbl b) {
    return a /= b;
}

template <int DIM>
bool operator==(vec<DIM> const &a, vec<DIM> const &b) {
    for (int i = 0; i < DIM; i++)
        if (a[i] != b[i]) return false;
    return true;
}

template <int DIM>
inline bool operator!=(vec<DIM> const &a, vec<DIM> const &b) {
    return !(a == b);
}

/**
 * @brief 二つのベクトルの内積をとる。
 * @return 内積
 */
template <int DIM>
dbl dot(vec<DIM> const &a, vec<DIM> const &b) {
    dbl res = 0.0;
    for (int i = 0; i < DIM; i++) res += a[i] * b[i];
    return res;
}

/**
 * @brief 二次元ベクトルの外積をとる。
 * @return 外積 (z 座標のみをもつ **三次元** ベクトルで返される)
 * @details 返されるベクトルの x, y 座標はどちらも 0 になる。
 */
vec<3> cross(vec<2> const &a, vec<2> const &b) {
    return {0, 0, a[0] * b[1] - a[1] * b[0]};
}

/**
 * @brief 三次元ベクトルの外積をとる。
 * @return 外積
 * @details 外積は二次元と三次元のベクトルにのみ提供されている。
 */
vec<3> cross(vec<3> const &a, vec<3> const &b) {
    return {a[1] * b[2] - a[2] * b[1], a[2] * b[0] - a[0] * b[2],
            a[0] * b[1] - a[1] * b[0]};
}

/**
 * @brief 二つのベクトルが平行かどうか判定する。
 * @return 平行なら true
 * @details 現在の実装は、外積をとってその大きさが 0 となれば平行と判断すると
 * いうもの。
 */
template <int DIM>
bool is_par(vec<DIM> const &a, vec<DIM> const &b) {
    return cross(a, b).len() == 0;
}

/**
 * @brief 二つの **平行なベクトル** が同じ向きを向いているか (正負みたいなもの
 * が一致するか) を判定する。
 * @return 同じ向きなら true
 * @details ベクトルが平行であることは前提とする。平行でないベクトルについて呼
 * び出された場合は assert により強制終了する。
 */
template <int DIM>
bool is_same_dir(vec<DIM> const &a, vec<DIM> const &b) {
    // this function can only be applied with parallel vecs.
    assert(is_par(a, b));

    for (std::size_t i = 0; i < DIM; i++)
        // a[i] * b[i] < 0 means a[i] and b[i] has the opposite sign.
        if (a[i] * b[i] < 0) return false;

    return true;
}

/// ストリーム入力演算子
template <int DIM>
std::istream &operator>>(std::istream &is, vec<DIM> &v) {
    for (int i = 0; i < DIM; i++) is >> v[i];
    return is;
}

/// ストリーム出力演算子
template <int DIM>
std::ostream &operator<<(std::ostream &os, vec<DIM> const &v) {
    os << '(';
    for (int i = 0; i < DIM; i++) {
        if (i != 0) os << ',';
        os << v[i];
    }
    os << ')';
    return os;
}

/// 二次元ベクトルの型エイリアス
using vec2 = vec<2>;

/// 三次元ベクトルの型エイリアス
using vec3 = vec<3>;

/// 「座標」を表す型 (実体はエイリアス)
template <int DIM>
using crd = vec<DIM>;

/// 二次元座標の型エイリアス
using crd2 = vec<2>;

/// 二次元座標の型エイリアス
using crd3 = vec<3>;

} // namespace pcl
