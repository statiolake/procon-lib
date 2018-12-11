#include "prelude.hpp"

#include "struct/union_find.hpp"

#include <bits/stdc++.h>

using namespace std;
using namespace pcl;

int main() {
    int n, q;
    cin >> n >> q;
    union_find uf(n);

    for (int i = 0; i < q; i++) {
        int com, x, y;
        cin >> com >> x >> y;
        if (com == 0) {
            // unite
            uf.unite(x, y);
        } else {
            // find
            cout << (uf.find(x) == uf.find(y)) << endl;
        }
    }
}
