#ifndef STREAM_HPP_L5EPV267
#define STREAM_HPP_L5EPV267
#include <iostream>

namespace pcl { namespace utility {
    struct empty_stream_buf : public std::streambuf {
        char dummybuf[8];

      protected:
        virtual int overflow(int c) {
            setp(dummybuf, dummybuf + sizeof(dummybuf));
            return c == traits_type::eof() ? '\0' : c;
        }
    };

    struct empty_stream : private empty_stream_buf, public std::ostream {
      public:
        empty_stream()
            : std::ostream(this) {}
        empty_stream_buf const *rdbuf() const { return this; }
    };
}} // namespace pcl::utility

#endif /* end of include guard: STREAM_HPP_L5EPV267 */
