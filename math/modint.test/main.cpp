#include "prelude.hpp"

#include "math/modint.hpp"

#include <bits/stdc++.h>
using namespace std;
using namespace pcl;
int main() {
  modint<int, 5> x, y;
  cin >> x >> y;

  cout << x + y << endl;
  cout << x - y << endl;
  cout << x * y << endl;
  cout << x / y << endl;

  cout << 2ll + y << endl;
  cout << 2ll - y << endl;
  cout << 2ll * y << endl;
  cout << 2ll / y << endl;

  cout << y + 2ll << endl;
  cout << y - 2ll << endl;
  cout << y * 2ll << endl;
  cout << y / 2ll << endl;

  cin >> y;

  cout << (x == y) << endl;
  cout << (x != y) << endl;
  cout << (x < y) << endl;
  cout << (x <= y) << endl;
  cout << (x > y) << endl;
  cout << (x >= y) << endl;

  cin >> x;

  cout << (x == y) << endl;
  cout << (x != y) << endl;
  cout << (x < y) << endl;
  cout << (x <= y) << endl;
  cout << (x > y) << endl;
  cout << (x >= y) << endl;
}
