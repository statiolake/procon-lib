#ifndef SEGMENT_TREE_HPP_ACMT4Z9H
#define SEGMENT_TREE_HPP_ACMT4Z9H

#include <cassert>
#include <vector>

namespace pcl {

/// verified with: aoj:DSL_2_A
template <typename Monoid>
class segment_tree {
public:
  using value_type = typename Monoid::value_type;

private:
  int const sz, n;
  std::vector<value_type> data;

  /// n は 2^n >= sz を満たす最初の整数
  int calc_n(int sz) {
    // 参考: http://marupeke296.com/TIPS_No17_Bit.html
    sz--;
    sz |= sz >> 1;
    sz |= sz >> 2;
    sz |= sz >> 4;
    sz |= sz >> 8;
    sz |= sz >> 16;
    return sz + 1;
  }

public:
  segment_tree(std::vector<value_type> const &init)
      : sz(init.size())
      , n(calc_n(sz))
      , data(n * 2, Monoid::id()) {
    std::copy(init.begin(), init.end(), data.begin() + n);
    for (int i = n - 1; i >= 0; i--) {
      data[i] = Monoid::op(data[i * 2], data[i * 2 + 1]);
    }
  }

  segment_tree(int sz, value_type init = Monoid::id())
      : segment_tree(std::vector<value_type>(sz, init)) {}

  void update(int i, int x) {
    assert(0 <= i && i <= sz);
    // data の中では 1-indexed のように扱っている
    data[i += n] = x;
    while (i /= 2) data[i] = Monoid::op(data[i * 2], data[i * 2 + 1]);
  }

  value_type find(int l, int r) const {
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
};

template <typename T, T inf>
struct range_minimum_query {
  using value_type = T;
  constexpr static T id() { return inf; }
  constexpr static T op(T const &lhs, T const &rhs) {
    return std::min(lhs, rhs);
  }
};

} // namespace pcl

#endif /* end of include guard: SEGMENT_TREE_HPP_ACMT4Z9H */
