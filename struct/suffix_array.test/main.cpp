/// verified with: aoj:ALDS1_14_D

#include "prelude.hpp"

#include "struct/suffix_array.hpp"

#include <bits/stdc++.h>

using namespace std;
using namespace pcl;

int main() {
    string T;
    int Q;
    cin >> T >> Q;

    suffix_array sa(T);

    for (int q = 0; q < Q; q++) {
        string P;
        cin >> P;
        cout << sa.matches(P) << endl;
    }
}
