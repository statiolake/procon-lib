#ifndef ITER_SAFE_ITER_KZAA4F7K
#define ITER_SAFE_ITER_KZAA4F7K

#if __cplusplus >= 201703L

#include <utility>

namespace pcl {

template <typename T>
class safe_iota {
public:
  class safe_iota_iterator;

private:
  T m_beg, m_end, m_step, m_curr;

public:
  class safe_iota_end_iterator {
  private:
    T m_value;

  public:
    friend bool safe_iota_iterator::
    operator!=(safe_iota_end_iterator const &);
    friend bool safe_iota_iterator::
    operator==(safe_iota_end_iterator const &);
    safe_iota_end_iterator(T value)
        : m_value(value) {}

    operator T() { return m_value; }
    T operator*() { return m_value; }
  };

  class safe_iota_iterator {
  private:
    T m_value, m_step;

  public:
    safe_iota_iterator(T value, T step)
        : m_value(value)
        , m_step(step) {}

    operator T() { return m_value; }
    T operator*() { return m_value; }

    safe_iota_iterator &operator++() {
      m_value += m_step;
      return *this;
    }

    safe_iota_iterator operator++(int) {
      safe_iota_iterator orig(*this);
      m_value += m_step;
      return orig;
    }

    safe_iota_iterator &operator--() {
      m_value -= m_step;
      return *this;
    }

    safe_iota_iterator operator--(int) {
      safe_iota_iterator orig(*this);
      m_value -= m_step;
      return orig;
    }

    bool operator!=(safe_iota_iterator const &other) {
      return m_value != other.m_value;
    }

    bool operator==(safe_iota_iterator const &other) {
      return m_value == other.m_value;
    }

    bool operator!=(safe_iota_end_iterator const &other) {
      return m_step > 0 ? m_value < other.m_value : m_value > other.m_value;
    }

    bool operator==(safe_iota_end_iterator const &other) {
      return !(*this != other);
    }
  };

  safe_iota(T beg, T end, T step)
      : m_beg(beg)
      , m_end(end)
      , m_step(step)
      , m_curr(beg) {}

  safe_iota_iterator begin() { return safe_iota_iterator(m_beg, m_step); }

  safe_iota_end_iterator end() { return safe_iota_end_iterator(m_end); }
};

template <typename T>
safe_iota<T> make_safe_iota(T beg, T end, T step = 1) {
  return safe_iota<T>(beg, end, step);
}
} // namespace pcl

#endif

#endif /* end of include guard: ITER_SAFE_ITER_KZAA4F7K */
