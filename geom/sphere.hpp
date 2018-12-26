#pragma once

#include "../prelude.hpp"

namespace pcl {

template <int DIM>
class sphere {
  private:
    crd<DIM> pos_;
    dbl rad_;

  public:
    sphere(crd<DIM> const &pos, dbl rad)
        : pos_(pos)
        , rad_(rad) {
    }

    crd<DIM> const &pos() const {
        return pos_;
    }
    dbl const &rad() const {
        return rad_;
    }
};

template <int DIM>
std::ostream &operator<<(std::ostream &os, sphere<DIM> const &sph) {
    os << "sphere { pos: " << sph.pos() << ", rad: " << sph.rad() << " }";
    return os;
}

} // namespace pcl
