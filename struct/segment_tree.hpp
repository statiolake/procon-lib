#pragma once

#include "../prelude.hpp"

#include <cassert>
#include <vector>

namespace pcl {

/// verified with: aoj:DSL_2_A
template <typename Monoid>
class segment_tree {
  public:
    using value_type = typename Monoid::value_type;

  private:
    ll const sz, n;
    std::vector<value_type> data;

    /// n is the first integer that satisfies 2^n >= sz
    ll calc_n(ll sz) {
        sz--;
        sz |= sz >> 1;
        sz |= sz >> 2;
        sz |= sz >> 4;
        sz |= sz >> 8;
        sz |= sz >> 16;
        sz |= sz >> 32;
        return sz + 1;
    }

  public:
    segment_tree(std::vector<value_type> const &init)
        : sz(init.size())
        , n(calc_n(sz))
        , data(n * 2, Monoid::id()) {
        std::copy(init.begin(), init.end(), data.begin() + n);
        for (ll i = n - 1; i >= 0; i--) {
            data[i] = Monoid::op(data[i * 2], data[i * 2 + 1]);
        }
    }

    segment_tree(ll sz, value_type init = Monoid::id())
        : segment_tree(std::vector<value_type>(sz, init)) {}

    void update(ll i, ll x) {
        assert(0 <= i && i <= sz);
        data[i += n] = x;
        while (i /= 2) data[i] = Monoid::op(data[i * 2], data[i * 2 + 1]);
    }

    value_type find(ll l, ll r) const {
        assert(0 <= l && l <= r && r <= sz);
        l += n, r += n;
        value_type res1 = Monoid::id(), res2 = Monoid::id();
        while (l < r) {
            if (l & 1) res1 = Monoid::op(res1, data[l++]);
            if (r & 1) res2 = Monoid::op(data[--r], res2);
            l >>= 1, r >>= 1;
        }
        return Monoid::op(res1, res2);
    }

    value_type const &get(ll i) const { return data[i + n]; }
};

template <typename T>
struct range_minimum_query {
    using value_type = T;
    constexpr static value_type id() { return TNF<T>; }
    constexpr static value_type op(value_type const &lhs,
                                   value_type const &rhs) {
        return std::min(lhs, rhs);
    }
};

} // namespace pcl
