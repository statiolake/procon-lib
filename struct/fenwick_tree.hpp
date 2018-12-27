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
    int const size_;
    std::vector<value_type> data_;

  public:
    fenwick_tree(int size)
        : size_(size)
        , data_(size, Group::id()) {
    }

    int size() const {
        return size_;
    }

    void add(int i, value_type const &x) {
        assert(in_range(0, i, size()));
        for (; i < size(); i |= i + 1) data_[i] = Group::op(data_[i], x);
    }

    value_type sum(int i) const {
        // since sum(i) is sum of 0..i, i can be size.
        assert(in_range(0, i, size() + 1));
        value_type res = Group::id();
        for (i--; i >= 0; i = (i & (i + 1)) - 1)
            res = Group::op(res, data_[i]);
        return res;
    }

    value_type sum(int a, int b) const {
        // since sum(i) is sum of a..b, b can be size.
        assert(in_range(0, {a, b}, size() + 1));
        return Group::op(sum(b), Group::inv(sum(a)));
    }
};

} // namespace pcl
