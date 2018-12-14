#pragma once

#include "../prelude.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

namespace pcl {
class suffix_array {
  private:
    // size_ is (s_.size() + 1) since empty string ("") is also suffix.
    int const size_;
    std::string const s_;
    std::vector<int> a_;

  public:
    suffix_array(std::string const &s)
        : size_(s.size() + 1)
        , s_(s)
        , a_(size_) {
        std::vector<int> rank(size_);
        for (int i = 0; i < size_; i++) a_[i] = i;
        for (int i = 0; i < size_; i++) rank[i] = s[i];
        for (int k = 1; k < size_; k *= 2) {
            auto cmp = [&](int ia, int ib) {
                if (rank[ia] != rank[ib]) {
                    return rank[ia] < rank[ib];
                } else {
                    int ra = -1, rb = -1;
                    if (ia + k < size_) ra = rank[ia + k];
                    if (ib + k < size_) rb = rank[ib + k];
                    return ra < rb;
                }
            };
            std::sort(a_.begin(), a_.end(), cmp);

            std::vector<int> tmp(size_);
            tmp[a_[0]] = 0;
            for (int i = 1, j = 0; i < size_; i++) {
                if (rank[a_[i]] == rank[a_[i - 1]]) {
                    // the former half is same. check the latter half.
                    if (a_[i - 1] + k >= size_) {
                        // then previous item doesn't have a latter half.
                        // check if current item has a latter half or not. if
                        // it has, then previous < current because current is
                        // the same with previous in the former half but
                        // longer than previous.
                        if (a_[i] + k < size_) j++;
                    } else {
                        // then previous item is present, current item must be
                        // present.
                        assert(a_[i] + k < size_);
                        if (rank[a_[i - 1] + k] < rank[a_[i] + k]) j++;
                    }
                } else {
                    // the former half is different. of course previous item
                    // must have the former rank.
                    assert(rank[a_[i - 1]] < rank[a_[i]]);
                    j++;
                }
                tmp[a_[i]] = j;
            }
            rank = tmp;
        }
    }

    bool matches(std::string const &s) {
        auto cmp = [&](int a, std::string const &b) {
            return s_.compare(a, b.size(), b) < 0;
        };
        auto it = std::lower_bound(a_.begin(), a_.end(), s, cmp);
        if (it == a_.end()) return false;

        // check if it really matches:
        // `... -1 -1 -1 -1 1    1 1 1 ...` is not a match.
        //                  ^-it
        return s_.compare(*it, s.size(), s) == 0;
    }
};
} // namespace pcl
