#include "prelude.hpp"

// using libraries:
#include "util/stream/empty_stream.hpp"

#include <bits/stdc++.h>

using namespace std;
using namespace pcl;

int main() {
    es << "Hello, world!" << endl;
    es << "empty stream outputs nothing." << endl;
    es << "... but this should be deprecated." << endl;
}
