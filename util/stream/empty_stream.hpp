/**
 * @file stream/empty_stream.hpp
 * @brief 空の出力ストリーム
 */
#pragma once

#include "../../prelude.hpp"

#include <iostream>

namespace pcl {

/// @brief 空の出力ストリームバッファ。内部的に使われる。
struct empty_stream_buf : public std::streambuf {
    char dummybuf[8];

  protected:
    virtual int overflow(int c) {
        setp(dummybuf, dummybuf + sizeof(dummybuf));
        return c == traits_type::eof() ? '\0' : c;
    }
};

/// @brief
/// 空の出力ストリーム。ここへの出力は書き込んだフリをして全て捨てられる。
struct empty_stream : private empty_stream_buf, public std::ostream {
  public:
    empty_stream()
        : std::ostream(this) {
    }

    empty_stream_buf const *rdbuf() const {
        return this;
    }
};

/// @brief 空の出力ストリームのグローバルなインスタンス。 cout とかと同じ。
empty_stream es;

} // namespace pcl
