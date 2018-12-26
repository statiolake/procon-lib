/**
 * @file util/alg.hpp
 * @brief 数学的ではない (汎用的な) アルゴリズムたち。
 */
#pragma once

#include "../prelude.hpp"

#include <utility>

namespace pcl {

/**
 * @brief 回数を指定する二分探索。
 * @param[in] left 範囲の左端
 * @param[in] right 範囲の右端
 * @param[in] pred 判定関数。 pred は bool(Input) の形の関数オブジェクト。
 * pred はある値を境に、それより左側が true 、右側が false
 * となっていなければならない。
 * @param[in] last 二分探索の回数
 * @return Input 範囲のうち pred の true と false の境目に近い値。
 * @details
 * 二分探索だが、その終了条件を一定回数にするもの。浮動小数点数など誤差が生じてしまうもので用いる。二分探索は毎回範囲が半分に狭まるため、一見少ない回数でも非常に精度がよい。
 */
template <typename Input, typename Pred>
Input binary_search_n(Input left, Input right, Pred const &pred,
                      int last = 64) {
    Input mid = left + (right - left) / 2.0;

    (pred(mid) ? left : right) = mid;
    if (last <= 0) return mid;
    return binary_search_n(left, right, pred, last - 1);
}

} // namespace pcl
