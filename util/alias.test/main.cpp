#include "prelude.hpp"

// using libraries:
#include "util/alias.hpp"

#include <bits/stdc++.h>

using namespace std;
using namespace pcl;

int main() {
    for (int i = 0; i < 2; i++) {
        auto a = cget<int>(), b = cget<int>();
        updmax(a, b);
        cout << a << endl;
    }

    for (int i = 0; i < 2; i++) {
        auto a = cget<int>(), b = cget<int>();
        updmin(a, b);
        cout << a << endl;
    }

    for (int i = 0; i < 2; i++) {
        auto a = cget<int>(), b = cget<int>(), c = cget<int>();
        cout << in_range(a, b, c) << endl;
    }

    for (int i = 0; i < 2; i++) {
        int a, b, c, d, e;
        cin >> a >> b >> c >> d >> e;
        cout << in_range(a, {b, c, d}, e) << endl;
    }

    for (int i = 0; i < 2; i++) {
        int a, b, c, d, e;
        cin >> a >> b >> c >> d >> e;
        cout << in_range_strict(a, {b, c, d}, e) << endl;
    }
}
