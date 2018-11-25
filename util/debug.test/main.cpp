#include "prelude.hpp"
#include "util/debug.hpp"

#include <bits/stdc++.h>
using namespace std;
using namespace pcl;
int main() {
  PD { cerr << "this is debug string." << endl; }
  PD_LIB { cerr << "this is debug string." << endl; }
}
