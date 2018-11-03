#pragma once

#include <utility>
namespace pcl {
template <typename Input, typename Pred>
Input binary_search(Input left, Input right, Pred &&pred,
                    std::size_t last = 32) {
  Input mid = left + (right - left) / 2;
  if (pred(mid)) {
    right = mid;
  } else {
    left = mid;
  }
  return last > 0
             ? binary_search(left, right, std::forward<Pred>(pred), last - 1)
             : mid;
}
} // namespace pcl
