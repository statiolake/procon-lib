#pragma once

#include "prelude.hpp"

#include "graph/graph.hpp"

#include <queue>
#include <utility>

namespace pcl {

/**
 * @brief 有向非巡回グラフ (DAG) をトポロジカルソートする。
 * @param[in] dag DAG
 * @return トポロジカル順に並んだ頂点集合へのポインタ
 * @details DAG でないときは頂点集合へのポインタが nullptr となる。トポロジカ
 * ル順が複数通り考えられる場合は、辞書順で最小になるものとする。
 */
// FIXME: unique_ptr だとヒープ確保のコストがかかるので Option にしたい。完成
// が待たれる。
std::unique_ptr<std::vector<int>>
topological_sort(graph::list<int> const &dag) {
    int V = dag.size();

    // 入次数。 deg[i] := 頂点 i に入る辺の本数。
    std::vector<int> deg(V);
    for (int i = 0; i < V; i++)
        for (auto const &t : dag.adj_of(i)) deg[t.to]++;

    // 現在、入次数が 0 である頂点の集合
    std::priority_queue<int, std::vector<int>, std::greater<int>> que;
    // 最初は最初から入次数が 0 である頂点 (根みたいなもの) を追加しておく。
    for (int s = 0; s < V; s++)
        if (deg[s] == 0) que.push(s);

    std::vector<int> sorted;
    while (!que.empty()) {
        int c = que.top();
        que.pop();
        sorted.push_back(c);

        // 今追加した頂点をグラフから削除する。つまり、 (i) これ以降この頂点に
        // 到達できないようにして (ii) この頂点とつながっている辺を削除する。
        //
        // まず、 dag が本当に DAG である場合を考える。このときは、
        // (i) DAG には閉路がないから、今いるこの頂点に戻ってくる経路はどのみ
        // ち存在しないはず。ということは本当に頂点を取り除く必要はなく、何も
        // しなくてもこの頂点には到達できない。
        // (ii) 入次数 0 の頂点のはずなので、この頂点に向かってくる辺はない。
        // 従ってこの頂点から出ていく辺のみを削除すればよい。これも、どうせこ
        // の頂点を訪れることは二度とないのだから実際に削除する必要はなく、こ
        // の頂点から出ている辺の行き先の入次数情報をデクリメントしてやればよ
        // い。
        //
        // このようにすると実際にグラフを変更することなく効率よく操作を完了で
        // きる。
        //
        // 一方 dag でない場合にこの操作が停止するか、それを検出できるかを考え
        // る。仮にこの頂点に戻ってくる閉路がある場合でも、いずれ入り次数が負
        // になって自動で止まる (なぜなら入次数が 0 のときのみキューへ追加して
        // いるため) 。
        // といっても、実際に削除する必要はない。なぜなら DAG なので、今のこの
        // 頂点に戻ってくる経路はどのみち存在しない。これ以降どう探索してもこ
        // の頂点に戻ってくることはない。
        for (auto const &t : dag.adj_of(c))
            if (--deg[t.to] == 0) que.push(t.to);
    }

    // このとき dag は実は DAG ではなかったということ
    if (sorted.size() != dag.size()) return nullptr;

    return std::make_unique<std::vector<int>>(std::move(sorted));
}

} // namespace pcl
