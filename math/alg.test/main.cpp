#include "prelude.hpp"

#include "math/alg.hpp"

#include <bits/stdc++.h>

using namespace std;
using namespace pcl;

int main() {
    int a, b;
    cin >> a >> b;

    cout << gcd(a, b) << endl;
    cout << lcm(a, b) << endl;

    int gcd, x, y;
    tie(gcd, x, y) = extgcd(a, b);
    cout << gcd << ' ' << (a * x + b * y == gcd) << endl;

    for (auto x : sieve(a)) cout << x << ' ';
    cout << endl;

    cout << pow(a, b) << endl;

    cout << is_prime(a) << ' ' << is_prime(b) << endl;
}
