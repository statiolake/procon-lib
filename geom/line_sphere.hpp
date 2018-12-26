#pragma once

#include "../prelude.hpp"

#include "../struct/vec.hpp"
#include "line.hpp"
#include "sphere.hpp"

namespace pcl {

template <int DIM>
bool have_itsc(segment<DIM> const &seg, sphere<DIM> const &sph,
               bool inclusive) {
    if (static_cast<line<DIM> const &>(seg).has(sph.pos())) {
        // the pos of sphere is on the same line with segment.
        // if pos is on the segment, if either beg or end is out of
        // sphere, then they have intersection.
        if (seg.has(sph.pos())) {
            dbl d = std::max(dist(sph.pos(), seg.beg()),
                             dist(sph.pos(), seg.end()));
            return inclusive ? d >= sph.rad() : d > sph.rad();
        } else {
            // now segment's inclusive are the same direction from the pos
            // of sphere. so, dist from beg or from end is smaller than
            // rad, the segment pierce the sphere.
            dbl d = std::min(dist(sph.pos(), seg.beg()),
                             dist(sph.pos(), seg.end()));
            return inclusive ? d <= sph.rad() : d < sph.rad();
        }
    } else {
        auto vec_normal = seg.normal_from(sph.pos());
        if (vec_normal.len() > sph.rad()) return false;

        segment<DIM> seg_normal(sph.pos(), sph.pos() + vec_normal * 2);
        bool res = have_itsc(seg, seg_normal, inclusive);
        return res;
    }
}

template <int DIM>
bool have_itsc(sphere<DIM> const &seg, segment<DIM> const &sph,
               bool inclusive) {
    return have_itsc(sph, seg, inclusive);
}
} // namespace pcl
