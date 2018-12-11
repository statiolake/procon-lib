#pragma once

#include "prelude.hpp"

#include <limits>

namespace pcl {

template <typename T>
constexpr T TNF = std::numeric_limits<T>::max() / 2;

constexpr int INF    = TNF<int>;
constexpr ll LNF     = TNF<ll>;
constexpr double DNF = TNF<double>;

constexpr double EPS = 1e-8;
constexpr int DX[]   = {1, 0, -1, 0, 1, 1, -1, -1};
constexpr int DY[]   = {0, 1, 0, -1, -1, 1, 1, -1};
} // namespace pcl
