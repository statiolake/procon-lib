#pragma once

#include <algorithm>
#include <cmath>

namespace pcl {
template <typename T>
void updmax(T &a, T const &b) {
    a = std::max(a, b);
}

template <typename T>
void updmin(T &a, T const &b) {
    a = std::min(a, b);
}

template <typename T, typename U, typename V>
bool in_range(T const &begin, U const &mid, V const &end) {
    return begin <= mid && mid < end;
}
template <typename T, typename U, typename V>
bool in_range(T const &begin, std::initializer_list<U> list, V const &end) {
    auto p = std::minmax_element(list.begin(), list.end());
    return begin <= *p.first && *p.second < end;
}
inline bool eqdbl(double a, double b) { return std::abs(a - b) < EPS; }
inline bool ledbl(double a, double b) { return a < b || eqdbl(a, b); }
inline bool gtdbl(double a, double b) { return a > b || eqdbl(a, b); }
} // namespace pcl
