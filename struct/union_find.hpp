/**
 * @file struct/union_find.hpp
 * @brief Union-Find - 集合の要素を高速にグルーピングする
 */
#pragma once

#include "../prelude.hpp"

#include <cassert>
#include <vector>

namespace pcl {

/**
 * @brief Union-Find
 * @details 集合を高速にグルーピングする。
 * - unite: 二つの要素が属する集合同士を結合して大きいグループにする。
 * - find: ある要素が属しているグループの番号を得る。
 */
class union_find {
  private:
    std::vector<int> par_rank_; // 正: 親ノード, 負: (rank + 1)
    std::size_t size_;

  public:
    /**
     * @brief コンストラクタ
     * @details n 要素の集合を用意する。最初、各要素は全てバラバラである。
     */
    union_find(int n)
        : par_rank_(n, -1)
        , size_(n) {
    }

    /**
     * @brief 二つの要素が属するグループを結合する。
     * @param[in] a 要素のインデックス
     * @param[in] b 要素のインデックス
     * @details a が属するグループと b が属するグループを結合する。もともと同
     * じグループに属していれば何もしない。
     * 経路圧縮と rank の両方を実装しているため、計算量はアッカーマン関数の逆
     * 関数を α として O(α(n)) 。
     */
    void unite(int a, int b) {
        int pa = find(a), pb = find(b);
        if (pa == pb) return;
        --size_;

        int np, nc;
        if (par_rank_[pa] == par_rank_[pb]) {
            np = pa;
            nc = pb;
            par_rank_[np]--;
        } else if (par_rank_[pa] > par_rank_[pb]) {
            np = pb;
            nc = pa;
        } else {
            np = pa;
            nc = pb;
        }

        par_rank_[nc] = np;
    }

    /**
     * @brief ある要素の属するグループのルートのインデックスを求める。
     * @param[in] a 要素のインデックス
     * @details a が属するグループのルートのインデックスはそのままグループ番号
     * のように利用することができる。ただし連番にはなっていないので注意。
     * 経路圧縮で書き換えを行うため、 `find()` だけでも `const` では使うことが
     * できない。経路圧縮と rank の両方を実装しているため、計算量はアッカーマ
     * ン関数の逆関数を α として O(α(n)) 。
     */
    int find(int a) {
        if (par_rank_[a] < 0) return a;
        return par_rank_[a] = find(par_rank_[a]);
    }

    /**
     * @brief 現在のグループの個数を返す。
     * @details 木の要素の個数 **ではない** ので注意が必要。
     */
    std::size_t size() const {
        return size_;
    }
};

} // namespace pcl
