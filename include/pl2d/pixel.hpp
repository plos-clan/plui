#pragma once
#include <define.h>
#include <type.hpp>

// pixel 也可以处理颜色变换等

namespace pl2d {

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

template <typename T>
struct BasePixel {
  union {
    struct {
      T r = 0, g = 0, b = 0, a = 0;
    };
    T d[4];
  };

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

struct PixelB : BasePixel<u8> {
  PixelB(const BasePixel<u8> &p) : BasePixel<u8>(p) {}
  PixelB(BasePixel<u8> &&p) : BasePixel<u8>(cpp::move(p)) {}

  void        mix(const PixelB &s);
  static auto mix(const PixelB &c1, const PixelB &c2) -> PixelB;

  auto to_grayscale() -> PixelB;

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

struct PixelS : BasePixel<u16> {
  void        mix(const PixelS &s);
  static auto mix(const PixelS &c1, const PixelS &c2) -> PixelS;

  auto to_grayscale() -> PixelS;

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

struct PixelI : BasePixel<u32> {
  void        mix(const PixelI &s);
  static auto mix(const PixelI &c1, const PixelI &c2) -> PixelI;

  auto to_grayscale() -> PixelI;

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

template <typename T>
struct BasePixelF : BasePixel<T> {};

struct PixelF : BasePixelF<f32> {
  void        mix(const PixelF &s);
  static auto mix(const PixelF &c1, const PixelF &c2) -> PixelF;

  auto to_grayscale() -> PixelF;

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

struct PixelD : BasePixelF<f64> {
  void        mix(const PixelD &s);
  static auto mix(const PixelD &c1, const PixelD &c2) -> PixelD;

  auto to_grayscale() -> PixelD;

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

using Pixel = PixelB;

} // namespace pl2d
