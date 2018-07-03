#ifndef ASSERT_HPP
#define ASSERT_HPP

#include <iostream>
#include <string>

#include "alias.hpp"

namespace pcl {
template <typename MessagePrinter>
void _assert_failed(char const *expr, MessagePrinter msg_printer,
                    char const *file, unsigned line) {
    std::cerr << "Assertion Failed." << std::endl;
    std::cerr << "  ---> `" << expr << "` at " << file << ", line " << line
              << std::endl;
    msg_printer();
    abort();
}

#define DEFINE_ASSERT_XX(xx, cond_op)                                      \
    template <typename T>                                                  \
    void _assert_##xx(char const *expr1_str, char const *expr2_str,        \
                      T const &expr1, T const &expr2, char const *message, \
                      char const *file, unsigned line) {                   \
        if (!(expr1 cond_op expr2)) {                                      \
            std::string expr_str = "";                                     \
            expr_str += expr1_str;                                         \
            expr_str += " == ";                                            \
            expr_str += expr2_str;                                         \
            auto printer = [&]() {                                         \
                if (message[0] != 0)                                       \
                    std::cerr << "  | " << message << std::endl;           \
                std::cerr << "  | left:  " << expr1 << std::endl;          \
                std::cerr << "  | right: " << expr2 << std::endl;          \
            };                                                             \
            _assert_failed(expr_str.c_str(), printer, file, line);         \
        }                                                                  \
    }

DEFINE_ASSERT_XX(eq, ==)
DEFINE_ASSERT_XX(ne, !=)
DEFINE_ASSERT_XX(gt, >)
DEFINE_ASSERT_XX(lt, <)
DEFINE_ASSERT_XX(ge, >=)
DEFINE_ASSERT_XX(le, <=)

template <typename T, typename U, typename V>
void _assert_range(T const &begin, char const *mid_str, U const &mid,
                   V const &end, char const *message, char const *file,
                   unsigned line) {
    if (!in_range(begin, mid, end)) {
        std::string expr_str = "";
        expr_str += std::to_string(begin);
        expr_str += " <= ";
        expr_str += mid_str;
        expr_str += " (";
        expr_str += std::to_string(mid);
        expr_str += ") < ";
        expr_str += std::to_string(end);
        auto printer = [&]() {
            std::cerr << "  | variable is not in range." << std::endl;
            if (message[0] != 0) std::cerr << "  | " << message << std::endl;
        };
        _assert_failed(expr_str.c_str(), printer, file, line);
    }
}

#undef DEFINE_ASSERT_XX
} // namespace pcl

#ifndef NOASSERT
#define ASSERT(expr, message)                                              \
    (!(expr) && pcl::_assert_failed(#expr,                                 \
                                    []() {                                 \
                                        if (message[0] != 0)               \
                                            std::cerr << "  | " << message \
                                                      << std::endl;        \
                                    },                                     \
                                    __FILE__, __LINE__))
#define ASSERT_RANGE(begin, mid, end, message) \
    pcl::_assert_range(begin, #mid, mid, end, message, __FILE__, __LINE__)

#define ASSERT_EQ(expr1, expr2, message)                                 \
    pcl::_assert_eq(#expr1, #expr2, (expr1), (expr2), message, __FILE__, \
                    __LINE__)
#define ASSERT_NE(expr1, expr2, message)                                 \
    pcl::_assert_ne(#expr1, #expr2, (expr1), (expr2), message, __FILE__, \
                    __LINE__)
#define ASSERT_GT(expr1, expr2, message)                                 \
    pcl::_assert_gt(#expr1, #expr2, (expr1), (expr2), message, __FILE__, \
                    __LINE__)
#define ASSERT_LT(expr1, expr2, message)                                 \
    pcl::_assert_lt(#expr1, #expr2, (expr1), (expr2), message, __FILE__, \
                    __LINE__)
#define ASSERT_GE(expr1, expr2, message)                                 \
    pcl::_assert_ge(#expr1, #expr2, (expr1), (expr2), message, __FILE__, \
                    __LINE__)
#define ASSERT_LE(expr1, expr2, message)                                 \
    pcl::_assert_le(#expr1, #expr2, (expr1), (expr2), message, __FILE__, \
                    __LINE__)
#else
#define ASSERT(...)
#define ASSERT_RANGE(...)
#define ASSERT_EQ(...)
#define ASSERT_NE(...)
#define ASSERT_GT(...)
#define ASSERT_LT(...)
#define ASSERT_GE(...)
#define ASSERT_LE(...)
#endif

#endif /* ASSERT_HPP */
