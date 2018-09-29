#ifndef LAMBDA_HPP_PRY0TKQ7
#define LAMBDA_HPP_PRY0TKQ7

#include "../../prelude.hpp"

#include <functional>
#include <iterator>

namespace pcl {
template <typename Input, typename Output>
class lambda_iterator {
private:
  using lambda_type = std::function<Output(Input)>;
  Input range_begin, range_end;
  lambda_type func;

public:
  lambda_iterator(Input const &begin, Input const &end, lambda_type f)
      : range_begin(begin)
      , range_end(end)
      , func(f) {}
  lambda_iterator(lambda_iterator &&other)
      : range_begin(std::move(other.begin))
      , range_end(std::move(other.end))
      , func(std::move(other.func)) {}

  class iterator {
  private:
    Input current;
    lambda_type func;

  public:
    using difference_type   = Input;
    using value_type        = Output;
    using pointer           = value_type *;
    using reference         = value_type &;
    using iterator_category = std::random_access_iterator_tag;

    iterator(Input init, lambda_type f)
        : current(init)
        , func(f) {}
    iterator(iterator const &other)
        : current(other.current)
        , func(other.func) {}

    iterator &operator=(iterator const &other) {
      current = other.current;
      func    = other.func;
      return *this;
    }

    Input current_arg() const { return current; }

    // iterator
    Output operator*() { return func(current); }

    iterator &operator++() { // pre
      ++current;
      return *this;
    }

    iterator operator++(int) { // post
      auto cp = *this;
      current++;
      return cp;
    }

    iterator &operator--() { // pre
      --current;
      return *this;
    }

    iterator operator--(int) { // post
      auto cp = *this;
      current--;
      return cp;
    }

    iterator operator+(Input x) const {
      iterator it(*this);
      it.current += x;
      return it;
    }

    iterator operator-(Input x) const {
      iterator it(*this);
      it.current -= x;
      return it;
    }

    Input operator-(iterator const &other) const {
      return current - other.current;
    }

    iterator &operator+=(Input x) {
      current += x;
      return *this;
    }

    iterator &operator-=(Input x) {
      current -= x;
      return *this;
    }

    bool operator==(iterator const &other) const {
      return current == other.current;
    }

    bool operator!=(iterator const &other) const {
      return current != other.current;
    }

    bool operator<(iterator const &other) const {
      return current < other.current;
    }

    bool operator>(iterator const &other) const {
      return current > other.current;
    }

    bool operator<=(iterator const &other) const {
      return current <= other.current;
    }

    bool operator>=(iterator const &other) const {
      return current >= other.current;
    }

    Output operator[](Input arg) { return func(arg); }
  };

  iterator begin() const { return iterator(range_begin, func); }
  iterator end() const { return iterator(range_end, func); }
};
}; // namespace pcl

#endif /* end of include guard: LAMBDA_HPP_PRY0TKQ7 */
