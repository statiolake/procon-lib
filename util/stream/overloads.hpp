/**
 * @file util/stream/overloads.hpp
 * @brief
 * いくつかの型について、ストリーム入出力演算子をオーバーロードしている。
 */
#pragma once

#include "../../prelude.hpp"

#include <iostream>
#include <vector>
namespace pcl {

/**
 * @brief vector<T> の出力演算子
 * @param[in] v 出力したい vector
 * @return std::ostream & 出力ストリーム
 */
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

/**
 * @brief vector<T> の入力演算子
 * @param[in] v 入力したい対象の vector
 * @return std::istream & 入力ストリーム
 * @details 空白区切りの入力を、 vector
 * の長さの回数だけ受け取って、前から順につめていく関数。 push_back()
 * ではないので、既存の要素を上書きする。
 */
template <typename T>
std::istream &operator>>(std::istream &is, std::vector<T> &v) {
    for (size_t i = 0; i < v.size(); i++) is >> v[i];
    return is;
}

} // namespace pcl
