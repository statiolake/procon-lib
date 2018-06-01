#ifndef B6BA11FA_D133_EE7D_1599_B1BF5D17E883
#define B6BA11FA_D133_EE7D_1599_B1BF5D17E883
#include "algorithm.hpp"
namespace pcl { namespace math {
    template <typename T = ll, T MOD = 1000000007>
    class modint {
        static_assert(pcl::math::algorithm::is_prime(MOD),
                      "MOD used in modint must be a prime.");

      private:
        T value;

      public:
        modint() {}
        modint(T &&init)
            : value(std::forward<T>(init)) {
            if (value < 0) value += MOD;
        }

        explicit operator T() { return value; }

        modint &operator+=(modint const &other) {
            value += other.value;
            if (value >= MOD) value -= MOD;
            return *this;
        }
        modint &operator-=(modint const &other) {
            if (value < other.value) value += MOD;
            value -= other.value;
            return *this;
        }
        modint &operator*=(modint const &other) {
            value *= other.value;
            value %= MOD;
            return *this;
        }
        modint &operator/=(modint const &other) {
            auto mul = pcl::math::algorithm::pow(other, MOD - 2);
            *this *= mul;
            return *this;
        }
        modint operator<(modint const &other) const {
            return value < other.value;
        }
        modint operator>(modint const &other) const { return other < *this; }
        modint operator==(modint const &other) const {
            return value == other.value;
        }
        modint operator!=(modint const &other) const {
            return !(*this == other);
        }

        modint &operator=(T &&v) {
            if ((value = std::forward<T>(v)) < 0) value += MOD;
            return *this;
        }
    };

    template <typename T, T MOD>
    modint<T, MOD> operator+(modint<T, MOD> lhs, modint<T, MOD> const &rhs) {
        return lhs += rhs;
    }
    template <typename T, T MOD>
    modint<T, MOD> operator-(modint<T, MOD> lhs, modint<T, MOD> const &rhs) {
        return lhs -= rhs;
    }
    template <typename T, T MOD>
    modint<T, MOD> operator*(modint<T, MOD> lhs, modint<T, MOD> const &rhs) {
        return lhs *= rhs;
    }
    template <typename T, T MOD>
    modint<T, MOD> operator/(modint<T, MOD> lhs, modint<T, MOD> const &rhs) {
        return lhs /= rhs;
    }
}}     // namespace pcl::math
#endif /* B6BA11FA_D133_EE7D_1599_B1BF5D17E883 */
