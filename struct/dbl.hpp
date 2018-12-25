#pragma once

#include "../prelude.hpp"

#include <cmath>
#include <iostream>
#include <type_traits>

namespace pcl {
class dbl {
  private:
    double val;

    friend bool operator==(dbl const &lhs, dbl const &rhs);
    friend bool operator!=(dbl const &lhs, dbl const &rhs);
    friend bool operator<(dbl const &lhs, dbl const &rhs);
    friend bool operator>(dbl const &lhs, dbl const &rhs);
    friend bool operator<=(dbl const &lhs, dbl const &rhs);
    friend bool operator>=(dbl const &lhs, dbl const &rhs);

  public:
    dbl()
        : val() {}
    dbl(double init)
        : val(init) {}
    dbl(dbl const &other)
        : val(other.val) {}
    explicit operator double() const { return val; }

    inline dbl &operator+=(dbl const &other) {
        val += other.val;
        return *this;
    }

    inline dbl &operator-=(dbl const &other) {
        val -= other.val;
        return *this;
    }

    inline dbl &operator*=(dbl const &other) {
        val *= other.val;
        return *this;
    }

    inline dbl &operator/=(dbl const &other) {
        val /= other.val;
        return *this;
    }

    inline dbl &operator=(dbl const &other) {
        val = other.val;
        return *this;
    }
};

inline dbl operator+(dbl lhs, dbl const &rhs) { return (lhs += rhs); }
inline dbl operator-(dbl lhs, dbl const &rhs) { return (lhs -= rhs); }
inline dbl operator*(dbl lhs, dbl const &rhs) { return (lhs *= rhs); }
inline dbl operator/(dbl lhs, dbl const &rhs) { return (lhs /= rhs); }

inline bool operator==(dbl const &lhs, dbl const &rhs) { return std::abs(lhs.val - rhs.val) < EPS; }

inline bool operator!=(dbl const &lhs, dbl const &rhs) { return !(lhs == rhs); }

inline bool operator<=(dbl const &lhs, dbl const &rhs) { return lhs.val < rhs.val || lhs == rhs; }

inline bool operator>=(dbl const &lhs, dbl const &rhs) { return lhs.val > rhs.val || lhs == rhs; }

inline bool operator<(dbl const &lhs, dbl const &rhs) { return !(lhs >= rhs); }

inline bool operator>(dbl const &lhs, dbl const &rhs) { return !(lhs <= rhs); }

inline dbl operator+(dbl const &lhs, double rhs) { return lhs + dbl(rhs); }
inline dbl operator-(dbl const &lhs, double rhs) { return lhs - dbl(rhs); }
inline dbl operator*(dbl const &lhs, double rhs) { return lhs * dbl(rhs); }
inline dbl operator/(dbl const &lhs, double rhs) { return lhs / dbl(rhs); }
inline bool operator==(dbl const &lhs, double rhs) { return lhs == dbl(rhs); }
inline bool operator!=(dbl const &lhs, double rhs) { return lhs != dbl(rhs); }
inline bool operator<(dbl const &lhs, double rhs) { return lhs < dbl(rhs); }
inline bool operator>(dbl const &lhs, double rhs) { return lhs > dbl(rhs); }
inline bool operator<=(dbl const &lhs, double rhs) { return lhs <= dbl(rhs); }
inline bool operator>=(dbl const &lhs, double rhs) { return lhs >= dbl(rhs); }

inline dbl operator+(double lhs, dbl const &rhs) { return dbl(lhs) + rhs; }
inline dbl operator-(double lhs, dbl const &rhs) { return dbl(lhs) - rhs; }
inline dbl operator*(double lhs, dbl const &rhs) { return dbl(lhs) * rhs; }
inline dbl operator/(double lhs, dbl const &rhs) { return dbl(lhs) / rhs; }
inline bool operator==(double lhs, dbl const &rhs) { return dbl(lhs) == rhs; }
inline bool operator!=(double lhs, dbl const &rhs) { return dbl(lhs) != rhs; }
inline bool operator<(double lhs, dbl const &rhs) { return dbl(lhs) < rhs; }
inline bool operator>(double lhs, dbl const &rhs) { return dbl(lhs) > rhs; }
inline bool operator<=(double lhs, dbl const &rhs) { return dbl(lhs) <= rhs; }
inline bool operator>=(double lhs, dbl const &rhs) { return dbl(lhs) >= rhs; }

std::istream &operator>>(std::istream &is, dbl &d) {
    double val;
    is >> val;
    d = val;
    return is;
}

std::ostream &operator<<(std::ostream &os, dbl const &d) {
    os << (double)d;
    return os;
}
} // namespace pcl

namespace std {
pcl::dbl sqrt(pcl::dbl const &a) { return pcl::dbl(sqrt((double)a)); }

pcl::dbl min(pcl::dbl const &lhs, pcl::dbl const &rhs) { return lhs < rhs ? lhs : rhs; }

pcl::dbl max(pcl::dbl const &lhs, pcl::dbl const &rhs) { return lhs < rhs ? rhs : lhs; }
} // namespace std
