#ifndef MAT_HPP
#define MAT_HPP
#include <vector>
namespace pcl {
template <typename T>
struct mat {
    std::size_t n, m;
    std::vector<std::vector<T>> val;

    mat(std::size_t n, std::size_t m)
        : n(n)
        , m(m)
        , val(n, std::vector<T>(m)) {
        ASSERT_GT(n, 0, "the dimension of matrix must be positive.");
        ASSERT_GT(m, 0, "the dimension of matrix must be positive.");
    }

    mat(std::initializer_list<std::initializer_list<T>> init)
        : val(std::move(init)) {
        ASSERT_GT(n = val.size(), 0,
                  "matrix initializer must have positive number of rows.");
        for (std::size_t i = 0; i < n; i++) {
            if (i == 0) {
                ASSERT_GT(
                    m = val[0].size(), 0,
                    "matrix initializer must have positive number of cols.");
            }
            ASSERT_EQ(m, val[i].size(),
                      "matrix initializer has incompatible size: the number "
                      "of cols differs row by row.");
        }
    }

    bool operator==(mat const &other) const {
        for (std::size_t i = 0; i < n; i++) {
            for (std::size_t j = 0; j < m; j++) {
                if (val[i][j] != other.val[i][j]) return false;
            }
        }
        return true;
    }
    bool operator!=(mat const &other) const { return !(*this == other); }

    mat operator-() const {
        mat result = *this;
        for (std::size_t i = 0; i < n; i++) {
            for (std::size_t j = 0; j < m; j++) {
                result[i][j] = -result[i][j];
            }
        }
        return result;
    }
    mat &operator+=(mat const &other) {
        ASSERT_EQ(n, other.n,
                  "these matrices have incompatible size with +=.");
        ASSERT_EQ(m, other.m,
                  "these matrices have incompatible size with +=.");

        for (std::size_t i = 0; i < n; i++) {
            for (std::size_t j = 0; j < m; j++) {
                val[i][j] += other.val[i][j];
            }
        }
    }
    mat &operator-=(mat const &other) {
        ASSERT_EQ(n, other.n,
                  "these matrices have incompatible size with -=.");
        ASSERT_EQ(m, other.m,
                  "these matrices have incompatible size with -=.");

        for (std::size_t i = 0; i < n; i++) {
            for (std::size_t j = 0; j < m; j++) {
                val[i][j] -= other.val[i][j];
            }
        }
    }

    mat removed(std::size_t row, std::size_t col) const {
        ASSERT_GT(n, 1,
                  "more than or equal to 2 rows are needed to remove row.");
        ASSERT_GT(m, 1,
                  "more than or equal to 2 cols are needed to remove row.");
        mat result(n - 1, m - 1);
        for (std::size_t i = 0; i < n; i++) {
            if (i == row) continue;
            for (std::size_t j = 0; j < n; j++) {
                if (j == col) continue;
                std::size_t ni = i > row ? i - 1 : i;
                std::size_t nj = j > col ? j - 1 : j;

                result.val[ni][nj] = val[ni][nj];
            }
        }
        return result;
    }

    T det() const {
        ASSERT_EQ(n, m, "cannot calculate determinant of non-square matrix.")
        if (n == 1) return val[n][m];
        if (n == 2) return val[0][0] * val[1][1] - val[0][1] * val[1][0];
        T value{};
        for (std::size_t i = 0; i < n; i++) {
            value += removed(i, 0).det() * val[i][0] * (i % 2 == 0 ? 1 : -1);
        }
        return value;
    }
};

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
    ASSERT_EQ(n, other.n, "these matrices have incompatible size with *.");

    mat<T> result(n, other.m);
    for (std::size_t i = 0; i < n; i++) {
        for (std::size_t j = 0; j < other.m; j++) {
            for (std::size_t k = 0; k < m; k++)
                result[i][j] += val[i][k] * other.val[k][j];
        }
    }
    return result;
}
} // namespace pcl
#endif /* MAT_HPP */
