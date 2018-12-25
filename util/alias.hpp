/**
 * @file alias.hpp
 * @brief よく使うけどアルゴリズムというほどでもない便利関数たち。
 */
#pragma once

#include "../prelude.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>

namespace pcl {
/**
 * @brief 最大値なら更新する (緩和) 。
 * @param[inout] a この値を更新する。
 * @param[in] b この値で更新を試みる。
 * @details a と b のうち大きい方を a へ代入する。各種アルゴリズムや動的計画法
 * などで便利。
 */
template <typename T>
void updmax(T &a, T const &b) {
    a = std::max(a, b);
}

/**
 * @brief 最小値なら更新する (緩和) 。
 * @param[inout] a この値を更新する。
 * @param[in] b この値で更新を試みる。
 * @details a と b のうち小きい方を a へ代入する。各種アルゴリズムや動的計画法
 * などで便利。
 */
template <typename T>
void updmin(T &a, T const &b) {
    a = std::min(a, b);
}

/**
 * @brief 値が範囲内にあるかどうかを返す。
 * @param[in] begin 最小値
 * @param[in] mid 中間値
 * @param[in] end 最大値
 * @return bool begin <= mid < end かどうか
 * @details 配列の添字アクセス演算子などで範囲内アクセスを判定するのに使える。
 */
template <typename T, typename U, typename V>
bool in_range(T const &begin, U const &mid, V const &end) {
    return begin <= mid && mid < end;
}

/**
 * @brief 複数の値について、範囲内にあるかどうかを返す。
 * @param[in] begin 最小値
 * @param[in] list 中間値たち
 * @param[in] end 最大値
 * @return bool 任意の l in list について begin <= l < end かどうか
 * @details 配列の添字アクセス演算子などで範囲内アクセスを判定するのに使える。
 */
template <typename T, typename U, typename V>
bool in_range(T const &begin, std::initializer_list<U> list, V const &end) {
    auto p = std::minmax_element(list.begin(), list.end());
    return begin <= *p.first && *p.second < end;
}

/**
 * @brief 複数の値について、その順番で昇順になっているかどうかを調べる。
 * @param[in] begin 最小値
 * @param[in] list 中間値たち
 * @param[in] end 最大値
 * @return bool list がソートされていてかつ begin <= list < end かどうか
 * @details 配列の添字アクセス演算子などで範囲内アクセスを判定するのに使える。
 */
template <typename T, typename U, typename V>
bool strict_in_range(T const &begin, std::initializer_list<U> list, V const &end) {
    if (!std::is_sorted(list.begin(), list.end())) return false;
    return in_range(begin, list, end);
}

/**
 * @brief 型 T の入力を std::cin から取る。
 * @return T 得られた入力値
 * @details 一々宣言してから std::cin >> x するのが面倒なので、 int x =
 * cget<int>(); のように使いたい。Rust のように戻り値推論が効いて int x =
 * cget(); とできると便利なのだが...
 */
template <typename T>
inline T cget() {
    T x;
    std::cin >> x;
    return x;
}
} // namespace pcl
