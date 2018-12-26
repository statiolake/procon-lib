#include "prelude.hpp"

// using libraries:
#include "struct/vec.hpp"

#include <bits/stdc++.h>

using namespace std;
using namespace pcl;

int main() {
    double a, b, c, d, e, f;
    cin >> a >> b >> c >> d >> e >> f;

    double r;
    cin >> r;

    vec3 x(a, b, c), y(d, e, f);

    cout << setprecision(9);

    cout << x + y << endl;
    cout << x - y << endl;
    cout << r * x << endl;
    cout << x * r << endl;
    cout << x / r << endl;
    cout << x.normalized() << endl;
    cout << y.len() << endl;
    cout << dot(x, y) << endl;
    cout << cross(x, y) << endl;

    for (int i = 0; i < 2; i++) {
        cin >> x >> y;
        cout << is_par(x, y) << endl;
        cout << is_same_dir(x, y) << endl;
    }
}
