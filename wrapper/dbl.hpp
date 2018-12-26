#pragma once

#include "../prelude.hpp"

#include <cmath>
#include <iostream>
#include <type_traits>

namespace pcl {
class dbl {
  private:
    double v;

    friend bool operator==(dbl const &a, dbl const &b);
    friend bool operator!=(dbl const &a, dbl const &b);
    friend bool operator<(dbl const &a, dbl const &b);
    friend bool operator>(dbl const &a, dbl const &b);
    friend bool operator<=(dbl const &a, dbl const &b);
    friend bool operator>=(dbl const &a, dbl const &b);

  public:
    dbl()
        : v() {
    }
    dbl(double init)
        : v(init) {
    }
    dbl(dbl const &o)
        : v(o.v) {
    }
    explicit operator double() const {
        return v;
    }

    inline dbl &operator+=(dbl const &o) {
        v += o.v;
        return *this;
    }

    inline dbl &operator-=(dbl const &o) {
        v -= o.v;
        return *this;
    }

    inline dbl &operator*=(dbl const &o) {
        v *= o.v;
        return *this;
    }

    inline dbl &operator/=(dbl const &o) {
        v /= o.v;
        return *this;
    }

    inline dbl &operator=(dbl const &o) {
        v = o.v;
        return *this;
    }
};

inline dbl operator+(dbl a, dbl const &b) {
    return (a += b);
}
inline dbl operator-(dbl a, dbl const &b) {
    return (a -= b);
}
inline dbl operator*(dbl a, dbl const &b) {
    return (a *= b);
}
inline dbl operator/(dbl a, dbl const &b) {
    return (a /= b);
}

inline bool operator==(dbl const &a, dbl const &b) {
    return std::abs(a.v - b.v) < EPS;
}
inline bool operator!=(dbl const &a, dbl const &b) {
    return !(a == b);
}
inline bool operator<=(dbl const &a, dbl const &b) {
    return a.v < b.v || a == b;
}
inline bool operator>=(dbl const &a, dbl const &b) {
    return a.v > b.v || a == b;
}
inline bool operator<(dbl const &a, dbl const &b) {
    return !(a >= b);
}
inline bool operator>(dbl const &a, dbl const &b) {
    return !(a <= b);
}

inline dbl operator+(dbl const &a, double b) {
    return a + dbl(b);
}
inline dbl operator-(dbl const &a, double b) {
    return a - dbl(b);
}
inline dbl operator*(dbl const &a, double b) {
    return a * dbl(b);
}
inline dbl operator/(dbl const &a, double b) {
    return a / dbl(b);
}

inline bool operator==(dbl const &a, double b) {
    return a == dbl(b);
}
inline bool operator!=(dbl const &a, double b) {
    return a != dbl(b);
}
inline bool operator<(dbl const &a, double b) {
    return a < dbl(b);
}
inline bool operator>(dbl const &a, double b) {
    return a > dbl(b);
}
inline bool operator<=(dbl const &a, double b) {
    return a <= dbl(b);
}
inline bool operator>=(dbl const &a, double b) {
    return a >= dbl(b);
}

inline dbl operator+(double a, dbl const &b) {
    return dbl(a) + b;
}
inline dbl operator-(double a, dbl const &b) {
    return dbl(a) - b;
}
inline dbl operator*(double a, dbl const &b) {
    return dbl(a) * b;
}
inline dbl operator/(double a, dbl const &b) {
    return dbl(a) / b;
}

inline bool operator==(double a, dbl const &b) {
    return dbl(a) == b;
}
inline bool operator!=(double a, dbl const &b) {
    return dbl(a) != b;
}
inline bool operator<(double a, dbl const &b) {
    return dbl(a) < b;
}
inline bool operator>(double a, dbl const &b) {
    return dbl(a) > b;
}
inline bool operator<=(double a, dbl const &b) {
    return dbl(a) <= b;
}
inline bool operator>=(double a, dbl const &b) {
    return dbl(a) >= b;
}

std::istream &operator>>(std::istream &is, dbl &d) {
    double v;
    is >> v;
    d = v;
    return is;
}

std::ostream &operator<<(std::ostream &os, dbl const &d) {
    os << (double)d;
    return os;
}
} // namespace pcl

namespace std {
pcl::dbl sqrt(pcl::dbl const &a) {
    return pcl::dbl(sqrt(static_cast<double>(a)));
}
pcl::dbl min(pcl::dbl const &a, pcl::dbl const &b) {
    return a < b ? a : b;
}
pcl::dbl max(pcl::dbl const &a, pcl::dbl const &b) {
    return a < b ? b : a;
}
} // namespace std
