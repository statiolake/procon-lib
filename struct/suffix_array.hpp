/**
 * @file struct/suffix_array.hpp
 * @brief 接尾辞配列による文字列検索
 */
#pragma once

#include "../prelude.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

namespace pcl {

/// 接尾辞配列と、それによる文字列検索。
class suffix_array {
  private:
    /// size_ は s_.size() + 1 になる。空文字列 "" も接尾辞なので。
    int const size_;

    /// 元の文字列
    std::string const s_;

    /// 接尾辞配列
    /// 辞書順で i 番目の接尾辞は a_[i] 文字目から始まる。
    std::vector<int> a_;

  public:
    /**
     * @brief 与えられた文字列の接尾辞配列を構築する。
     * @details 接尾辞を全てソートする。ソートは、接尾辞の先頭 1文字だけをソー
     * トして、それを使って先頭 2文字をソートして、それを使って 4 文字をソー
     * トして、 ...を繰り返す。よって計算量は O(N(logN)^2) 。ナイーブにクイッ
     * クソートする方法だと O(N^2logN) なので高速化されている。
     */
    suffix_array(std::string const &s)
        : size_(s.size() + 1)
        , s_(s)
        , a_(size_) {
        // i 文字目から始まる接尾辞は辞書順で r[i] に位置する (最初から完成形
        // の順位になっているわけではなく、それまでにソートされた範囲での順位
        // になる。つまり、途中は接尾辞の k 文字目までソートされている状態の順
        // 位、その次に 2k 文字目までソートされている状態の順位、と遷移してい
        // く) 。
        std::vector<int> rank(size_);

        // 最初、1 文字だけソートされているときの順位は文字コードをそのまま使
        // えばよい (ASCII を前提とするのでポータブルではないが、まあ...) 。こ
        // れだと順位が飛ぶことがあるが、それは別に大した問題ではない。同じ文
        // 字が同じ順位であればよい。
        for (int i = 0; i < size_; i++) rank[i] = s[i];

        // 最初はソートされていない状態で a_ を作る。
        for (int i = 0; i < size_; i++) a_[i] = i;

        // k 文字目までソートされているという前提で 2k 文字目までソートする。
        // ここでのソートされている、とは、 `rank` が正しい順序を示しているこ
        // とを言うので、最初 `a_` は初期化されたてでソートされていないが問題
        // はない。実はソート処理自体には `a_` は使わず、 `rank` のみに依存す
        // る。
        for (int k = 1; k < size_; k *= 2) {
            auto cmp = [&](int ia, int ib) {
                // 2k 文字の長さの文字列を二つに分割する。
                // s_[ia..ia+k] + s_[ia+k..ia+2k]
                // その上で、「前半の順位」と「後半の順位」を使うと全体の順位
                // が決定できる。要するに
                // `pair(rank[ia], rank[ia+k]) < pair(rank[ib], rank[ib+k])`
                // であるが、 ia+k などが範囲外になる場合を特別扱いする必要が
                // ある。
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

            // 今回のソート結果を元に、次の rank を計算する。
            // rank を書き換えるのは都合が悪いので一旦 tmp なる別の配列に計算
            // して、後で rank へ移す。
            std::vector<int> tmp(size_);

            // 次の順位は基本的には rank[a_[i]] = i なのだが、それは接尾辞配列
            // に同じものが含まれなかった場合である。同じものの順位が同じにな
            // らないと、同じなのに不当に順位がついてしまって動かない。特に先
            // のソートアルゴリズムでは a_ を一切見ないので、 rank が異なれば
            // 違う文字列とみなされてしまう。完成する接尾辞配列では同じ文字列
            // は含まれない (そもそも全部長さが異なるため) が、 k 文字目までソ
            // ートした途中段階では同じ文字列となることが大いにありえる。
            // というわけで一般には rank[a_[i]] != i なのだが、rank[a_[0]] = 0
            // だけは自明。これは次の for 文で「一つ前の順位の...」が必要だか
            // ら、 0 だけ特別扱いしておくということ。
            tmp[a_[0]] = 0;

            // i は i 番目の文字列、 j は現在の順位。
            // 基本的に for (i = 1; i < size_; i++) rank[a_[i]] = i; を、同じ
            // ものが同じ順位になるように対応させたものである。そのためループ
            // カウンタとは別に順位のカウンタを持ち、一つ前の順位の文字列と異
            // なる文字列のときだけインクリメントすることにする。
            for (int i = 1, j = 0; i < size_; i++) {
                // 先の比較関数を再利用する。もし i 位の文字列と i-1 位の文字
                // 列が全く同一なら、 (少し略記するけど)  cmp(i, i-1) と
                // cmp(i-1, i) はどちらも false を返すはず。
                if (cmp(a_[i - 1], a_[i]) || cmp(a_[i], a_[i - 1])) j++;
                tmp[a_[i]] = j;
            }

            rank = std::move(tmp);
        }
    }

    /**
     * @brief 作った接尾辞配列を用いて検索を行う関数。
     * @param[in] p 検索したいパターン文字列。
     * @return 見つかったら true を返す。
     */
    bool matches(std::string const &p) {
        // 接尾辞配列は全ての場所からスタートする接尾辞の集合なので、もし p が
        // s_ に含まれているなら、 s_ のある接尾辞の先頭 p.size() 文字が p と
        // 一致することになる。接尾辞配列は辞書順にならんでいるので、二分探索
        // を用いて高速に存在するかどうかを確かめられる。

        auto cmp = [&](int a, std::string const &b) {
            // substr() を使って実際に部分文字列を生成してしまえば普通に < が
            // 使えるが、文字列生成のコストがあるので compare() を使う。
            // string_view が使えれば少し直感的に扱えるのに。
            return s_.compare(a, b.size(), b) < 0;
        };

        // 存在確認には本当は binary_search() が使いたいのだがだが、今回は比較
        // 関数が特殊で比較する二者の型が異なっている (int と string) 。そのせ
        // いで binary_search() が同一性の確認に要求する !(a<b) && !(b<a) を実
        // 行できない。
        auto it = std::lower_bound(a_.begin(), a_.end(), p, cmp);
        if (it == a_.end()) return false;

        // 本当にマッチしたかどうかを確認する。というのは、今用いたのはあくま
        // で lower_bound()なので、辞書順で p 以上の接尾辞を得たに過ぎない。本
        // 当に接尾辞の先頭 p.size() 文字が p と一致しているか確認する必要があ
        // る。
        return s_.compare(*it, p.size(), p) == 0;
    }
};

} // namespace pcl
