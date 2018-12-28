#pragma once

#include "../prelude.hpp"

#include <algorithm>
#include <functional>
#include <utility>
#include <vector>

namespace pcl {
// set of vertices
using vgrp_t = std::vector<int>;

// graph (adjacency list)
using graph_t = std::vector<vgrp_t>;

graph_t reverse_graph(graph_t const &g) {
    graph_t rg(g.size());
    for (int i = 0; i < static_cast<int>(g.size()); i++) {
        for (int to : g[i]) rg[to].push_back(i);
    }
    return rg;
}

std::vector<std::pair<int, int>> make_numbering(graph_t const &g) {
    // std::pair<int, int> = { order in postorder DFS, vertex number }
    // order | -1 => not yet visited
    //       | -2 => now searching
    std::vector<std::pair<int, int>> numbering(g.size(),
                                               std::make_pair(-1, 0));

    std::function<int(int, int)> dfs = [&](int v, int num) {
        // if v is already visited, do nothing.
        if (numbering[v].first != -1) return num;
        numbering[v].first = -2;
        for (int to : g[v]) num = dfs(to, num);
        numbering[v] = std::make_pair(num, v);
        return num + 1;
    };

    int num = 0;
    for (int i = 0; i < static_cast<int>(g.size()); i++) {
        if (numbering[i].first == -1) num = dfs(i, num);
    }

    return numbering;
}

class scc_decomp {
  private:
    std::vector<int> scc_of_;
    int size_;

  public:
    scc_decomp(std::vector<int> scc_of, int size)
        : scc_of_(scc_of)
        , size_(size) {
    }
    int size() const {
        return size_;
    }
    int scc_of(int v) const {
        return scc_of_[v];
    }
};

scc_decomp decompose_impl(graph_t const &rg,
                          std::vector<std::pair<int, int>> const &numbering) {
    std::vector<int> scc_of(rg.size(), -1);

    // mark a strongly connected components beginning from vertex v with
    // `num`.
    std::function<void(int, int)> dfs = [&](int v, int num) {
        scc_of[v] = num;
        // add not yet decomposed vertices in adjacent vertices
        for (int to : rg[v]) {
            if (scc_of[to] != -1) continue;
            dfs(to, num);
        }
    };

    int num = 0;
    for (auto const &p : numbering) {
        int v = p.second;
        if (scc_of[v] == -1) dfs(v, num++);
    }

    return scc_decomp(scc_of, num);
}

scc_decomp decompose_into_sccs(graph_t const &g) {
    auto numbering = make_numbering(g);
    std::sort(numbering.begin(), numbering.end(),
              std::greater<std::pair<int, int>>());
    return decompose_impl(reverse_graph(g), numbering);
}

graph_t make_scc_graph(graph_t const &g_ind, scc_decomp const &sccs) {
    graph_t g_scc(sccs.size());
    for (int i = 0; i < static_cast<int>(g_ind.size()); i++) {
        auto &v = g_scc[sccs.scc_of(i)];
        for (int to : g_ind[i]) {
            if (sccs.scc_of(i) == sccs.scc_of(to)) continue;
            if (find(v.begin(), v.end(), sccs.scc_of(to)) != v.end())
                continue;
            v.push_back(sccs.scc_of(to));
        }
    }
    return g_scc;
}

vgrp_t find_roots(std::vector<vgrp_t> const &g) {
    std::vector<bool> pointed(g.size(), false);
    for (auto const &v : g)
        for (auto x : v) pointed[x] = true;

    vgrp_t roots;
    for (int i = 0; i < static_cast<int>(g.size()); i++)
        if (!pointed[i]) roots.push_back(i);

    return roots;
}

} // namespace pcl
