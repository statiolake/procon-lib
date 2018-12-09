#pragma once

#include "prelude.hpp"

#include <limits>

namespace pcl {
constexpr int INF    = std::numeric_limits<int>::max() / 2;
constexpr ll LNF     = std::numeric_limits<ll>::max() / 2;
constexpr double DNF = std::numeric_limits<double>::max() / 2;
constexpr double EPS = 1e-8;
constexpr int DX[]   = {1, 0, -1, 0, 1, 1, -1, -1};
constexpr int DY[]   = {0, 1, 0, -1, -1, 1, 1, -1};
} // namespace pcl
