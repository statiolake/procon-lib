#ifndef F8BF9740_A133_EE18_1629_F4FE4326E750
#define F8BF9740_A133_EE18_1629_F4FE4326E750

#include <cmath>
#include <utility>
#include <vector>

namespace pcl {
template <typename T>
constexpr T gcd(T a, T b) {
  return b == 0 ? a : gcd(b, a % b);
}

template <typename T>
constexpr T lcm(T a, T b) {
  return a / gcd(a, b) * b;
}

template <typename T>
constexpr T extgcd(T a, T b, T &xd, T &yd) {
  if (b == 0) {
    xd = 1, yd = 0;
    return a;
  }
  T gcd = extgcd(b, a % b, yd, xd);
  yd -= (a / b) * xd;
  return gcd;
}

/// verified with aoj:0009
template <typename T>
std::vector<T> sieve(T N) {
  std::vector<T> result;
  std::vector<bool> is_not_prime(N);
  for (T i = 2; i <= N; i++) {
    if (is_not_prime[i]) continue;
    result.push_back(i);
    for (T j = i + i; j <= N; j += i) is_not_prime[j] = true;
  }
  return result;
}

template <typename T>
constexpr T pow(T x, int n) {
  T result = 1;
  while (n > 0) {
    if (n & 1) result *= x;
    x *= x;
    n >>= 1;
  }
  return result;
}

template <typename T>
constexpr bool is_prime(T val) {
  // msvc fails if use sqrt(val) instead of val
  // maybe msvc has no constexpr sqrt function.
  for (T i = 2; i < val; i++) {
    if (val % i == 0) return false;
  }
  return true;
}
} // namespace pcl

#endif /* F8BF9740_A133_EE18_1629_F4FE4326E750 */
