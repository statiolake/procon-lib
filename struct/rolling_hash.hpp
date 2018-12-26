#pragma once

#include "../prelude.hpp"

#include <cassert>
#include <string>
#include <vector>

namespace pcl {

template <ull b = 100'000'007>
class rolling_hash_ {
  private:
    int size_;
    std::vector<ull> hash_, pow_;

  public:
    rolling_hash(std::string const &s)
        : size_(s.size() + 1)
        , hash_(size_, 0)
        , pow_(size_, 1) {
        for (int i = 1; i < size_; i++) {
            pow_[i] = pow_[i - 1] * b;
        }

        for (int i = 1; i < size_; i++) {
            hash_[i] = hash_[i - 1] * b + s[i - 1];
        }
    }

    ull of_range(int l, int r) {
        assert(in_range_strict(0, {l, r}, size_));
        return hash_[r] - hash_[l] * pow_[r - l];
    }
};
} // namespace pcl
