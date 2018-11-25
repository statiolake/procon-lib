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
    auto val = A * t + B * sin(C * t * 3.1415926535);
    PD { cerr << "for " << t << ": " << val << endl; }
    return val < 100;
  };

  cout << fixed << binary_search_count(0.0, T, pred) << endl;
}
