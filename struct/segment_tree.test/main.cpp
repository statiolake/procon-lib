#include "prelude.hpp"

#include "math/monoid.hpp"
#include "struct/segment_tree.hpp"

#include <bits/stdc++.h>

using namespace std;
using namespace pcl;

int main() {
    int n, q;
    cin >> n >> q;

    segment_tree<monoid::min<ll>> st(n, (1ll << 31) - 1);
    for (int i = 0; i < q; i++) {
        int com, x, y;
        cin >> com >> x >> y;
        if (com == 0) {
            st.update(x, y);
        } else {
            cout << st.find(x, y + 1) << endl;
        }
    }
}
