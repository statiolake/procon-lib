#ifndef ASSERT_HPP
#define ASSERT_HPP

#include <iostream>
#include <string>

#include "alias.hpp"

namespace pcl {
template <typename Printer>
void _assert_failed(char const *expr, Printer showmsg, char const *file,
                    unsigned line) {
    std::cerr << "!!!!! Assertion Failed !!!!!" << std::endl;
    std::cerr << "  ---> `" << expr << "` at " << file << ", line " << line
              << std::endl;
    showmsg();
    abort();
}

#define DEFINE_ASSERT_XX(xx, cond_op)                                     \
    template <typename T, typename U>                                     \
    void _assert_##xx(char const *expr1_str, char const *expr2_str,       \
                      T const &expr1, U const &expr2, char const *msg,    \
                      char const *file, unsigned line) {                  \
        if (!(expr1 cond_op expr2)) {                                     \
            std::string es =                                              \
                std::string(expr1_str) + " " #cond_op " " + expr2_str;    \
            auto printer = [&]() {                                        \
                if (msg[0] != 0) std::cerr << "  | " << msg << std::endl; \
                std::cerr << "  | left:  " << expr1 << std::endl;         \
                std::cerr << "  | right: " << expr2 << std::endl;         \
            };                                                            \
            _assert_failed(es.c_str(), printer, file, line);              \
        }                                                                 \
    }

DEFINE_ASSERT_XX(eq, ==)
DEFINE_ASSERT_XX(ne, !=)
DEFINE_ASSERT_XX(gt, >)
DEFINE_ASSERT_XX(lt, <)
DEFINE_ASSERT_XX(ge, >=)
DEFINE_ASSERT_XX(le, <=)

template <typename T, typename U, typename V>
void _assert_range(T const &begin, char const *mid_str, U const &mid,
                   V const &end, char const *msg, char const *file,
                   unsigned line) {
    if (!in_range(begin, mid, end)) {
        std::string es = "";
        es += std::to_string(begin) + " <= " + mid_str + " (" +
              std::to_string(mid) + ") < " + std::to_string(end);
        auto printer = [&]() {
            std::cerr << "  | variable is not in range." << std::endl;
            if (msg[0] != 0) std::cerr << "  | " << msg << std::endl;
        };
        _assert_failed(es.c_str(), printer, file, line);
    }
}

#undef DEFINE_ASSERT_XX
} // namespace pcl

#ifdef NOASSERT
#define ASSERT(...)
#define ASSERT_RANGE(...)
#define ASSERT_EQ(...)
#define ASSERT_NE(...)
#define ASSERT_GT(...)
#define ASSERT_LT(...)
#define ASSERT_GE(...)
#define ASSERT_LE(...)
#else
#define ASSERT(expr, msg)                                                  \
    (void)(!(expr) && (pcl::_assert_failed(#expr,                          \
                                           [&]() {                         \
                                               if ((msg)[0] != 0)          \
                                                   std::cerr << "  | "     \
                                                             << msg        \
                                                             << std::endl; \
                                           },                              \
                                           __FILE__, __LINE__),            \
                       0))
#define ASSERT_RANGE(begin, mid, end, msg) \
    pcl::_assert_range(begin, #mid, mid, end, msg, __FILE__, __LINE__)
#define CALL_ASSERT_XX(xx, expr1, expr2, msg) \
    pcl::_assert_##xx(#expr1, #expr2, expr1, expr2, msg, __FILE__, __LINE__)
#define ASSERT_EQ(expr1, expr2, msg) CALL_ASSERT_XX(eq, expr1, expr2, msg)
#define ASSERT_NE(expr1, expr2, msg) CALL_ASSERT_XX(ne, expr1, expr2, msg)
#define ASSERT_GT(expr1, expr2, msg) CALL_ASSERT_XX(gt, expr1, expr2, msg)
#define ASSERT_LT(expr1, expr2, msg) CALL_ASSERT_XX(lt, expr1, expr2, msg)
#define ASSERT_GE(expr1, expr2, msg) CALL_ASSERT_XX(ge, expr1, expr2, msg)
#define ASSERT_LE(expr1, expr2, msg) CALL_ASSERT_XX(le, expr1, expr2, msg)
#endif
#endif /* ASSERT_HPP */
