#ifndef F8BF9740_A133_EE18_1629_F4FE4326E750
#define F8BF9740_A133_EE18_1629_F4FE4326E750

#include <cmath>
#include <utility>
#include <vector>

namespace pcl { namespace math { namespace algorithm {
    template <typename T>
    T gcd(T a, T b) {
        return b == 0 ? a : gcd(b, a % b);
    }

    template <typename T>
    T lcm(T a, T b) {
        return a / gcd(a, b) * b;
    }

    template <typename T>
    std::pair<T, T> ext_gcd(T a, T b) {
        if (b == 0) return make_pair(1, 0);
        T xd, yd;
        tie(xd, yd) = ext_gcd(b, a % b);
        return make_pair(yd, xd - (a / b) * yd);
    }

    template <typename T>
    std::vector<T> get_primes(T N) {
        std::vector<T> result;
        std::vector<bool> is_not_prime(N);
        for (T i = 2; i <= N; i++) {
            if (is_not_prime[i]) continue;
            result.push_back(i);
            for (T j = i + i; j <= N; j++) is_not_prime[j] = true;
        }
        return result;
    }

    template <typename T>
    T pow(T x, int n) {
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
        for (T i = 1; i <= sqrt(val); i++) {
            if (val % i == 0) return false;
        }
        return true;
    }
}}} // namespace pcl::math::algorithm

#endif /* F8BF9740_A133_EE18_1629_F4FE4326E750 */
