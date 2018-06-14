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
} // namespace pcl

#endif /* BCC09B9B_0133_EE7C_AAF9_25F0BA678968 */
