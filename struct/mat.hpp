#pragma once

#include "../prelude.hpp"

#include <cassert>
#include <iostream>
#include <vector>

namespace pcl {
template <typename T>
class mat {
  private:
    int h_, w_;
    std::vector<std::vector<T>> val_;

    template <typename U>
    friend bool operator==(mat<U> const &lhs, mat<U> const &rhs);

  public:
    mat(std::vector<std::vector<T>> &&init)
        : h_(init.size())
        , w_(init[0].size())
        , val_(std::move(init)) {
        // the dimension of matrix must be positive.
        // (maybe before approaching this assertion exception is already
        // triggered when attempted to create vector of negative length)
        assert(h_ > 0);
        assert(w_ > 0);

        for (int i = 0; i < h_; i++) {
            // matrix initializer has incompatible size: the number of cols
            // differs row by row.
            assert(w_ == static_cast<int>(val_[i].size()));
        }
    }

    mat(std::vector<std::vector<T>> const &init)
        : mat(std::vector<std::vector<T>>(init)) {}

    mat(int h, int w)
        : mat(std::vector<std::vector<T>>(h, std::vector<T>(w))) {}

    mat(std::initializer_list<std::initializer_list<T>> &&init) {
        for (auto row : std::move(init)) { val_.emplace_back(row); }
        h_ = val_.size();

        // matrix initializer must have positive number of rows.
        assert(h_ > 0);

        w_ = val_[0].size();
        assert(w_ > 0);

        for (int i = 0; i < h_; i++) {
            // matrix initializer has incompatible size: the number of cols
            // differs row by row.
            assert(w_ == static_cast<int>(val_[i].size()));
        }
    }

    mat(mat const &other) = default;

    void resize(int h_, int w_) {
        assert(h_ > 0);
        assert(w_ > 0);

        this->h_ = h_, this->w_ = w_;
        val_.resize(h_);
        for (int i = 0; i < h_; i++) val_.resize(w_);
    }

    int height() const { return h_; }
    int width() const { return w_; }

    inline T const &at(int i, int j) const {
        assert(in_range(0, i, h_));
        assert(in_range(0, j, w_));
        return val_[i][j];
    }

    inline T &at(int i, int j) {
        assert(in_range(0, i, h_));
        assert(in_range(0, j, w_));
        return val_[i][j];
    }

    mat &operator=(mat const &other) {
        h_ = other.h_, w_ = other.w_;
        val_ = other.val_;
        return *this;
    }

    mat &operator=(mat &&other) {
        h_ = other.h_, w_ = other.w_;
        val_ = std::move(other.val_);
        return *this;
    }

    mat operator-() const {
        mat result = *this;
        for (int i = 0; i < h_; i++)
            for (int j = 0; j < w_; j++) result[i][j] = -result[i][j];
        return result;
    }

    mat &operator+=(mat const &other) {
        // assert size restriction: otherwise they're incompatible for +=.
        assert(h_ == other.h_);
        assert(w_ == other.w_);

        for (int i = 0; i < h_; i++)
            for (int j = 0; j < w_; j++) val_[i][j] += other.val_[i][j];
    }

    mat &operator-=(mat const &other) {
        // assert size restriction: otherwise they're incompatible for -=.
        assert(h_ == other.h_);
        assert(w_ == other.w_);

        for (int i = 0; i < h_; i++)
            for (int j = 0; j < w_; j++) val_[i][j] -= other.val_[i][j];
    }

    mat removed(int row, int col) const {
        // the number of rows / cols must be >= 2 to remove row.
        assert(h_ >= 2);
        assert(w_ >= 2);

        mat result(h_ - 1, w_ - 1);
        for (int i = 0; i < h_; i++) {
            if (i == row) continue;
            for (int j = 0; j < h_; j++) {
                if (j == col) continue;
                int ni = i > row ? i - 1 : i;
                int nj = j > col ? j - 1 : j;

                result.val_[ni][nj] = val_[i][j];
            }
        }
        return result;
    }

    T det() const {
        // if non-square matrix, cannot calculate determinant.
        assert(h_ == w_);

        if (h_ == 1) return val_[h_][w_];
        if (h_ == 2) return val_[0][0] * val_[1][1] - val_[0][1] * val_[1][0];

        T val_det{};
        for (int i = 0; i < h_; i++)
            val_det +=
                removed(i, 0).det() * val_[i][0] * (i % 2 == 0 ? 1 : -1);

        return val_det;
    }
};

template <typename T>
bool operator==(mat<T> const &lhs, mat<T> const &rhs) {
    int h = lhs.height(), w = lhs.width();
    assert(h == rhs.height());
    assert(w == rhs.width());
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            if (lhs.at(i, j) != rhs.at(i, j)) return false;
    return true;
}

template <typename T>
bool operator!=(mat<T> const &lhs, mat<T> const &rhs) {
    return !(lhs == rhs);
}

template <typename T>
mat<T> operator+(mat<T> lhs, mat<T> const &rhs) {
    return (lhs += rhs);
}

template <typename T>
mat<T> operator-(mat<T> lhs, mat<T> const &rhs) {
    return (lhs -= rhs);
}

template <typename T>
mat<T> operator*(mat<T> const &lhs, mat<T> const &rhs) {
    int n = lhs.height(), m = lhs.width(), l = rhs.width();

    // assert size restriction: otherwise they're incompatible for *.
    assert(m == rhs.height());

    mat<T> result(n, l);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < l; j++)
            for (int k = 0; k < m; k++)
                result.at(i, j) += lhs.at(i, k) * rhs.at(k, j);

    return result;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, mat<T> const &m) {
    os << "{ ";
    for (int i = 0; i < m.height(); i++) {
        if (i != 0) os << ", ";
        os << "{ ";
        for (int j = 0; j < m.width(); j++) {
            if (j != 0) os << ", ";
            os << m.at(i, j);
        }
        os << " }";
    }
    os << " }";
    return os;
}

template <typename T>
std::istream &operator>>(std::istream &is, mat<T> &m) {
    for (int i = 0; i < m.height(); i++)
        for (int j = 0; j < m.width(); j++) is >> m.at(i, j);
    return is;
}
} // namespace pcl
