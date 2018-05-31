#ifndef B6BA11FA_D133_EE7D_1599_B1BF5D17E883
#define B6BA11FA_D133_EE7D_1599_B1BF5D17E883
#include "algorithm.hpp"
namespace pcl { namespace math {
    template <typename T, T MOD>
    class modint;

    template <typename T, T MOD>
    modint<T, MOD> operator+(modint<T, MOD> const &lhs,
                             modint<T, MOD> const &rhs);

    template <typename T, T MOD>
    modint<T, MOD> operator-(modint<T, MOD> const &lhs,
                             modint<T, MOD> const &rhs);

    template <typename T, T MOD>
    modint<T, MOD> operator*(modint<T, MOD> const &lhs,
                             modint<T, MOD> const &rhs);

    template <typename T, T MOD>
    modint<T, MOD> operator/(modint<T, MOD> const &lhs,
                             modint<T, MOD> const &rhs);

    template <typename T, T MOD>
    class modint {
      private:
        T value;
        friend modint operator+<T, MOD>(modint const &lhs, modint const &rhs);
        friend modint operator-<T, MOD>(modint const &lhs, modint const &rhs);
        friend modint operator*<T, MOD>(modint const &lhs, modint const &rhs);
        friend modint operator/<T, MOD>(modint const &lhs, modint const &rhs);

      public:
        modint() {}
        modint(T const &init)
            : value(init % MOD) {}
        modint(modint const &other) { value = other.value; }

        operator T() { return value; }

        modint &operator=(modint const &other) {
            value = other.value;
            return *this;
        }
        modint &operator=(T value) {
            this->value = value % MOD;
            return *this;
        }
        modint &operator+=(modint<T, MOD> const &other) {
            value += other.value;
            value %= MOD;
            return *this;
        }
        modint &operator-=(modint<T, MOD> const &other) {
            value -= other.value;
            value %= MOD;
            return *this;
        }
        modint &operator*=(modint<T, MOD> const &other) {
            value *= other.value;
            value %= MOD;
            return *this;
        }
        modint &operator/=(modint<T, MOD> const &other) {
            *this = *this / other;
            return *this;
        }
    };

    template <typename T, T MOD>
    modint<T, MOD> operator+(modint<T, MOD> const &lhs,
                             modint<T, MOD> const &rhs) {
        return modint<T, MOD>((lhs.value + rhs.value) % MOD);
    }

    template <typename T, T MOD>
    modint<T, MOD> operator-(modint<T, MOD> const &lhs,
                             modint<T, MOD> const &rhs) {
        return modint<T, MOD>((lhs.value + MOD - rhs.value) % MOD);
    }

    template <typename T, T MOD>
    modint<T, MOD> operator*(modint<T, MOD> const &lhs,
                             modint<T, MOD> const &rhs) {
        return modint<T, MOD>((lhs.value * rhs.value) % MOD);
    }
    template <typename T, T MOD>
    modint<T, MOD> operator/(modint<T, MOD> const &lhs,
                             modint<T, MOD> const &rhs) {
        auto mul = pcl::math::algorithm::pow(rhs, MOD - 2);
        return lhs * mul;
    }
}}     // namespace pcl::math
#endif /* B6BA11FA_D133_EE7D_1599_B1BF5D17E883 */
