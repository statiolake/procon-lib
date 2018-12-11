#include "prelude.hpp"

#include "struct/dbl.hpp"

#include <bits/stdc++.h>

using namespace std;
using namespace pcl;

int main() {
    dbl x, y;

    cin >> x >> y;

    double z;
    cin >> z;

    cout << x + y << endl;
    cout << x - y << endl;
    cout << x * y << endl;
    cout << x / y << endl;
    cout << (x == y) << endl;
    cout << (x != y) << endl;
    cout << (x < y) << endl;
    cout << (x > y) << endl;
    cout << (x <= y) << endl;
    cout << (x >= y) << endl;

    cout << x + z << endl;
    cout << x - z << endl;
    cout << x * z << endl;
    cout << x / z << endl;
    cout << (x == z) << endl;
    cout << (x != z) << endl;
    cout << (x < z) << endl;
    cout << (x > z) << endl;
    cout << (x <= z) << endl;
    cout << (x >= z) << endl;

    cout << z + y << endl;
    cout << z - y << endl;
    cout << z * y << endl;
    cout << z / y << endl;
    cout << (z == y) << endl;
    cout << (z != y) << endl;
    cout << (z < y) << endl;
    cout << (z > y) << endl;
    cout << (z <= y) << endl;
    cout << (z >= y) << endl;
}
