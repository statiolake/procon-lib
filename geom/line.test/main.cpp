/// verified with: aoj:2641, aoj:2003

#include "prelude.hpp"

#include "geom/line.hpp"
#include "geom/line_sphere.hpp"
#include "geom/sphere.hpp"

#include <bits/stdc++.h>

using namespace std;
using namespace pcl;

namespace pcl {
ostream &operator<<(ostream &os, pair<bool, coord<2>> const &v) {
    os << "(" << v.first << "," << v.second << ")";
    return os;
}
} // namespace pcl

void aoj2003() {
    using entrance = pair<bool, coord<2>>;
    int m;
    cin >> m;
    for (int q = 0; q < m; q++) {
        coord<2> A, B;
        cin >> A >> B;
        segment<2> new_road(A, B);

        // pair<high, intersect>
        vector<entrance> ents;

        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            coord<2> s, t;
            int o, l;
            cin >> s >> t >> o >> l;
            segment<2> road(s, t);
            if (!have_intersection(new_road, road, false)) continue;
            ents.push_back(make_pair(o == 1 ? l == 1 : l == 0, intersection(new_road, road, false)));
        }

        for (auto const &ent : ents) {
            line<2> const target(new_road.start(), ent.second);
            assert(static_cast<line<2> const &>(new_road) == target);
        }

        auto nearer = [&](entrance const &a, entrance const &b) { return distance(a.second, new_road.start()) < distance(b.second, new_road.start()); };

        sort(ents.begin(), ents.end(), nearer);

        auto same_height_p = [&](entrance const &a, entrance const &b) { return a.first == b.first; };

        auto numof_ents = static_cast<int>(distance(ents.begin(), unique(ents.begin(), ents.end(), same_height_p)));
        cout << max(0, numof_ents - 1) << endl;
    }
}

void aoj2641() {
    int N, Q;
    cin >> N >> Q;
    vector<pair<sphere<3>, ll>> obs;
    for (int i = 0; i < N; i++) {
        coord<3> c;
        dbl r;
        ll l;
        cin >> c >> r >> l;
        obs.push_back(make_pair(sphere<3>(c, r), l));
    }

    for (int i = 0; i < Q; i++) {
        coord<3> s, e;
        cin >> s >> e;
        segment<3> seg(s, e);

        ll mp = 0;
        for (int i = 0; i < N; i++) {
            if (have_intersection(seg, obs[i].first, true)) mp += obs[i].second;
        }
        cout << mp << endl;
    }
}

int main() {
    // aoj2003();
    // aoj2641();
    int n;
    cin >> n;
    if (n == 2003) {
        aoj2003();
    } else if (n == 2641) {
        aoj2641();
    } else {
        assert(false);
    }
}
