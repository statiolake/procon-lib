#ifndef B6BA11FA_D133_EE7D_1599_B1BF5D17E883
#define B6BA11FA_D133_EE7D_1599_B1BF5D17E883
#include "algorithm.hpp"
namespace pcl { namespace math {
    template <typename T = ll, T MOD = 1'000'000'007>
    class modint {
      private:
        T value;
        static inline T inv(T a) { return inv_impl(a, MOD); }
        static T inv_impl(T a, T b) {
            return (a == 1 ? 1 : (1 - b * inv_impl(b % a, a)) / a + b);
        }

      public:
        modint() {}
        template <typename U>
        modint(U &&init)
            : value(std::forward<U>(init)) {
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
            auto i = inv(other.value);
            *this *= i;
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

        template <typename U>
        modint &operator=(U &&v) {
            if ((value = std::forward<U>(v)) < 0) value += MOD;
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
