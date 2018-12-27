/**
 * @file math/group.hpp
 * @brief `群`
 * @details 群は次のような構造をもつものである。
 * ```cpp
 * struct {
 *    using value_type;
 *    constexpr static value_type id();
 *    constexpr static value_type inv(x);
 *    constexpr static value_type op(lhs, rhs);
 * };
 * ```
 */
#pragma once

#include "../prelude.hpp"

namespace pcl { namespace group {

    /**
     * @brief 加算の群。
     * @details いわゆる (G, +) のような型。 G は次の条件を満たしていればよい:
     * - operator+() が定義されている。
     * - デフォルトコンストラクタが返す値が + の単位元になる (0) 。
     * - x の逆元が単項マイナス演算子を用いて -x で与えられる。
     */
    template <typename T>
    struct add {
        using value_type = T;
        constexpr static value_type id() {
            return T{};
        }
        constexpr static value_type inv(value_type const &x) {
            return -x;
        }
        constexpr static value_type op(value_type const &a,
                                       value_type const &b) {
            return a + b;
        }
    };

}} // namespace pcl::group
