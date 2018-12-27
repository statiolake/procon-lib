/**
 * @file struct/rolling_hash.hpp
 * @brief Rolling Hash - 区間のハッシュ値を高速に求める。
 */
#pragma once

#include "../prelude.hpp"

#include <cassert>
#include <string>
#include <vector>

namespace pcl {

/**
 * @brief Rolling Hash
 * @details Rolling Hash は計算過程で剰余をとる必要があるが、別に法は素数であ
 * る必要はない (基数 b と互いに素であればよい) ので、ここでは剰余の法として
 * ULLONG_MAX+1 を用いる。こうすると、 unsigned のオーバーフローは wrapping に
 * なることが保証されているため、何もしなくても加、減、乗算については常に剰余
 * をとっているのと同じことになる。ただし除算だけは注意が必要。 modint を思い
 * 出すと分かるが、割りたい数と剰余の法が互いに素である必要がある。
 * (ULLONG_MAX+1) = 2^64 は素数ではないので常に割れるわけではない。割れる場合
 * も、普通の割り算ではなく逆元を計算して積をとる計算になる。一般に ull を自動
 * modint として使うときは除算が不要な場合に限る方がよい。
 */
template <ull b = 100'000'007>
class rolling_hash {
  private:
    /// Rolling Hash 対象となる文字列の長さ
    int size_;

    /// hash_[i] は s[0..i] の部分文字列のハッシュ値。
    std::vector<ull> hash_;

    /// pow_[i] は pow(b, i) (= b^i) を表す。
    std::vector<ull> pow_;

  public:
    /**
     * @brief 与えられた文字列のハッシュ値を Rolling Hash により計算する。
     * @param[in] s 文字列
     * @details s[0..i] のハッシュ値を、 Rolling Hash を用いて全ての i につい
     * て計算する。この前計算により、一度計算を終わらせれば任意の区間のハッシ
     * ュを O(1) で計算することができる。累積和と全く同じアイデアである。
     */
    rolling_hash(std::string const &s)
        : size_(s.size() + 1)
        , hash_(size_, 0)
        , pow_(size_, 1) {
        for (int i = 1; i < size_; i++) pow_[i] = pow_[i - 1] * b;
        for (int i = 1; i < size_; i++) {
            hash_[i] = hash_[i - 1] * b + s[i - 1];
        }
    }

    /**
     * @brief 指定された範囲の文字列のハッシュ値を求める。
     * @param[in] l 範囲の左端
     * @param[in] r 範囲の右端 (右端は区間に含まない)
     */
    ull of_range(int l, int r) {
        assert(in_range_strict(0, {l, r}, size_));
        return hash_[r] - hash_[l] * pow_[r - l];
    }
};

} // namespace pcl
