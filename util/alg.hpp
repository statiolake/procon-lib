#pragma once

#include "../prelude.hpp"

#include <utility>
namespace pcl {

template <typename Input, typename Pred>
Input binary_search_count(Input left, Input right, Pred const &pred, int last = 64) {
    Input mid = left + (right - left) / 2.0;

    (pred(mid) ? left : right) = mid;
    if (last <= 0) return mid;
    return binary_search_count(left, right, pred, last - 1);
}

} // namespace pcl
