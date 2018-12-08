#include "prelude.hpp"

// using libraries:
#include "util/stream/overloads.hpp"

#include <bits/stdc++.h>

using namespace std;
using namespace pcl;

int main() {
    vector<vector<int>> v(3, vector<int>(3));
    cin >> v;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (j != 0) cout << ' ';
            cout << v[i][j];
        }
        cout << endl;
    }
}
