/**
 * @file math/monoid.hpp
 * @brief `モノイド`
 * @details モノイドは次のような構造をもつものである。群から逆元を除いたもので
 * ある。
 * ```cpp
 * struct {
 *    using value_type = T;
 *    constexpr static value_type id();
 *    constexpr static value_type op(lhs, rhs);
 * };
 * ```
 */
#pragma once

#include "../prelude.hpp"

namespace pcl { namespace monoid {

    /**
     * @brief 最小値のモノイド。
     * @details T は次の条件を満たしていればよい:
     * - std::min(a, b) が呼び出せる。
     * - TNF<T> により単位元 (無限大) が得られる。
     */
    template <typename T>
    struct min {
        using value_type = T;

        constexpr static value_type id() {
            return TNF<T>;
        }

        constexpr static value_type op(value_type const &a,
                                       value_type const &b) {
            return std::min(a, b);
        }
    };

}} // namespace pcl::monoid
