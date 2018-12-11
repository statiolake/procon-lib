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
    explicit explicit operator double() const { return val; }

    dbl &operator+=(dbl const &other) {
        val += other.val;
        return *this;
    }

    dbl &operator-=(dbl const &other) {
        val -= other.val;
        return *this;
    }

    dbl &operator*=(dbl const &other) {
        val *= other.val;
        return *this;
    }

    dbl &operator/=(dbl const &other) {
        val /= other.val;
        return *this;
    }

    dbl &operator=(dbl const &other) {
        val = other.val;
        return *this;
    }
};

dbl operator+(dbl lhs, dbl const &rhs) { return (lhs += rhs); }
dbl operator-(dbl lhs, dbl const &rhs) { return (lhs -= rhs); }
dbl operator*(dbl lhs, dbl const &rhs) { return (lhs *= rhs); }
dbl operator/(dbl lhs, dbl const &rhs) { return (lhs /= rhs); }

bool operator==(dbl const &lhs, dbl const &rhs) {
    return eqdbl(lhs.val, rhs.val);
}

bool operator!=(dbl const &lhs, dbl const &rhs) {
    return nedbl(lhs.val, rhs.val);
}

bool operator<(dbl const &lhs, dbl const &rhs) {
    return ltdbl(lhs.val, rhs.val);
}

bool operator>(dbl const &lhs, dbl const &rhs) {
    return gtdbl(lhs.val, rhs.val);
}

bool operator<=(dbl const &lhs, dbl const &rhs) {
    return ledbl(lhs.val, rhs.val);
}

bool operator>=(dbl const &lhs, dbl const &rhs) {
    return gedbl(lhs.val, rhs.val);
}

dbl operator+(dbl const &lhs, double rhs) { return lhs + dbl(rhs); }
dbl operator-(dbl const &lhs, double rhs) { return lhs - dbl(rhs); }
dbl operator*(dbl const &lhs, double rhs) { return lhs * dbl(rhs); }
dbl operator/(dbl const &lhs, double rhs) { return lhs / dbl(rhs); }
bool operator==(dbl const &lhs, double rhs) { return lhs == dbl(rhs); }
bool operator!=(dbl const &lhs, double rhs) { return lhs != dbl(rhs); }
bool operator<(dbl const &lhs, double rhs) { return lhs < dbl(rhs); }
bool operator>(dbl const &lhs, double rhs) { return lhs > dbl(rhs); }
bool operator<=(dbl const &lhs, double rhs) { return lhs <= dbl(rhs); }
bool operator>=(dbl const &lhs, double rhs) { return lhs >= dbl(rhs); }

dbl operator+(double lhs, dbl const &rhs) { return dbl(lhs) + rhs; }
dbl operator-(double lhs, dbl const &rhs) { return dbl(lhs) - rhs; }
dbl operator*(double lhs, dbl const &rhs) { return dbl(lhs) * rhs; }
dbl operator/(double lhs, dbl const &rhs) { return dbl(lhs) / rhs; }
bool operator==(double lhs, dbl const &rhs) { return dbl(lhs) == rhs; }
bool operator!=(double lhs, dbl const &rhs) { return dbl(lhs) != rhs; }
bool operator<(double lhs, dbl const &rhs) { return dbl(lhs) < rhs; }
bool operator>(double lhs, dbl const &rhs) { return dbl(lhs) > rhs; }
bool operator<=(double lhs, dbl const &rhs) { return dbl(lhs) <= rhs; }
bool operator>=(double lhs, dbl const &rhs) { return dbl(lhs) >= rhs; }

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
} // namespace std
