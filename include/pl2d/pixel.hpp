#pragma once
#include <define.h>
#include <type.hpp>

namespace pl2d {

struct PixelB; // byte
struct PixelS; // short
struct PixelI; // int
struct PixelF; // float
struct PixelD; // double

struct PixelB {
  union {
    struct {
      byte r = 0, g = 0, b = 0, a = 0;
    };
    byte d[4];
  };

  auto operator[](size_t n) const -> byte {
    return d[n];
  }
  auto operator[](size_t n) -> byte & {
    return d[n];
  }

  auto operator+=(const PixelB &s) -> PixelB & {
    mix(s);
    return *this;
  }
  auto operator+(const PixelB &s) const -> PixelB {
    return mix(*this, s);
  }

  void        mix(const PixelB &s);
  static auto mix(const PixelB &c1, const PixelB &c2) -> PixelB;

  auto to_u8() const -> PixelB;
  auto to_u16() const -> PixelS;
  auto to_u32() const -> PixelI;
  auto to_f32() const -> PixelF;
  auto to_f64() const -> PixelD;

  auto to_grayscale() -> PixelB;

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

struct PixelS {
  union {
    struct {
      u16 r = 0, g = 0, b = 0, a = 0;
    };
    u16 d[4];
  };

  auto operator[](size_t n) const -> u16 {
    return d[n];
  }
  auto operator[](size_t n) -> u16 & {
    return d[n];
  }

  auto operator+=(const PixelS &s) -> PixelS & {
    mix(s);
    return *this;
  }
  auto operator+(const PixelS &s) const -> PixelS {
    return mix(*this, s);
  }

  void        mix(const PixelS &s);
  static auto mix(const PixelS &c1, const PixelS &c2) -> PixelS;

  auto to_u8() const -> PixelB;
  auto to_u16() const -> PixelS;
  auto to_u32() const -> PixelI;
  auto to_f32() const -> PixelF;
  auto to_f64() const -> PixelD;

  auto to_grayscale() -> PixelS;

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

struct PixelI {
  union {
    struct {
      u32 r = 0, g = 0, b = 0, a = 0;
    };
    u32 d[4];
  };

  auto operator[](size_t n) const -> u32 {
    return d[n];
  }
  auto operator[](size_t n) -> u32 & {
    return d[n];
  }

  auto operator+=(const PixelI &s) -> PixelI & {
    mix(s);
    return *this;
  }
  auto operator+(const PixelI &s) const -> PixelI {
    return mix(*this, s);
  }

  void        mix(const PixelI &s);
  static auto mix(const PixelI &c1, const PixelI &c2) -> PixelI;

  auto to_u8() const -> PixelB;
  auto to_u16() const -> PixelS;
  auto to_u32() const -> PixelI;
  auto to_f32() const -> PixelF;
  auto to_f64() const -> PixelD;

  auto to_grayscale() -> PixelI;

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

struct PixelF {
  union {
    struct {
      f32 r = 0, g = 0, b = 0, a = 0;
    };
    f32 d[4];
  };

  auto operator[](size_t n) const -> f32 {
    return d[n];
  }
  auto operator[](size_t n) -> f32 & {
    return d[n];
  }

  auto operator+=(const PixelF &s) -> PixelF & {
    mix(s);
    return *this;
  }
  auto operator+(const PixelF &s) const -> PixelF {
    return mix(*this, s);
  }

  void        mix(const PixelF &s);
  static auto mix(const PixelF &c1, const PixelF &c2) -> PixelF;

  auto to_u8() const -> PixelB;
  auto to_u16() const -> PixelS;
  auto to_u32() const -> PixelI;
  auto to_f32() const -> PixelF;
  auto to_f64() const -> PixelD;

  auto to_grayscale() -> PixelF;

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

struct PixelD {
  union {
    struct {
      f64 r = 0, g = 0, b = 0, a = 0;
    };
    f64 d[4];
  };

  auto operator[](size_t n) const -> f64 {
    return d[n];
  }
  auto operator[](size_t n) -> f64 & {
    return d[n];
  }

  auto operator+=(const PixelD &s) -> PixelD & {
    mix(s);
    return *this;
  }
  auto operator+(const PixelD &s) const -> PixelD {
    return mix(*this, s);
  }

  void        mix(const PixelD &s);
  static auto mix(const PixelD &c1, const PixelD &c2) -> PixelD;

  auto to_u8() const -> PixelB;
  auto to_u16() const -> PixelS;
  auto to_u32() const -> PixelI;
  auto to_f32() const -> PixelF;
  auto to_f64() const -> PixelD;

  auto to_grayscale() -> PixelD;

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
