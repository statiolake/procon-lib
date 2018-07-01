#ifndef GEOM_HPP
#define GEOM_HPP

#include "math/dbl.hpp"
#include "math/mat.hpp"
#include "struct/vec.hpp"
namespace pcl {
template <size_t D>
using vecdbl = vec<dbl, D>;

using vec2d = vecdbl<2>;
using vec3d = vecdbl<3>;

template <size_t D>
using coorddbl = vecdbl<D>;

using coord2d = coorddbl<2>;
using coord3d = coorddbl<3>;

template <size_t D>
class segment {
  private:
    std::pair<dbl, dbl> range;

  public:
    coorddbl<D> start;
    vecdbl<D> dir;

    segment(segment const &other)
        : range(other.range)
        , start(other.start)
        , dir(other.dir) {}

    segment(coorddbl<D> const &start, coorddbl<D> const &end)
        : range(0, (end - start).length())
        , start(start)
        , dir((end - start).normalized()) {}

    virtual bool is_line() const { return false; }
    virtual dbl length() const { return range.second - range.first; }
    virtual dbl range_begin() const { return range.first; }
    virtual dbl range_end() const { return range.second; }

    dbl distance_from(coorddbl<D> const &from) {
        vecdbl<D> a = from - start;
        return a.cross(dir);
    }

    vecdbl<D> normal_from(coorddbl<D> const &from) {
        dbl t = (from - start).dot(dir);
        return start + t * dir - from;
    }

    bool has_intersection(segment const &other) {
        if (!on_same_plane(other)) return false;
        if (dir.is_pararell(other.dir)) return false;

        auto check = [&](auto const &base, auto const &target) {
            auto rbegin = target.range_begin();
            auto rend   = target.range_end();
            if (target.is_line()) { return true; }
            ASSERT(in_range(-DNF, {rbegin, rend}, DNF),
                   "internal error: there must not be half-line in current "
                   "implementation.");
            auto rela = target.start - start;
            auto relb = length() * target.dir + rela;
            auto x1   = base.dir.cross(rela)[0];
            auto x2   = base.dir.cross(relb)[0];
            return x1 * x2 < 0;
        };

        if (!check(*this, other)) return false;
        if (!check(other, *this)) return false;
        return true;
    }

    auto on_same_plane(segment const &other)
        -> std::enable_if<D == 2, bool>::type {
        return true;
    }

    auto on_same_plane(segment const &other)
        -> std::enable_if<D == 3, bool>::type {
        auto a = dir;
        auto b = other.start - start;
        auto c = other.start + other.dir - start;

        mat coords = {
            {a.x, a.y, a.z},
            {b.x, b.y, b.z},
            {c.x, c.y, c.z},
        };
        return coords.det() == 0;
    }

    coorddbl<D> intersection(segment const &other) const {
        ASSERT(has_intersection(other),
               "these segments have no intersection.");
        coorddbl<D> result;
        segment const *base   = this;
        segment const *target = &other;
        if (base->is_line() && other->is_line()) {

        } else {
            if (other->is_line()) {
                ASSERT(!base->is_line(), "base must not be line here.");
                std::swap(base, other);
            }
            dbl d1 = base->distance_from(target.start);
            dbl d2 = base->distance_from(target.start +
                                         target.dir * target.length());
            dbl t  = d1 / (d1 + d2);
            return target->start + t * target->dir;
        }
    }
};

template <size_t D>
struct line : public segment {
    line(line const &other)
        : segment(other.start, other.start + other.dir) {}
    line(coorddbl<D> const &start, coorddbl<D> const &end)
        : segment(start, end) {}

    virtual bool is_line() const override { return true; }
    virtual dbl length() const override { return DNF; }
    virtual dbl range_begin() const override { return -DNF; }
    virtual dbl range_end() const override { return DNF; }
};

} // namespace pcl
#endif /* GEOM_HPP */
