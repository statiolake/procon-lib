#ifndef E6D6F3A3_3133_EE7A_22DB_4696842CE1C5
#define E6D6F3A3_3133_EE7A_22DB_4696842CE1C5

#include <cmath>
#include <iostream>
#include <type_traits>

namespace pcl {
class dbl {
  private:
    double value;

  public:
    dbl()
        : value() {}
    dbl(double init)
        : value(init) {}
    dbl(dbl const &other)
        : value(other.value) {}

    explicit operator double() const { return value; }

    dbl &operator+=(dbl const &other) {
        value += other.value;
        return *this;
    }
    dbl &operator-=(dbl const &other) {
        value -= other.value;
        return *this;
    }
    dbl &operator*=(dbl const &other) {
        value *= other.value;
        return *this;
    }
    dbl &operator/=(dbl const &other) {
        value /= other.value;
        return *this;
    }

    bool operator==(dbl const &other) const {
        return std::abs(value - other.value) < EPS;
    }
    bool operator!=(dbl const &other) const { return !(*this == other); }
    bool operator<(dbl const &other) const { return value < other.value; }
    bool operator>(dbl const &other) const { return other < *this; }
    bool operator<=(dbl const &other) const {
        return *this < other || *this == other;
    }
    bool operator>=(dbl const &other) const { return other <= *this; }

    dbl &operator=(dbl const &other) {
        value = other.value;
        return *this;
    }
    template <typename Number>
    auto operator=(Number const &other) ->
        typename std::enable_if<std::is_scalar<Number>::value, dbl &>::type {
        *this = dbl(other);
        return *this;
    }
};

dbl operator+(dbl lhs, dbl const &rhs) { return (lhs += rhs); }
dbl operator-(dbl lhs, dbl const &rhs) { return (lhs -= rhs); }
dbl operator*(dbl lhs, dbl const &rhs) { return (lhs *= rhs); }
dbl operator/(dbl lhs, dbl const &rhs) { return (lhs /= rhs); }

template <typename Number>
auto operator+(Number const &lhs, dbl const &rhs) ->
    typename std::enable_if<std::is_scalar<Number>::value, dbl>::type {
    return (dbl(lhs) + rhs);
}
template <typename Number>
auto operator-(Number const &lhs, dbl const &rhs) ->
    typename std::enable_if<std::is_scalar<Number>::value, dbl>::type {
    return (dbl(lhs) - rhs);
}
template <typename Number>
auto operator*(Number const &lhs, dbl const &rhs) ->
    typename std::enable_if<std::is_scalar<Number>::value, dbl>::type {
    return (dbl(lhs) * rhs);
}
template <typename Number>
auto operator/(Number const &lhs, dbl const &rhs) ->
    typename std::enable_if<std::is_scalar<Number>::value, dbl>::type {
    return (dbl(lhs) / rhs);
}

template <typename Number>
auto operator+(dbl lhs, Number const &rhs) ->
    typename std::enable_if<std::is_scalar<Number>::value, dbl>::type {
    return (lhs + dbl(rhs));
}
template <typename Number>
auto operator-(dbl lhs, Number const &rhs) ->
    typename std::enable_if<std::is_scalar<Number>::value, dbl>::type {
    return (lhs - dbl(rhs));
}
template <typename Number>
auto operator*(dbl lhs, Number const &rhs) ->
    typename std::enable_if<std::is_scalar<Number>::value, dbl>::type {
    return (lhs * dbl(rhs));
}
template <typename Number>
auto operator/(dbl lhs, Number const &rhs) ->
    typename std::enable_if<std::is_scalar<Number>::value, dbl>::type {
    return (lhs / dbl(rhs));
}

template <typename Number>
auto operator==(dbl const &lhs, Number const &rhs) ->
    typename std::enable_if<std::is_scalar<Number>::value, bool>::type {
    return lhs == dbl(rhs);
}
template <typename Number>
auto operator!=(dbl const &lhs, Number const &rhs) ->
    typename std::enable_if<std::is_scalar<Number>::value, bool>::type {
    return lhs != dbl(rhs);
}
template <typename Number>
auto operator<(dbl const &lhs, Number const &rhs) ->
    typename std::enable_if<std::is_scalar<Number>::value, bool>::type {
    return lhs < dbl(rhs);
}
template <typename Number>
auto operator>(dbl const &lhs, Number const &rhs) ->
    typename std::enable_if<std::is_scalar<Number>::value, bool>::type {
    return lhs > dbl(rhs);
}
template <typename Number>
auto operator<=(dbl const &lhs, Number const &rhs) ->
    typename std::enable_if<std::is_scalar<Number>::value, bool>::type {
    return lhs <= dbl(rhs);
}
template <typename Number>
auto operator>=(dbl const &lhs, Number const &rhs) ->
    typename std::enable_if<std::is_scalar<Number>::value, bool>::type {
    return lhs >= dbl(rhs);
}

template <typename Number>
auto operator==(Number const &lhs, dbl const &rhs) ->
    typename std::enable_if<std::is_scalar<Number>::value, bool>::type {
    return rhs == lhs;
}
template <typename Number>
auto operator!=(Number const &lhs, dbl const &rhs) ->
    typename std::enable_if<std::is_scalar<Number>::value, bool>::type {
    return rhs != lhs;
}
template <typename Number>
auto operator<(Number const &lhs, dbl const &rhs) ->
    typename std::enable_if<std::is_scalar<Number>::value, bool>::type {
    return rhs > lhs;
}
template <typename Number>
auto operator>(Number const &lhs, dbl const &rhs) ->
    typename std::enable_if<std::is_scalar<Number>::value, bool>::type {
    return rhs < lhs;
}
template <typename Number>
auto operator<=(Number const &lhs, dbl const &rhs) ->
    typename std::enable_if<std::is_scalar<Number>::value, bool>::type {
    return rhs >= lhs;
}
template <typename Number>
auto operator>=(Number const &lhs, dbl const &rhs) ->
    typename std::enable_if<std::is_scalar<Number>::value, bool>::type {
    return rhs <= lhs;
}

std::istream &operator>>(std::istream &is, dbl &d) {
    double value;
    is >> value;
    d = value;
    return is;
}

std::ostream &operator<<(std::ostream &os, dbl const &d) {
    os << (double)d;
    return os;
}
} // namespace pcl

namespace std {
pcl::dbl sqrt(pcl::dbl a) { return pcl::dbl(sqrt((double)a)); }
} // namespace std

#endif /* E6D6F3A3_3133_EE7A_22DB_4696842CE1C5 */
