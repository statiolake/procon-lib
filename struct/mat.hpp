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
    std::vector<std::vector<T>> v_;

    template <typename U>
    friend bool operator==(mat<U> const &a, mat<U> const &b);

  public:
    mat(std::vector<std::vector<T>> &&init)
        : h_(init.size())
        , w_(init[0].size())
        , v_(std::move(init)) {
        // the dimension of matrix must be positive.
        // (maybe before approaching this assertion exception is already
        // triggered when attempted to create vector of negative length)
        assert(h_ > 0);
        assert(w_ > 0);

        for (int i = 0; i < h_; i++) {
            // matrix initializer has incompatible size: the number of cols
            // differs row by row.
            assert(w_ == static_cast<int>(v_[i].size()));
        }
    }

    mat(std::vector<std::vector<T>> const &init)
        : mat(std::vector<std::vector<T>>(init)) {
    }

    mat(int h, int w)
        : mat(std::vector<std::vector<T>>(h, std::vector<T>(w))) {
    }

    mat(std::initializer_list<std::initializer_list<T>> &&init) {
        for (auto row : std::move(init)) {
            v_.emplace_back(row);
        }
        h_ = v_.size();

        // matrix initializer must have positive number of rows.
        assert(h_ > 0);

        w_ = v_[0].size();
        assert(w_ > 0);

        for (int i = 0; i < h_; i++) {
            // matrix initializer has incompatible size: the number of cols
            // differs row by row.
            assert(w_ == static_cast<int>(v_[i].size()));
        }
    }

    mat(mat const &o) = default;

    void resize(int h, int w) {
        assert(h > 0);
        assert(w > 0);
        h_ = h, w_ = w;

        v_.resize(h_);
        for (int i = 0; i < h_; i++) v_.resize(w_);
    }

    int height() const {
        return h_;
    }
    int width() const {
        return w_;
    }

    inline T const &at(int i, int j) const {
        assert(in_range(0, i, h_));
        assert(in_range(0, j, w_));
        return v_[i][j];
    }

    inline T &at(int i, int j) {
        assert(in_range(0, i, h_));
        assert(in_range(0, j, w_));
        return v_[i][j];
    }

    mat &operator=(mat const &o) {
        h_ = o.h_, w_ = o.w_;
        v_ = o.v_;
        return *this;
    }

    mat &operator=(mat &&o) {
        h_ = o.h_, w_ = o.w_;
        v_ = std::move(o.v_);
        return *this;
    }

    mat operator-() const {
        mat res = *this;
        for (int i = 0; i < h_; i++)
            for (int j = 0; j < w_; j++) res[i][j] = -res[i][j];
        return res;
    }

    mat &operator+=(mat const &o) {
        // assert size restriction: otherwise they're incompatible for +=.
        assert(h_ == o.h_);
        assert(w_ == o.w_);

        for (int i = 0; i < h_; i++)
            for (int j = 0; j < w_; j++) v_[i][j] += o.v_[i][j];
    }

    mat &operator-=(mat const &o) {
        // assert size restriction: otherwise they're incompatible for -=.
        assert(h_ == o.h_);
        assert(w_ == o.w_);

        for (int i = 0; i < h_; i++)
            for (int j = 0; j < w_; j++) v_[i][j] -= o.v_[i][j];
    }

    mat removed(int r, int l) const {
        // the number of rows / cols must be >= 2 to remove row.
        assert(h_ >= 2);
        assert(w_ >= 2);

        mat res(h_ - 1, w_ - 1);
        for (int i = 0; i < h_; i++) {
            if (i == r) continue;
            for (int j = 0; j < h_; j++) {
                if (j == l) continue;
                int ni = i > r ? i - 1 : i;
                int nj = j > l ? j - 1 : j;

                res.v_[ni][nj] = v_[i][j];
            }
        }
        return res;
    }

    T det() const {
        // if non-square matrix, cannot calculate determinant.
        assert(h_ == w_);

        if (h_ == 1) return v_[h_][w_];
        if (h_ == 2) return v_[0][0] * v_[1][1] - v_[0][1] * v_[1][0];

        T v_det{};
        for (int i = 0; i < h_; i++)
            v_det += removed(i, 0).det() * v_[i][0] * (i % 2 == 0 ? 1 : -1);

        return v_det;
    }
};

template <typename T>
bool operator==(mat<T> const &a, mat<T> const &b) {
    int h = a.height(), w = a.width();
    assert(h == b.height());
    assert(w == b.width());
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            if (a.at(i, j) != b.at(i, j)) return false;
    return true;
}

template <typename T>
bool operator!=(mat<T> const &a, mat<T> const &b) {
    return !(a == b);
}

template <typename T>
mat<T> operator+(mat<T> a, mat<T> const &b) {
    return (a += b);
}

template <typename T>
mat<T> operator-(mat<T> a, mat<T> const &b) {
    return (a -= b);
}

template <typename T>
mat<T> operator*(mat<T> const &a, mat<T> const &b) {
    int n = a.height(), m = a.width(), l = b.width();

    // assert size restriction: otherwise they're incompatible for *.
    assert(m == b.height());

    mat<T> res(n, l);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < l; j++)
            for (int k = 0; k < m; k++)
                res.at(i, j) += a.at(i, k) * b.at(k, j);

    return res;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, mat<T> const &m) {
    os << "mat { ";
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
