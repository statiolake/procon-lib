#include "prelude.hpp"

// using libraries:
#include "util/alias.hpp"

#include <bits/stdc++.h>

using namespace std;
using namespace pcl;

int main() {
    for (int i = 0; i < 2; i++) {
        int a, b;
        cin >> a >> b;
        updmax(a, b);
        cout << a << endl;
    }

    for (int i = 0; i < 2; i++) {
        int a, b;
        cin >> a >> b;
        updmin(a, b);
        cout << a << endl;
    }

    for (int i = 0; i < 2; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        cout << in_range(a, b, c) << endl;
    }

    for (int i = 0; i < 2; i++) {
        int a, b, c, d, e;
        cin >> a >> b >> c >> d >> e;
        cout << in_range(a, {b, c, d}, e) << endl;
    }

    for (int i = 0; i < 2; i++) {
        double a, b, r = 0.0;
        int n;
        cin >> a >> n >> b;
        for (int i = 0; i < n; i++) r += a;
        cout << eqdbl(r, b) << endl;
    }

    for (int i = 0; i < 2; i++) {
        double a, b, r = 0.0;
        int n;
        cin >> a >> n >> b;
        for (int i = 0; i < n; i++) r += a;
        cout << ledbl(r, b) << endl;
    }

    for (int i = 0; i < 2; i++) {
        double a, b, r = 0.0;
        int n;
        cin >> a >> n >> b;
        for (int i = 0; i < n; i++) r += a;
        cout << gedbl(r, b) << endl;
    }
}
