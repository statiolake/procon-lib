#ifndef FENWICK_TREE_HPP_BXZMBQU9
#define FENWICK_TREE_HPP_BXZMBQU9

#include <cassert>
#include <vector>

namespace pcl {

/// verified with: aoj:DSL_2_B
template <typename T>
class fenwick_tree {
private:
  const int n;
  std::vector<T> data;

public:
  fenwick_tree(int n, T init = 0)
      : n(n)
      , data(n, init) {}

  void add(int i, T const &x) {
    assert(0 <= i && i < n);
    for (; i < n; i |= i + 1) data[i] += x;
  }

  T sum(int i) const {
    assert(0 <= i && i <= n);
    T res = 0;
    for (i--; i >= 0; i = (i & (i + 1)) - 1) res += data[i];
    return res;
  }

  T sum(int l, int r) const {
    assert(0 <= l && l <= r && r <= n);
    return sum(r) - sum(l);
  }
};

} // namespace pcl

#endif /* end of include guard: FENWICK_TREE_HPP_BXZMBQU9 */
