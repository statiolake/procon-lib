#include "prelude.hpp"

#include <bits/stdc++.h>

using namespace std;
using namespace pcl;

void reset(bool (*m)[3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) m[i][j] = false;
    }
    m[1][1] = true;
}

void print(bool const (*m)[3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) cout << m[i][j];
        cout << endl;
    }
}

int main() {
    bool m[3][3];

    reset(m);
    for (int i = 0; i < 4; i++) m[1 + DX[i]][1 + DY[i]] = true;
    print(m);

    reset(m);
    for (int i = 0; i < 8; i++) m[1 + DX[i]][1 + DY[i]] = true;
    print(m);
}
