#pragma once

#include <utility>
namespace pcl {

template <typename Input, typename Pred>
Input binary_search_count(Input left, Input right, Pred &&pred,
                          std::size_t last = 32) {
  Input mid = left + (right - left) / 2;
  if (pred(mid)) {
    left = mid;
  } else {
    right = mid;
  }
  return last > 0 ? binary_search_count(left, right, std::forward<Pred>(pred),
                                        last - 1)
                  : mid;
}

} // namespace pcl
