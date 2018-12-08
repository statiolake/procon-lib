/*
 * to verify:
 * https://beta.atcoder.jp/contests/abc026/tasks/abc026_d
 */
#include "prelude.hpp"

#include "util/alg.hpp"

#include <bits/stdc++.h>
using namespace std;
using namespace pcl;

int main() {
    double A, B, C;
    cin >> A >> B >> C;

    double T  = 1000;
    auto pred = [&](double t) {
        return A * t + B * sin(C * t * 3.14159265358979) < 100;
    };

    cout << fixed << setprecision(12) << binary_search_count(0.0, T, pred)
         << endl;
}
