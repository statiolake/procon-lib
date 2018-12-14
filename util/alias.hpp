#pragma once

#include "../prelude.hpp"

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

template <typename T, typename U, typename V>
bool strict_in_range(T const &begin, std::initializer_list<U> list,
                     V const &end) {
    if (!std::is_sorted(list.begin(), list.end())) return false;
    return in_range(begin, list, end);
}
} // namespace pcl
