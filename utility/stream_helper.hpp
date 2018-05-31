#ifndef STREAM_HELPER_HPP_DNIKPKZJ
#define STREAM_HELPER_HPP_DNIKPKZJ

#include <iostream>
#include <vector>
namespace pcl { namespace utility {
    // useful for debug printing
    template <typename T>
    std::ostream &operator<<(std::ostream &os, std::vector<T> const &v) {
        for (size_t i = 0; i < v.size(); i++) {
            if (i != 0) os << ", ";
            os << v[i];
        }
        os << std::endl;
        return os;
    }

    template <typename T>
    std::ostream &operator<<(std::ostream &os,
                             std::vector<std::vector<T>> const &v) {
        for (auto const &x : v) os << x;
        return os;
    }

    // useful for getting input
    template <typename T>
    std::istream &operator>>(std::istream &is, std::vector<T> &v) {
        for (size_t i = 0; i < v.size(); i++) is >> v[i];
        return is;
    }

    // useful for getting input
    template <typename T>
    std::istream &operator>>(std::istream &is,
                             std::vector<std::vector<T>> &v) {
        for (size_t i = 0; i < v.size(); i++) is >> v[i];
        return is;
    }
}} // namespace pcl::utility

#endif /* end of include guard: STREAM_HELPER_HPP_DNIKPKZJ */