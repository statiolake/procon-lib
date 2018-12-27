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
    ll const size_, n_;
    std::vector<value_type> data_;

    /// n_ is the first integer that satisfies 2^n_ >= size
    ll calc_n(ll size) {
        size--;
        size |= size >> 1;
        size |= size >> 2;
        size |= size >> 4;
        size |= size >> 8;
        size |= size >> 16;
        size |= size >> 32;
        return size + 1;
    }

  public:
    segment_tree(std::vector<value_type> const &init)
        : size_(init.size())
        , n_(calc_n(size_))
        , data_(n_ * 2, Monoid::id()) {
        std::copy(init.begin(), init.end(), data_.begin() + n_);
        for (ll i = n_ - 1; i >= 0; i--) {
            data_[i] = Monoid::op(data_[i * 2], data_[i * 2 + 1]);
        }
    }

    segment_tree(ll size_, value_type init = Monoid::id())
        : segment_tree(std::vector<value_type>(size_, init)) {
    }

    void update(ll i, ll x) {
        assert(0 <= i && i <= size_);
        data_[i += n_] = x;
        while (i /= 2) data_[i] = Monoid::op(data_[i * 2], data_[i * 2 + 1]);
    }

    value_type find(ll a, ll b) const {
        assert(0 <= a && a <= b && b <= size_);
        a += n_, b += n_;
        value_type res1 = Monoid::id(), res2 = Monoid::id();
        while (a < b) {
            if (a & 1) res1 = Monoid::op(res1, data_[a++]);
            if (b & 1) res2 = Monoid::op(data_[--b], res2);
            a >>= 1, b >>= 1;
        }
        return Monoid::op(res1, res2);
    }

    value_type const &get(ll i) const {
        return data_[i + n_];
    }
};

} // namespace pcl
