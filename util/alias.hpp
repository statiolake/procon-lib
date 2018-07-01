#ifndef BCC09B9B_0133_EE7C_AAF9_25F0BA678968
#define BCC09B9B_0133_EE7C_AAF9_25F0BA678968

#include <algorithm>

namespace pcl {
template <typename T>
void updmax(T &a, T const &b) {
    a = std::max(a, b);
}

template <typename T>
void updmin(T &a, T const &b) {
    a = std::min(a, b);
}

template <typename T>
bool in_range(T const &begin, T const &mid, T const &end) {
    return begin <= mid && mid < end;
}
template <typename T>
bool in_range(T const &begin, std::initializer_list<T> list, T const &end) {
    auto p = std::minmax_element(list.begin(), list.end());
    return begin <= *p.first && *p.second < end;
}
} // namespace pcl

#endif /* BCC09B9B_0133_EE7C_AAF9_25F0BA678968 */
