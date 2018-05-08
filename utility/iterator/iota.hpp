#ifndef IOTA_HPP_GQIXM5SA
#define IOTA_HPP_GQIXM5SA

#include <cassert>

namespace pcl { namespace utility { namespace iterator {

    template <typename T>
    class iota {
        private:
            T m_beg, m_end, m_step;
        public:
            class iota_iterator {
                private:
                    T m_value, m_step;
                public:
                    iota_iterator(T value, T step) : m_value(value), m_step(step) {}
                    bool operator!=(iota_iterator const &other) {
                        return m_value != other.m_value;
                    }
                    bool operator==(iota_iterator const &other) {
                        return m_value == other.m_value;
                    }
                    operator T() { return m_value; }
                    T operator*() { return m_value; }
                    iota_iterator &operator++() {
                        m_value += m_step;
                        return *this;
                    }
                    iota_iterator operator++(int) {
                        iota_iterator orig = *this;
                        m_value += m_step;
                        return orig;
                    }
                    iota_iterator &operator--() {
                        m_value -= m_step;
                        return *this;
                    }
                    iota_iterator operator--(int) {
                        iota_iterator orig = *this;
                        m_value -= m_step;
                        return orig;
                    }
            };

            iota(T beg, T end, T step) : m_beg(beg), m_end(end), m_step(step) {
                assert(m_step == 1 || m_step == -1);
            }
            iota_iterator begin() { return iota_iterator(m_beg, m_step); }
            iota_iterator end() { return iota_iterator(m_end, 0); }
    };

    template <typename T>
    iota<T> make_iota(T beg, T end) {
        return iota<T>(beg, end, 1);
    }

    template <typename T>
    iota<T> make_descending_iota(T beg, T end) {
        return iota<T>(beg, end, -1);
    }

}}}

#endif /* end of include guard: IOTA_HPP_GQIXM5SA */
