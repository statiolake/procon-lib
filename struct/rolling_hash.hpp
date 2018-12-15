#pragma once

#include "../prelude.hpp"

#include <cassert>
#include <string>
#include <vector>

namespace pcl {

template <ull b = 100'000'007>
class rolling_hash {
  private:
    int size_;
    std::vector<ull> hash, pow;

  public:
    rolling_hash(std::string const &s)
        : size_(s.size() + 1)
        , hash(size_, 0)
        , pow(size_, 1) {
        for (int i = 1; i < size_; i++) pow[i] = pow[i - 1] * b;
        for (int i = 1; i < size_; i++) hash[i] = hash[i - 1] * b + s[i - 1];
    }

    ull range(int l, int r) {
        assert(strict_in_range(0, {l, r}, size_));
        return hash[r] - hash[l] * pow[r - l];
    }
};
} // namespace pcl
