/// basically verified with: aoj:ITP1_7_D

#include "prelude.hpp"

#include "struct/mat.hpp"

#include <bits/stdc++.h>

using namespace std;
using namespace pcl;

int main() {
    int n, m, l;
    cin >> n >> m >> l;

    mat<ll> A(n, m), B(m, l);
    cin >> A >> B;

    auto C = A * B;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < l; j++) {
            if (j != 0) cout << ' ';
            cout << C.at(i, j);
        }
        cout << endl;
    }

    assert(n == l);
    cout << C.det() << endl;
}
