/// verified with: aoj:2444

#include "prelude.hpp"

#include "math/rolling_hash.hpp"

#include <bits/stdc++.h>

using namespace std;
using namespace pcl;

int main() {
    cget<int>(); // ignore n;
    int m    = cget<int>();
    string s = cget<string>();
    rolling_hash<P7> rh(s);

    int l = 0, r = 1;
    unordered_set<ull> hashes;

    for (int i = 0; i < m; i++) {
        string q = cget<string>();
        if (q == "L++") l++;
        if (q == "L--") l--;
        if (q == "R++") r++;
        if (q == "R--") r--;
        hashes.insert(rh.of_range(l, r));
    }
    cout << hashes.size() << endl;
}
