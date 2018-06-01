#ifndef STREAM_HELPER_HPP_DNIKPKZJ
#define STREAM_HELPER_HPP_DNIKPKZJ

#include <iostream>
#include <vector>
namespace pcl { namespace utility {
    template <typename T>
    std::ostream &operator<<(std::ostream &os, std::vector<T> const &v) {
        os << '[';
        for (size_t i = 0; i < v.size(); i++) {
            if (i != 0) os << ", ";
            os << v[i];
        }
        os << ']';
        return os;
    }

    template <typename T>
    std::ostream &operator<<(std::ostream &os,
                             std::vector<std::vector<T>> const &v) {
        for (auto const &x : v) os << x;
        return os;
    }

    template <typename T>
    std::istream &operator>>(std::istream &is, std::vector<T> &v) {
        for (size_t i = 0; i < v.size(); i++) is >> v[i];
        return is;
    }

    template <typename T>
    std::istream &operator>>(std::istream &is,
                             std::vector<std::vector<T>> &v) {
        for (size_t i = 0; i < v.size(); i++) is >> v[i];
        return is;
    }
}} // namespace pcl::utility

// so that overloaded operators can be found
using namespace pcl::utility;

#endif /* end of include guard: STREAM_HELPER_HPP_DNIKPKZJ */
