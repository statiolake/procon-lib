#pragma once

#include "../prelude.hpp"

#include <cassert>
#include <vector>

namespace pcl {

/// verified with: aoj:DSL_2_B
template <typename Group>
class fenwick_tree {
  public:
    using value_type = typename Group::value_type;

  private:
    int const sz;
    std::vector<value_type> data;

  public:
    fenwick_tree(int sz)
        : sz(sz)
        , data(sz, Group::id()) {}

    void add(int i, value_type const &x) {
        assert(in_range(0, i, sz));
        for (; i < sz; i |= i + 1) data[i] = Group::op(data[i], x);
    }

    value_type sum(int i) const {
        // since sum(i) is sum of 0..i, i can be sz.
        assert(in_range(0, i, sz + 1));
        value_type res = Group::id();
        for (i--; i >= 0; i = (i & (i + 1)) - 1)
            res = Group::op(res, data[i]);
        return res;
    }

    value_type sum(int l, int r) const {
        // since sum(i) is sum of l..r, r can be sz.
        assert(in_range(0, {l, r}, sz + 1));
        return Group::op(sum(r), Group::inv(sum(l)));
    }
};

template <typename T>
struct range_sum_query {
    using value_type = T;
    constexpr static value_type id() { return T{}; }
    constexpr static value_type inv(value_type const &x) { return -x; }
    constexpr static value_type op(value_type const &lhs,
                                   value_type const &rhs) {
        return lhs + rhs;
    }
};

} // namespace pcl
