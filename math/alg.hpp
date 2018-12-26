#pragma once

#include "../prelude.hpp"

#include <cmath>
#include <tuple>
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
// tuple<x, y, gcd>
constexpr std::tuple<T, T, T> extgcd(T a, T b) {
    if (b == 0) {
        return std::make_tuple(a, 1, 0);
    } else {
        T gcd, xd, yd;
        std::tie(gcd, xd, yd) = extgcd(b, a % b);
        return std::make_tuple(gcd, yd, xd - (a / b) * yd);
    }
}

/// verified with aoj:0009
template <typename T>
std::vector<T> sieve(T N) {
    std::vector<T> res;
    std::vector<bool> is_not_prime(N);
    for (T i = 2; i <= N; i++) {
        if (is_not_prime[i]) continue;
        res.push_back(i);
        for (T j = i + i; j <= N; j += i) is_not_prime[j] = true;
    }
    return res;
}

template <typename T>
constexpr T pow(T x, int n) {
    T res = 1;
    while (n > 0) {
        if (n & 1) res *= x;
        x *= x;
        n >>= 1;
    }
    return res;
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
