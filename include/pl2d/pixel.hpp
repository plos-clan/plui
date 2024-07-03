#pragma once
#include <define.h>
#include <type.hpp>

// pixel 也可以处理颜色变换等

namespace pl2d {

namespace color {
enum EFmtConv {
  U8,
  U16,
  U32,
  F32,
  F64,
};
enum EColorSpaceConv {
  RGB2Grayscale,
  RGB2HSV,
  HSV2RGB,
  RGB2HSL,
  HSL2RGB,
  RGB2XYZ,
  XYZ2RGB,
  XYZ2LAB,
  LAB2XYZ,
  RGB2LAB,
  LAB2RGB,
  XYZ2LUV,
  LUV2XYZ,
  RGB2LUV,
  LUV2RGB,
};
} // namespace color

dlimport auto gamma_correct(f32 x) -> f32;
dlimport auto gamma_correct(f64 x) -> f64;
dlimport auto reverse_gamma(f32 x) -> f32;
dlimport auto reverse_gamma(f64 x) -> f64;

#define BasePixelTemplate                                                                          \
  typename T, typename std::conditional_t<std::is_floating_point_v<T>, i32, T> T_MAX,              \
      typename std::conditional_t<std::is_floating_point_v<T>, i32, T> T_MAX_2, typename T2,       \
      typename FT
#define _BasePixelTemplate                                                                         \
  typename _T, typename std::conditional_t<std::is_floating_point_v<_T>, i32, _T> _T_MAX,          \
      typename std::conditional_t<std::is_floating_point_v<_T>, i32, _T> _T_MAX_2, typename _T2,   \
      typename _FT
#define BasePixelT  BasePixel<T, T_MAX, T_MAX_2, T2, FT>
#define _BasePixelT BasePixel<_T, _T_MAX, _T_MAX_2, _T2, _FT>

template <BasePixelTemplate>
struct BasePixel;

#define BasePixelBT BasePixel<u8, U8_MAX, I8_MAX, u32, f32>
#define BasePixelST BasePixel<u16, U16_MAX, I16_MAX, u32, f32>
#define BasePixelIT BasePixel<u32, U32_MAX, I32_MAX, u64, f64>
#define BasePixelFT BasePixel<f32, 1, 1, f32, f32>
#define BasePixelDT BasePixel<f64, 1, 1, f32, f64>

using PixelB = BasePixelBT; // byte
using PixelS = BasePixelST; // short
using PixelI = BasePixelIT; // int
using PixelF = BasePixelFT; // float
using PixelD = BasePixelDT; // double
using Pixel  = PixelB;

template <BasePixelTemplate>
struct BasePixel {
  union {
    struct {
#if COLOR_USE_BGR
      T b = 0, g = 0, r = 0, a = 0;
#else
      T r = 0, g = 0, b = 0, a = 0;
#endif
    };
    T d[4];
  };

  BasePixel() = default;
  BasePixel(u32);
  BasePixel(T r, T g, T b) : r(r), g(g), b(b), a(T_MAX) {}
  BasePixel(T r, T g, T b, T a) : r(r), g(g), b(b), a(a) {}
  BasePixel(const BasePixel &)                         = default;
  BasePixel(BasePixel &&) noexcept                     = default;
  auto operator=(const BasePixel &) -> BasePixel     & = default;
  auto operator=(BasePixel &&) noexcept -> BasePixel & = default;

  template <_BasePixelTemplate>
  BasePixel(const _BasePixelT &p);

  operator u32();

  auto operator[](size_t n) const -> T {
    return d[n];
  }
  auto operator[](size_t n) -> T & {
    return d[n];
  }

  auto operator+=(const BasePixel &s) -> BasePixel & {
    mix(s);
    return *this;
  }
  auto operator+(const BasePixel &s) const -> BasePixel {
    return mix(*this, s);
  }

  void        mix(const BasePixel &s);
  static auto mix(const BasePixel &c1, const BasePixel &c2) -> BasePixel;

  auto grayscale() const -> BasePixel;
  auto gamma_correct() const -> BasePixel;
  auto reverse_gamma() const -> BasePixel;

  auto to_u8() const -> PixelB;
  auto to_u16() const -> PixelS;
  auto to_u32() const -> PixelI;
  auto to_f32() const -> PixelF;
  auto to_f64() const -> PixelD;

  void RGB2Grayscale();
  void RGB2HSV();
  void HSV2RGB();
  void RGB2HSL();
  void HSL2RGB();
  void RGB2XYZ();
  void XYZ2RGB();
  void XYZ2LAB();
  void LAB2XYZ();
  void RGB2LAB();
  void LAB2RGB();
  void XYZ2LUV();
  void LUV2XYZ();
  void RGB2LUV();
  void LUV2RGB();
};

} // namespace pl2d
