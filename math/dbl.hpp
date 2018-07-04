#ifndef E6D6F3A3_3133_EE7A_22DB_4696842CE1C5
#define E6D6F3A3_3133_EE7A_22DB_4696842CE1C5

#include <cmath>
#include <iostream>
#include <type_traits>

namespace pcl {
class dbl {
  private:
    double val;

  public:
    dbl()
        : val() {}
    dbl(double init)
        : val(init) {}
    dbl(dbl const &other)
        : val(other.val) {}
    explicit operator double() const { return val; }

#define DERIVE_COMPOUND_OP(op)           \
    dbl &operator op(dbl const &other) { \
        val op other.val;                \
        return *this;                    \
    }
    DERIVE_COMPOUND_OP(+=)
    DERIVE_COMPOUND_OP(-=)
    DERIVE_COMPOUND_OP(*=)
    DERIVE_COMPOUND_OP(/=)
#undef DERIVE_COMPOUND_OP

    bool operator==(dbl const &other) const {
        return std::abs(val - other.val) < EPS;
    }
    bool operator!=(dbl const &other) const { return !(*this == other); }
    bool operator<(dbl const &other) const { return val < other.val; }
    bool operator>(dbl const &other) const { return other < *this; }
    bool operator<=(dbl const &other) const {
        return *this < other || *this == other;
    }
    bool operator>=(dbl const &other) const { return other <= *this; }

    dbl &operator=(dbl const &other) {
        val = other.val;
        return *this;
    }
};

dbl operator+(dbl lhs, dbl const &rhs) { return (lhs += rhs); }
dbl operator-(dbl lhs, dbl const &rhs) { return (lhs -= rhs); }
dbl operator*(dbl lhs, dbl const &rhs) { return (lhs *= rhs); }
dbl operator/(dbl lhs, dbl const &rhs) { return (lhs /= rhs); }

#define DERIVE_OP_SCALAR_LHS(op, rettype)                        \
    template <typename Number>                                   \
    auto operator op(Number const &lhs, dbl const &rhs)          \
        ->typename std::enable_if<std::is_scalar<Number>::value, \
                                  rettype>::type {               \
        return dbl(lhs) op rhs;                                  \
    }
#define DERIVE_OP_SCALAR_RHS(op, rettype)                        \
    template <typename Number>                                   \
    auto operator op(dbl const &lhs, Number const &rhs)          \
        ->typename std::enable_if<std::is_scalar<Number>::value, \
                                  rettype>::type {               \
        return lhs op dbl(rhs);                                  \
    }

DERIVE_OP_SCALAR_LHS(+, dbl)
DERIVE_OP_SCALAR_LHS(-, dbl)
DERIVE_OP_SCALAR_LHS(*, dbl)
DERIVE_OP_SCALAR_LHS(/, dbl)
DERIVE_OP_SCALAR_LHS(==, bool)
DERIVE_OP_SCALAR_LHS(!=, bool)
DERIVE_OP_SCALAR_LHS(<, bool)
DERIVE_OP_SCALAR_LHS(>, bool)
DERIVE_OP_SCALAR_LHS(<=, bool)
DERIVE_OP_SCALAR_LHS(>=, bool)
DERIVE_OP_SCALAR_RHS(+, dbl)
DERIVE_OP_SCALAR_RHS(-, dbl)
DERIVE_OP_SCALAR_RHS(*, dbl)
DERIVE_OP_SCALAR_RHS(/, dbl)
DERIVE_OP_SCALAR_RHS(==, bool)
DERIVE_OP_SCALAR_RHS(!=, bool)
DERIVE_OP_SCALAR_RHS(<, bool)
DERIVE_OP_SCALAR_RHS(>, bool)
DERIVE_OP_SCALAR_RHS(<=, bool)
DERIVE_OP_SCALAR_RHS(>=, bool)

#undef DERIVE_OP_SCALAR_LHS
#undef DERIVE_OP_SCALAR_RHS

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
pcl::dbl sqrt(pcl::dbl a) { return pcl::dbl(sqrt((double)a)); }
} // namespace std

#endif /* E6D6F3A3_3133_EE7A_22DB_4696842CE1C5 */
