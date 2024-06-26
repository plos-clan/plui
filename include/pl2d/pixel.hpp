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

// Gamma校正的参数
// 目前似乎用不上
constexpr f32 GAMMA = 2.2f;

dlimport auto gamma(f32 x, f32 g = GAMMA) -> f32;
dlimport auto gamma(f64 x, f64 g = GAMMA) -> f64;
dlimport auto igamma(f32 x, f32 g = GAMMA) -> f32;
dlimport auto igamma(f64 x, f64 g = GAMMA) -> f64;

struct PixelB; // byte
struct PixelS; // short
struct PixelI; // int
struct PixelF; // float
struct PixelD; // double

#define BasePixelTemplate                                                                          \
  typename T, typename std::conditional_t<std::is_floating_point_v<T>, i32, T> v_max,              \
      typename std::conditional_t<std::is_floating_point_v<T>, i32, T> v_max_2, typename T2,       \
      typename FT
#define BasePixelT BasePixel<T, v_max, v_max_2, T2, FT>

template <BasePixelTemplate>
struct BasePixel {
  union {
    struct {
      T r = 0, g = 0, b = 0, a = 0;
    };
    T d[4];
  };

  BasePixel() = default;
  BasePixel(T r, T g, T b, T a) : r(r), g(g), b(b), a(a) {}
  BasePixel(const BasePixel &)                         = default;
  BasePixel(BasePixel &&) noexcept                     = default;
  auto operator=(const BasePixel &) -> BasePixel     & = default;
  auto operator=(BasePixel &&) noexcept -> BasePixel & = default;

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

  auto to_grayscale() -> BasePixel;

  auto to_u8() const -> PixelB;
  auto to_u16() const -> PixelS;
  auto to_u32() const -> PixelI;
  auto to_f32() const -> PixelF;
  auto to_f64() const -> PixelD;

  operator PixelB();
  operator PixelS();
  operator PixelI();
  operator PixelF();
  operator PixelD();

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

struct PixelB : BasePixel<u8, 255, 128, u32, f32> {
  using BasePixel::BasePixel;

  auto to_u8() const -> PixelB;
  auto to_u16() const -> PixelS;
  auto to_u32() const -> PixelI;
  auto to_f32() const -> PixelF;
  auto to_f64() const -> PixelD;

#if FAST_COLOR_TRANSFORM
  auto to_grayscale() const -> PixelB;
  void RGB2Grayscale();
#endif
};

struct PixelS : BasePixel<u16, 65535, 32767, u32, f32> {
  using BasePixel::BasePixel;

  auto to_u8() const -> PixelB;
  auto to_u16() const -> PixelS;
  auto to_u32() const -> PixelI;
  auto to_f32() const -> PixelF;
  auto to_f64() const -> PixelD;

#if FAST_COLOR_TRANSFORM
  auto to_grayscale() const -> PixelS;
  void RGB2Grayscale();
#endif
};

struct PixelI : BasePixel<u32, 4294967295, 2147483647, u64, f32> {
  using BasePixel::BasePixel;

  auto to_u8() const -> PixelB;
  auto to_u16() const -> PixelS;
  auto to_u32() const -> PixelI;
  auto to_f32() const -> PixelF;
  auto to_f64() const -> PixelD;

#if FAST_COLOR_TRANSFORM
  auto to_grayscale() const -> PixelI;
  void RGB2Grayscale();
#endif
};

struct PixelF : BasePixel<f32, 1, 1, f32, f32> {
  using BasePixel::BasePixel;

  auto to_grayscale() -> PixelF;

  auto to_u8() const -> PixelB;
  auto to_u16() const -> PixelS;
  auto to_u32() const -> PixelI;
  auto to_f32() const -> PixelF;
  auto to_f64() const -> PixelD;
};

struct PixelD : BasePixel<f64, 1, 1, f32, f64> {
  using BasePixel::BasePixel;

  auto to_grayscale() -> PixelD;

  auto to_u8() const -> PixelB;
  auto to_u16() const -> PixelS;
  auto to_u32() const -> PixelI;
  auto to_f32() const -> PixelF;
  auto to_f64() const -> PixelD;
};

using Pixel = PixelB;

} // namespace pl2d
