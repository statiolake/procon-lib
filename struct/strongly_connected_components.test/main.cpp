#include "prelude.hpp"

#include "struct/strongly_connected_components.hpp"

#include <bits/stdc++.h>
using namespace std;
using namespace pcl;
vector<double> calc_prob_scc(strongly_connected_components_t const &sccs,
                             int N, vector<double> const &p_ind) {
    vector<double> p_scc(sccs.size(), 1.0);
    for (int ind = 0; ind < N; ind++) {
        int scc = sccs.scc_of(ind);
        p_scc[scc] *= p_ind[ind];
    }
    return p_scc;
}

int main() {
    int N;
    while (cin >> N, N) {
        vector<double> p_ind(N);
        graph_t g_ind(N);
        for (int i = 0; i < N; i++) {
            int m;
            cin >> p_ind[i] >> m;
            g_ind[i].resize(m);
            for (int j = 0; j < m; j++) {
                cin >> g_ind[i][j];
                g_ind[i][j]--;
            }
        }

        auto sccs  = decompose_into_sccs(g_ind);
        auto g_scc = make_scc_graph(g_ind, sccs);
        auto p_scc = calc_prob_scc(sccs, N, p_ind);
        auto roots = find_roots(g_scc);

        double all_getup = 1.0;
        for (int root : roots) all_getup *= 1.0 - p_scc[root];

        cout << fixed << setprecision(9) << all_getup << endl;
    }
}

// vim: set sw=2 ts=2 sts=2:
