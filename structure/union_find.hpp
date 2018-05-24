/*
 * union_find.hpp - union-find tree.
 * verifyed with aoj:DSL_1_A
 */
#ifndef UNION_FIND_HPP_OXVELNTB
#define UNION_FIND_HPP_OXVELNTB

#include <cassert>
#include <vector>

namespace pcl { namespace structure {
    class union_find {
      private:
        std::vector<int> parent_of, rank_of;
        std::size_t size_;

      public:
        union_find(int n)
            : parent_of(n, -1)
            , rank_of(n, 0)
            , size_(n) {}

        void unite(int a, int b) {
            int pa = find(a), pb = find(b);
            if (pa == pb) return;
            assert(pa != pb);
            --size_;

            int np, nc;
            if (rank_of[pa] == rank_of[pb]) {
                np = pa;
                nc = pb;
                rank_of[np]++;
            } else if (rank_of[pa] < rank_of[pb]) {
                np = pb;
                nc = pa;
            } else {
                np = pa;
                nc = pb;
            }

            parent_of[nc] = np;
        }

        int find(int a) {
            if (parent_of[a] == -1) return a;
            return parent_of[a] = find(parent_of[a]);
        }

        std::size_t size() const { return size_; }
    };
}} // namespace pcl::structure

#endif /* end of include guard: UNION_FIND_HPP_OXVELNTB */
