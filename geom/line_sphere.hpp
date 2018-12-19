#pragma once

#include "../prelude.hpp"

#include "../struct/vec.hpp"
#include "line.hpp"
#include "sphere.hpp"

namespace pcl {

template <int DIM>
bool have_intersection(segment<DIM> const &seg, sphere<DIM> const &sph,
                       bool endpoint) {
    if (static_cast<line<DIM> const &>(seg).has(sph.center())) {
        // the center of sphere is on the same line with segment.
        // if center is on the segment, if either start or end is out of
        // sphere, then they have intersection.
        if (seg.has(sph.center())) {
            dbl dist = std::max(distance(sph.center(), seg.start()),
                                distance(sph.center(), seg.end()));
            return endpoint ? dist >= sph.radius() : dist > sph.radius();
        } else {
            // now segment's endpoints are the same direction from the center
            // of sphere. so, distance from start or from end is smaller than
            // radius, the segment pierce the sphere.
            dbl dist = std::min(distance(sph.center(), seg.start()),
                                distance(sph.center(), seg.end()));
            return endpoint ? dist <= sph.radius() : dist < sph.radius();
        }
    } else {
        auto vec_normal = seg.normal_from(sph.center());
        if (vec_normal.length() > sph.radius()) return false;

        segment<DIM> seg_normal(sph.center(), sph.center() + vec_normal * 2);
        bool res = have_intersection(seg, seg_normal, endpoint);
        return res;
    }
}

template <int DIM>
bool have_intersection(sphere<DIM> const &seg, segment<DIM> const &sph,
                       bool endpoint) {
    return have_intersection(sph, seg, endpoint);
}
} // namespace pcl
