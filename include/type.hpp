#pragma once
#include <config.h>

namespace cpp {

template <typename T>
struct remove_reference {
  using type = T;
};

template <typename T>
using remove_reference_t = typename remove_reference<T>::type;

template <typename T>
constexpr auto move(T &&t) noexcept -> remove_reference_t<T> && {
  return static_cast<remove_reference_t<T> &&>(t);
}

template <bool, typename T = void>
struct enable_if {};

template <typename T>
struct enable_if<true, T> {
  using type = T;
};

template <bool C, typename T = void>
using enable_if_t = typename enable_if<C, T>::type;

template <typename T, T v>
struct integral_constant {};

template <typename Base, typename Derived>
struct is_base_of : public integral_constant<bool, __is_base_of(Base, Derived)> {};

template <typename Base, typename Derived>
inline constexpr bool is_base_of_v = __is_base_of(Base, Derived);

} // namespace cpp

static const auto null = nullptr;

using ssize_t = __INTPTR_TYPE__;
using size_t  = __UINTPTR_TYPE__;

using uchar  = unsigned char;
using ushort = unsigned short;
using uint   = unsigned int;
using ulong  = unsigned long;

using int8_t     = __INT8_TYPE__;
using uint8_t    = __UINT8_TYPE__;
using int16_t    = __INT16_TYPE__;
using uint16_t   = __UINT16_TYPE__;
using int32_t    = __INT32_TYPE__;
using uint32_t   = __UINT32_TYPE__;
using int64_t    = __INT64_TYPE__;
using uint64_t   = __UINT64_TYPE__;
using int128_t   = __int128;
using uint128_t  = unsigned __int128;
using float16_t  = _Float16;
using float32_t  = float;
using float64_t  = double;
using float128_t = __float128;

using i8   = int8_t;
using u8   = uint8_t;
using i16  = int16_t;
using u16  = uint16_t;
using i32  = int32_t;
using u32  = uint32_t;
using i64  = int64_t;
using u64  = uint64_t;
using i128 = int128_t;
using u128 = uint128_t;
using f16  = float16_t;
using f32  = float32_t;
using f64  = float64_t;
using f128 = float128_t;

using cfloat  = _Complex float;
using cdouble = _Complex double;
using complex = _Complex double;

using cint8_t     = _Complex __INT8_TYPE__;
using cuint8_t    = _Complex __UINT8_TYPE__;
using cint16_t    = _Complex __INT16_TYPE__;
using cuint16_t   = _Complex __UINT16_TYPE__;
using cint32_t    = _Complex __INT32_TYPE__;
using cuint32_t   = _Complex __UINT32_TYPE__;
using cint64_t    = _Complex __INT64_TYPE__;
using cuint64_t   = _Complex __UINT64_TYPE__;
using cfloat16_t  = _Complex _Float16;
using cfloat32_t  = _Complex float;
using cfloat64_t  = _Complex double;
using cfloat128_t = _Complex __float128;

using sbyte = i8;
using byte  = u8;

using cstr = const char *;

class RefCount {
public:
  size_t __rc__ = 0;
};

template <typename T>
class __P__ {
#define __rc__ (((RefCount *)ptr)->__rc__)

public:
  T *ptr = null;

  __P__() = default;

  __P__(T *p) : ptr(p) {
    if (ptr) __rc__++;
  }

  template <typename U, typename = typename cpp::enable_if_t<cpp::is_base_of_v<T, U>>>
  __P__(U *p) : ptr(static_cast<T *>(p)) {
    if (ptr) __rc__++;
  }

  __P__(const __P__<T> &p) : ptr(p.ptr) {
    if (ptr) __rc__++;
  }

  template <typename U, typename = typename cpp::enable_if_t<cpp::is_base_of_v<T, U>>>
  __P__(const __P__<U> &p) : ptr(static_cast<T *>(p.ptr)) {
    if (ptr) __rc__++;
  }

  __P__(__P__<T> &&p) noexcept : ptr(p.ptr) {
    p.ptr = null;
  }

  template <typename U, typename = typename cpp::enable_if_t<cpp::is_base_of_v<T, U>>>
  __P__(__P__<U> &&p) noexcept : ptr(p.ptr) {
    p.ptr = null;
  }

  auto operator=(const __P__<T> &p) -> __P__<T> & {
    if (this == &p) return *this;
    if (ptr != null && --__rc__ == 0) delete ptr;
    ptr = p.ptr;
    __rc__++;
    return *this;
  }

  template <typename U, typename = typename cpp::enable_if_t<cpp::is_base_of_v<T, U>>>
  auto operator=(const __P__<U> &p) -> __P__<T> & {
    if (this == &p) return *this;
    if (ptr != null && --__rc__ == 0) delete ptr;
    ptr = static_cast<T *>(p.ptr);
    __rc__++;
    return *this;
  }

  auto operator=(__P__<T> &&p) noexcept -> __P__<T> & {
    if (this == &p) return *this;
    if (ptr != null && --__rc__ == 0) delete ptr;
    ptr   = p.ptr;
    p.ptr = null;
    return *this;
  }

  template <typename U, typename = typename cpp::enable_if_t<cpp::is_base_of_v<T, U>>>
  auto operator=(__P__<U> &&p) noexcept -> __P__<T> & {
    if (this == &p) return *this;
    if (ptr != null && --__rc__ == 0) delete ptr;
    ptr   = static_cast<T *>(p.ptr);
    p.ptr = null;
    return *this;
  }

  ~__P__() {
    if (ptr != null && --__rc__ == 0) delete ptr;
  }

  auto operator*() const -> T & {
    return *ptr;
  }

  auto operator->() const -> T * {
    return ptr;
  }

  operator T *() const {
    return ptr;
  }

  template <typename U, typename = typename cpp::enable_if_t<cpp::is_base_of_v<U, T>>>
  operator U *() const {
    return static_cast<U *>(ptr);
  }

#undef __rc__
};

#define __Pclass__(__name__)                                                                       \
  class __name__;                                                                                  \
  using P##__name__ = __P__<__name__>
#define __P__(__name__) using P##__name__ = __P__<__name__>

template <typename T1, typename T2>
static inline auto isinstance(const T2 *ptr) -> bool {
  static_assert(cpp::is_base_of_v<T2, T1>);
  return dynamic_cast<const T1 *>(ptr) != null;
}
