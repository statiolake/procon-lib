#pragma once

#include "../prelude.hpp"

#include <type_traits>

namespace pcl {

class nullopt_t {};
nullopt_t nullopt;

template <typename T, typename std::enable_if<!std::is_reference<T>::value,
                                              std::nullptr_t>::type = nullptr>
class optional {
  private:
    bool init_;
    std::aligned_storage<sizeof(T), alignof(T)>::type storage_;

    T *ptr() {
        return static_cast<T *>(static_cast<void *>(&storage_));
    }

  public:
    /// デフォルトコンストラクタ
    optional()
        : init_(false) {
    }

    /// コピーコンストラクタ
    optional(optional const &init)
        : init_(true) {
        new (ptr()) T(*init.ptr());
    }

    /// 中身を初期化するコンストラクタ
    template <typename... Args>
    optional(Args &&... args)
        : init_(true) {
        new (ptr()) T(std::forward<Args>(args)...);
    }

    /// nullopt によるコンストラクタ
    optional(nullopt_t const &)
        : init_(false) {
    }

    ~optional() {
        // デストラクタを呼ぶ
        if (init_) ptr()->~T();
    }
};

} // namespace pcl
