#pragma once

#include "../prelude.hpp"

namespace pcl {

template <int DIM>
class sphere {
  private:
    coord<DIM> center_;
    dbl radius_;

  public:
    sphere(coord<DIM> const &center, dbl radius)
        : center_(center)
        , radius_(radius) {}

    coord<DIM> const &center() const { return center_; }
    dbl const &radius() const { return radius_; }
};

template <int DIM>
std::ostream &operator<<(std::ostream &os, sphere<DIM> const &sph) {
    os << "sphere { center: " << sph.center() << ", radius: " << sph.radius() << " }";
    return os;
}

} // namespace pcl
