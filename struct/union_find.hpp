/*
 * union_find.hpp - union-find tree.
 * verifyed with aoj:DSL_1_A
 */
#ifndef UNION_FIND_HPP_OXVELNTB
#define UNION_FIND_HPP_OXVELNTB

#include <cassert>
#include <vector>

namespace pcl {
class union_find {
  private:
    std::vector<int>
        parent_or_rank_of; // positive: parent, negative: (rank + 1)
    std::size_t size_;

  public:
    union_find(int n)
        : parent_or_rank_of(n, -1)
        , size_(n) {}

    void unite(int a, int b) {
        int pa = find(a), pb = find(b);
        if (pa == pb) return;
        assert(pa != pb);
        --size_;

        int np, nc;
        if (parent_or_rank_of[pa] == parent_or_rank_of[pb]) {
            np = pa;
            nc = pb;
            parent_or_rank_of[np]--;
        } else if (parent_or_rank_of[pa] > parent_or_rank_of[pb]) {
            np = pb;
            nc = pa;
        } else {
            np = pa;
            nc = pb;
        }

        parent_or_rank_of[nc] = np;
    }

    int find(int a) {
        if (parent_or_rank_of[a] < 0) return a;
        return parent_or_rank_of[a] = find(parent_or_rank_of[a]);
    }

    std::size_t size() const { return size_; }
};
} // namespace pcl

#endif /* end of include guard: UNION_FIND_HPP_OXVELNTB */
