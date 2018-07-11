#ifndef GEOM_HPP_BIAOH5YE
#define GEOM_HPP_BIAOH5YE

#include <iostream>

#include "../prelude.hpp"

#include "../struct/vec.hpp"
#include "mat.hpp"
namespace pcl {
class segment {
private:
  std::pair<double, double> range;

public:
  coord start;
  vec dir;

  segment(segment const &other)
      : range(other.range)
      , start(other.start)
      , dir(other.dir) {}

  segment(coord const &start, coord const &end)
      : range(0, (end - start).length())
      , start(start)
      , dir((end - start).normalized()) {}

  virtual bool is_line() const { return false; }
  virtual double length() const { return range.second - range.first; }
  virtual double range_begin() const { return range.first; }
  virtual double range_end() const { return range.second; }

  double distance_from(coord const &from) const {
    vec a = from - start;
    return cross(a, dir).length();
  }

  vec normal_from(coord const &from) const {
    ASSERT(eqdbl(dot(dir, dir), 1), "[normal_from] dir is not normalized!");
    double t = dot(from - start, dir);
    PD_LIB(std::cerr << "[normal_from] dir is " << dir << std::endl);
    PD_LIB(std::cerr << "[normal_from] t is " << t << std::endl);
    PD_LIB(std::cerr << "[normal_from] t*dir is " << t * dir << std::endl);
    auto normal = start + t * dir - from;
    ASSERT(eqdbl(dot(normal, dir), 0),
           "[normal_from] can't calculate normal!");
    return normal;
  }
};

class line : public segment {
public:
  line(line const &other)
      : segment(other.start, other.start + other.dir) {}
  line(coord const &start, coord const &end)
      : segment(start, end) {}

  virtual bool is_line() const override { return true; }
  virtual double length() const override { return DNF; }
  virtual double range_begin() const override { return -DNF; }
  virtual double range_end() const override { return DNF; }
};

class sphere {
public:
  coord center;
  double radius;

  sphere() {}
  sphere(coord const &center, double radius)
      : center(center)
      , radius(radius) {}
};

std::ostream &operator<<(std::ostream &os, segment const &seg) {
  os << "segment { start: " << seg.start << ", direction: " << seg.dir
     << ", length: " << seg.length() << " }";
  return os;
}

std::ostream &operator<<(std::ostream &os, line const &lin) {
  os << "line { start: " << lin.start << ", direction: " << lin.dir << " }";
  return os;
}

std::ostream &operator<<(std::ostream &os, sphere const &sph) {
  os << "sphere { center: " << sph.center << ", radius: " << sph.radius
     << " }";
  return os;
}

double distance(coord const &a, coord const &b) { return (a - b).length(); }

bool on_same_plane(segment const &lhs, segment const &rhs) {
  auto a = lhs.dir;
  auto b = rhs.start - lhs.start;
  auto c = rhs.start + rhs.dir - lhs.start;

  mat<double> coords = {
      {a.x, a.y, a.z},
      {b.x, b.y, b.z},
      {c.x, c.y, c.z},
  };
  return eqdbl(coords.det(), 0);
}

bool has_intersection(segment const &lhs, segment const &rhs) {
  if (!on_same_plane(lhs, rhs)) return false;
  if (is_parallel(lhs.dir, rhs.dir)) return false;

  auto check = [&](auto const &base, auto const &target) {
    if (target.is_line()) { return true; }
    PD_LIB(std::cerr << "[has_intersection] checking " << base << " and "
                     << target << std::endl);
    ASSERT(in_range(-DNF, {target.range_begin(), target.range_end()}, DNF),
           "internal error: there must not be half-line in current "
           "implementation.");
    auto rela = target.start - base.start;
    auto relb = target.length() * target.dir + rela;
    auto c1   = cross(base.dir, rela);
    auto c2   = cross(base.dir, relb);

    ASSERT(is_parallel(c1, c2),
           "cross product not returned parallel vectors.");

    for (std::size_t i = 0; i < 3; i++) {
      double prod = c1[i] * c2[i];
      if (!ledbl(prod, 0)) return false;
    }
    return true;
  };

  if (!check(lhs, rhs)) return false;
  if (!check(rhs, lhs)) return false;
  return true;
}

bool has_intersection(segment const &lhs, sphere const &rhs) {
  auto vec_normal = lhs.normal_from(rhs.center);
  PD_LIB(std::cerr << "[has_intersection] vec_normal: " << vec_normal
                   << " (length: " << vec_normal.length() << ")"
                   << std::endl);
  if (eqdbl(vec_normal.length(), 0)) {
    PD_LIB(std::cerr << "[has_intersection] vec_normal is 0; maybe the "
                        "center of sphere is on the same line."
                     << std::endl);
    auto center_start = lhs.start - rhs.center;
    auto center_end   = lhs.start + lhs.dir * lhs.length() - rhs.center;
    PD_LIB(std::cerr << "[has_intersection] center_start: " << center_start
                     << ", center_end: " << center_end
                     << ", radius: " << rhs.radius << std::endl);
    return is_parallel_vecs_same_direction(center_start, center_end);
  } else if (!ledbl(vec_normal.length(), rhs.radius)) {
    PD_LIB(std::cerr << "[has_intersection] length of vec_normal is larger "
                        "than radius. they can't have intersection."
                     << std::endl);
    return false;
  } else {
    PD_LIB(std::cerr << "[has_intersection] vec_normal: " << vec_normal
                     << std::endl);
    // vec_normal *= 2;
    segment seg_normal(rhs.center, rhs.center + vec_normal);
    return has_intersection(lhs, seg_normal);
  }
}

bool has_intersection(sphere const &lhs, segment const &rhs) {
  return has_intersection(rhs, lhs);
}

coord intersection(segment const &lhs, segment const &rhs) {
  ASSERT(has_intersection(lhs, rhs), "these segments have no intersection.");
  coord result;
  segment const *base   = &lhs;
  segment const *target = &rhs;

  if (base->is_line() && target->is_line()) {
    ASSERT(false, "line-line intersection is not yet implemented.");
    return {0, 0, 0}; // unreachable, but silent warning
  } else {
    if (target->is_line()) {
      ASSERT(!base->is_line(), "base must not be line here.");
      std::swap(base, target);
    }
    double d1 = base->distance_from(target->start);
    double d2 =
        base->distance_from(target->start + target->dir * target->length());
    double t = d1 / (d1 + d2);
    return target->start + t * target->dir;
  }
}

} // namespace pcl

#endif /* end of include guard: GEOM_HPP_BIAOH5YE */
