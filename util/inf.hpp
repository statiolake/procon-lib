#ifndef INF_HPP
#define INF_HPP

#include <type_traits>

struct _inf {
  int dir;
  _inf operator-() const { return _inf{dir * -1}; }
};

constexpr _inf INF{1};

template <typename Number,
          typename std::enable_if<!std::is_same<Number, _inf>::value,
                                  std::nullptr_t>::type = nullptr>
bool operator<(Number const &, _inf const &inf) {
  return inf.dir == 1;
}

template <typename Number,
          typename std::enable_if<!std::is_same<Number, _inf>::value,
                                  std::nullptr_t>::type = nullptr>
bool operator>(Number const &, _inf const &inf) {
  return inf.dir == -1;
}

template <typename Number,
          typename std::enable_if<!std::is_same<Number, _inf>::value,
                                  std::nullptr_t>::type = nullptr>
bool operator<=(Number const &a, _inf const &inf) {
  return a < inf;
}

template <typename Number,
          typename std::enable_if<!std::is_same<Number, _inf>::value,
                                  std::nullptr_t>::type = nullptr>
bool operator>=(Number const &a, _inf const &inf) {
  return a > inf;
}

template <typename Number,
          typename std::enable_if<!std::is_same<Number, _inf>::value,
                                  std::nullptr_t>::type = nullptr>
bool operator<(_inf const &inf, Number const &) {
  return inf.dir == -1;
}

template <typename Number,
          typename std::enable_if<!std::is_same<Number, _inf>::value,
                                  std::nullptr_t>::type = nullptr>
bool operator>(_inf const &inf, Number const &) {
  return inf.dir == 1;
}

template <typename Number,
          typename std::enable_if<!std::is_same<Number, _inf>::value,
                                  std::nullptr_t>::type = nullptr>
bool operator<=(_inf const &inf, Number const &a) {
  return inf < a;
}

template <typename Number,
          typename std::enable_if<!std::is_same<Number, _inf>::value,
                                  std::nullptr_t>::type = nullptr>
bool operator>=(_inf const &inf, Number const &a) {
  return inf > a;
}

template <typename Number,
          typename std::enable_if<!std::is_same<Number, _inf>::value,
                                  std::nullptr_t>::type = nullptr>
bool operator==(Number const &, _inf const &) {
  return false;
}

template <typename Number,
          typename std::enable_if<!std::is_same<Number, _inf>::value,
                                  std::nullptr_t>::type = nullptr>
bool operator!=(Number const &, _inf const &) {
  return true;
}

bool operator==(_inf const &a, _inf const &b) { return a.dir == b.dir; }
bool operator!=(_inf const &a, _inf const &b) { return a.dir != b.dir; }

template <typename Number,
          typename std::enable_if<!std::is_same<Number, _inf>::value,
                                  std::nullptr_t>::type = nullptr>

#define DEFINE_OP(op, ty1, v1, ty2, v2)                                 \
  template <typename Number,                                            \
            typename std::enable_if<!std::is_same<Number, _inf>::value, \
                                    std::nullptr_t>::type = nullptr>    \
  _inf operator op(ty1 const &v1, ty2 const &v2) {                      \
    return inf;                                                         \
  }

#define DEFINE_OP_BOTH(op)            \
  DEFINE_OP(op, Number, a, _inf, inf) \
  DEFINE_OP(op, _inf, inf, Number, a)

DEFINE_OP_BOTH(+)
DEFINE_OP_BOTH(-) DEFINE_OP_BOTH(*) DEFINE_OP_BOTH(/)

#undef DEFINE_OP
#undef DEFINE_OP_BOTH

#endif /* INF_HPP */
