#pragma once

#include <vector>

namespace pcl { namespace graph {
    /// 隣接リスト形式
    template <typename T>
    class list {
      public:
        struct target;
        class target_reference;

      private:
        std::vector<std::vector<target>> adj;

      public:
        list(int n)
            : adj(n) {}

        int size() const { return adj.size(); }

        void add_edge(int from, int to, T cost = T{}) {
            adj.at(from).push_back({to, cost});
        }

        bool remove_edge(int from, int to) {
            auto &cand = adj.at(from);
            for (auto it = cand.cbegin(); it != cand.cend(); ++it) {
                if (it->to == to) {
                    cand.erase(it);
                    return true;
                }
            }

            return false;
        }

        std::vector<target> const &adj_of(int x) const { return adj.at(x); }

        struct target {
            int to;
            T cost;
        };
    };

    /// 隣接行列形式
    class matrix {};
}} // namespace pcl::graph
