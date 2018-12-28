/**
 * @file globals.hpp
 * @brief よく使われるグローバル定数たちの宣言。
 */
#pragma once

#include "prelude.hpp"

#include <limits>

namespace pcl {

/// 型 T における "無限"
template <typename T>
constexpr T TNF = std::numeric_limits<T>::max() / 2;

/// int の "無限"
constexpr int INF = TNF<int>;

/// ll の "無限"
constexpr ll LNF = TNF<ll>;

/// double の "無限"
constexpr double DNF = TNF<double>;

/// double の微小 (これ以下の差異を差異と認めないしきい値)
constexpr double EPS = 1e-8;

/// よく使う素数 (7)
constexpr int P7 = 1'000'000'007;

/// X 方向の変化量。 DX[0..4] は上下左右の 4 方向、 DX[0..8] は 8 方向。
constexpr int DX[] = {1, 0, -1, 0, 1, 1, -1, -1};

/// Y 方向の変化量。 DY[0..4] は上下左右の 4 方向、 DY[0..8] は 8 方向。
constexpr int DY[] = {0, 1, 0, -1, -1, 1, 1, -1};
} // namespace pcl
