/// verified with: aoj DSL_2_B

#include "prelude.hpp"

#include "math/group.hpp"
#include "struct/fenwick_tree.hpp"

#include <bits/stdc++.h>

using namespace std;
using namespace pcl;

int main() {
    int n, q;
    cin >> n >> q;
    fenwick_tree<group::add<int>> ft(n);
    for (int i = 0; i < q; i++) {
        int com, x, y;
        cin >> com >> x >> y;
        x--;

        if (com == 0) {
            ft.add(x, y);
        } else {
            cout << ft.sum(x, y) << endl;
        }
    }
}
