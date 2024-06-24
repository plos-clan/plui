#include "pl2d/pixel.hpp"
#include "cpp/math.hpp"
#include <c.h>
#include <cpp.hpp>
#include <define.h>
#include <pl2d.hpp>
#include <type.hpp>

#define FAST_COLOR_TRANSFORM 1

#ifndef FAST_COLOR_TRANSFORM
#  define FAST_COLOR_TRANSFORM 0
#endif

namespace pl2d {

// gamma 函数浮点输入范围均为 0-1
namespace gamma {

finline auto rgb2xyz(float x) -> float {
  return (x > 0.04045f) ? powf((x + 0.055f) / 1.055f, 2.4f) : (x / 12.92f);
}
finline auto xyz2rgb(float x) -> float {
  return (x > 0.0031308f) ? (1.055f * powf(x, 1 / 2.4f) - 0.055f) : (12.92f * x);
}
finline auto xyz2lab(float x) -> float {
  return (x > 0.008856f) ? cbrtf(x) : ((903.3f * x + 16.f) / 116.f);
}
finline auto lab2xyz(float x) -> float {
  return (x > 0.206893f) ? cubef(x) : (((x * 116.f) - 16.f) / 903.3f);
}

// finline auto xyz2luv(float x) -> float {
//   return (x > 0.008856f) ? (116.f * cbrtf(x) - 16.f) : ((903.3f * x + 16.f) / 116.f);
// }

// 输入范围 0-255 输出 0-1
#if FAST_COLOR_TRANSFORM
finline auto rgb2xyz(byte x) -> float {
#  include "pixel/rgb2xyz.lut.h"
  return lut[x];
}
finline auto xyz2rgb(byte x) -> float {
#  include "pixel/xyz2rgb.lut.h"
  return lut[x];
}
finline auto xyz2lab(byte x) -> float {
#  include "pixel/xyz2lab.lut.h"
  return lut[x];
}
finline auto lab2xyz(byte x) -> float {
#  include "pixel/lab2xyz.lut.h"
  return lut[x];
}
#else
finline auto rgb2xyz(byte x) -> float {
  return rgb2xyz(x / 255.f);
}
finline auto xyz2rgb(byte x) -> float {
  return xyz2rgb(x / 255.f);
}
finline auto xyz2lab(byte x) -> float {
  return xyz2lab(x / 255.f);
}
finline auto lab2xyz(byte x) -> float {
  return lab2xyz(x / 255.f);
}
#endif

// 输入范围 0-65535 输出 0-1
finline auto rgb2xyz(u16 x) -> float {
  return rgb2xyz(x / 65535.f);
}
finline auto xyz2rgb(u16 x) -> float {
  return xyz2rgb(x / 65535.f);
}
finline auto xyz2lab(u16 x) -> float {
  return xyz2lab(x / 65535.f);
}
finline auto lab2xyz(u16 x) -> float {
  return lab2xyz(x / 65535.f);
}

// 输入范围 0-4294967295 输出 0-1
finline auto rgb2xyz(u32 x) -> float {
  return rgb2xyz(x / 4294967295.f);
}
finline auto xyz2rgb(u32 x) -> float {
  return xyz2rgb(x / 4294967295.f);
}
finline auto xyz2lab(u32 x) -> float {
  return xyz2lab(x / 4294967295.f);
}
finline auto lab2xyz(u32 x) -> float {
  return lab2xyz(x / 4294967295.f);
}

} // namespace gamma

//* ----------------------------------------------------------------------------------------------------
//; 类型转换
//* ----------------------------------------------------------------------------------------------------

// --------------------------------------------------
//. u8

dlexport auto PixelB::to_u8() const -> PixelB {
  return *this;
}
dlexport auto PixelB::to_u16() const -> PixelS {}
dlexport auto PixelB::to_u32() const -> PixelI {}
dlexport auto PixelB::to_f32() const -> PixelF {
  return PixelF{r / 255.f, g / 255.f, b / 255.f, a / 255.f};
}
dlexport auto PixelB::to_f64() const -> PixelD {
  return PixelD{r / 255., g / 255., b / 255., a / 255.};
}

// --------------------------------------------------
//. u16

dlexport auto PixelS::to_u8() const -> PixelB {}
dlexport auto PixelS::to_u16() const -> PixelS {
  return *this;
}
dlexport auto PixelS::to_u32() const -> PixelI {}
dlexport auto PixelS::to_f32() const -> PixelF {
  return PixelF{r / 65535.f, g / 65535.f, b / 65535.f, a / 65535.f};
}
dlexport auto PixelS::to_f64() const -> PixelD {
  return PixelD{r / 65535., g / 65535., b / 65535., a / 65535.};
}

// --------------------------------------------------
//. u32

dlexport auto PixelI::to_u8() const -> PixelB {}
dlexport auto PixelI::to_u16() const -> PixelS {}
dlexport auto PixelI::to_u32() const -> PixelI {
  return *this;
}
dlexport auto PixelI::to_f32() const -> PixelF {
  return PixelF{r / 4294967295.f, g / 4294967295.f, b / 4294967295.f, a / 4294967295.f};
}
dlexport auto PixelI::to_f64() const -> PixelD {
  return PixelD{r / 4294967295., g / 4294967295., b / 4294967295., a / 4294967295.};
}

// --------------------------------------------------
//. f32

dlexport auto PixelF::to_u8() const -> PixelB {
  return PixelB{(byte)(r * 255), (byte)(g * 255), (byte)(b * 255), (byte)(a * 255)};
}
dlexport auto PixelF::to_u16() const -> PixelS {
  return PixelS{(u16)(r * 65535), (u16)(g * 65535), (u16)(b * 65535), (u16)(a * 65535)};
}
dlexport auto PixelF::to_u32() const -> PixelI {
  return PixelI{(u32)(r * 4294967295), (u32)(g * 4294967295), (u32)(b * 4294967295),
                (u32)(a * 4294967295)};
}
dlexport auto PixelF::to_f32() const -> PixelF {
  return *this;
}
dlexport auto PixelF::to_f64() const -> PixelD {
  return PixelD{r, g, b, a};
}

// --------------------------------------------------
//. f64

dlexport auto PixelD::to_u8() const -> PixelB {
  return PixelB{(byte)(r * 255), (byte)(g * 255), (byte)(b * 255), (byte)(a * 255)};
}
dlexport auto PixelD::to_u16() const -> PixelS {
  return PixelS{(u16)(r * 65535), (u16)(g * 65535), (u16)(b * 65535), (u16)(a * 65535)};
}
dlexport auto PixelD::to_u32() const -> PixelI {
  return PixelI{(u32)(r * 4294967295), (u32)(g * 4294967295), (u32)(b * 4294967295),
                (u32)(a * 4294967295)};
}
dlexport auto PixelD::to_f32() const -> PixelF {
  return PixelF{(f32)r, (f32)g, (f32)b, (f32)a};
}
dlexport auto PixelD::to_f64() const -> PixelD {
  return *this;
}

//* ----------------------------------------------------------------------------------------------------
//; mix
//* ----------------------------------------------------------------------------------------------------

dlexport void PixelB::mix(const PixelB &s) {
  i32 _a = 255 * (a + s.a) - a * s.a;
  i32 sw = 255 * s.a;
  i32 dw = a * (255 - s.a);
  r      = (r * dw + s.r * sw) / _a;
  g      = (g * dw + s.g * sw) / _a;
  b      = (b * dw + s.b * sw) / _a;
  a      = _a / 255;
}
dlexport auto PixelB::mix(const PixelB &c1, const PixelB &c2) -> PixelB {
  i32 _a = 255 * (c1.a + c2.a) - c1.a * c2.a;
  i32 w1 = 255 * c1.a;
  i32 w2 = 255 * c2.a;
  return PixelB{
      (byte)((c1.r * w1 + c2.r * w2) / _a),
      (byte)((c1.g * w1 + c2.g * w2) / _a),
      (byte)((c1.b * w1 + c2.b * w2) / _a),
      (byte)(_a / 255),
  };
}

dlexport void PixelS::mix(const PixelS &s) {
  u32 _a = 65535 * (a + s.a) - a * s.a;
  u32 sw = 65535 * s.a;
  u32 dw = a * (65535 - s.a);
  r      = (r * dw + s.r * sw) / _a;
  g      = (g * dw + s.g * sw) / _a;
  b      = (b * dw + s.b * sw) / _a;
  a      = _a / 65535;
}
dlexport auto PixelS::mix(const PixelS &c1, const PixelS &c2) -> PixelS {
  u32 _a = 65535 * (c1.a + c2.a) - c1.a * c2.a;
  u32 w1 = 65535 * c1.a;
  u32 w2 = 65535 * c2.a;
  return PixelS{
      (u16)((c1.r * w1 + c2.r * w2) / _a),
      (u16)((c1.g * w1 + c2.g * w2) / _a),
      (u16)((c1.b * w1 + c2.b * w2) / _a),
      (u16)(_a / 65535),
  };
}

dlexport void PixelI::mix(const PixelI &s) {
  u64 _a = 4294967295 * (a + s.a) - a * s.a;
  u64 sw = 4294967295 * s.a;
  u64 dw = a * (4294967295 - s.a);
  r      = (r * dw + s.r * sw) / _a;
  g      = (g * dw + s.g * sw) / _a;
  b      = (b * dw + s.b * sw) / _a;
  a      = _a / 4294967295;
}
dlexport auto PixelI::mix(const PixelI &c1, const PixelI &c2) -> PixelI {
  u64 _a = 4294967295 * (c1.a + c2.a) - c1.a * c2.a;
  u64 w1 = 4294967295 * c1.a;
  u64 w2 = 4294967295 * c2.a;
  return PixelI{
      (u32)((c1.r * w1 + c2.r * w2) / _a),
      (u32)((c1.g * w1 + c2.g * w2) / _a),
      (u32)((c1.b * w1 + c2.b * w2) / _a),
      (u32)(_a / 4294967295),
  };
}

dlexport void PixelF::mix(const PixelF &s) {
  f32 _a = a + s.a - a * s.a;
  f32 sw = s.a;
  f32 dw = a * (1 - s.a);
  r      = (r * dw + s.r * sw) / _a;
  g      = (g * dw + s.g * sw) / _a;
  b      = (b * dw + s.b * sw) / _a;
  a      = _a;
}
dlexport auto PixelF::mix(const PixelF &c1, const PixelF &c2) -> PixelF {
  f32 _a = c1.a + c2.a - c1.a * c2.a;
  f32 w1 = c1.a;
  f32 w2 = c2.a;
  return PixelF{
      (c1.r * w1 + c2.r * w2) / _a,
      (c1.g * w1 + c2.g * w2) / _a,
      (c1.b * w1 + c2.b * w2) / _a,
      _a,
  };
}

dlexport void PixelD::mix(const PixelD &s) {
  f64 _a = a + s.a - a * s.a;
  f64 sw = s.a;
  f64 dw = a * (1 - s.a);
  r      = (r * dw + s.r * sw) / _a;
  g      = (g * dw + s.g * sw) / _a;
  b      = (b * dw + s.b * sw) / _a;
  a      = _a;
}
dlexport auto PixelD::mix(const PixelD &c1, const PixelD &c2) -> PixelD {
  f64 _a = c1.a + c2.a - c1.a * c2.a;
  f64 w1 = c1.a;
  f64 w2 = c2.a;
  return PixelD{
      (c1.r * w1 + c2.r * w2) / _a,
      (c1.g * w1 + c2.g * w2) / _a,
      (c1.b * w1 + c2.b * w2) / _a,
      _a,
  };
}

//* ----------------------------------------------------------------------------------------------------
//; 颜色转换
//* ----------------------------------------------------------------------------------------------------

// --------------------------------------------------
//. 灰度

#if FAST_COLOR_TRANSFORM
auto PixelB::to_grayscale() -> PixelB {
  byte gray = (r * 19595 + g * 38470 + b * 7471) / 65536;
  return PixelB{gray, gray, gray, a};
}
void PixelB::RGB2Grayscale() {
  byte gray = (r * 19595 + g * 38470 + b * 7471) / 65536;
  r = g = b = gray;
}
#else
auto PixelB::to_grayscale() -> PixelB {
  byte gray = r * .299f + g * .587f + b * .114f;
  return PixelB{gray, gray, gray, a};
}
void PixelB::RGB2Grayscale() {
  byte gray = r * .299f + g * .587f + b * .114f;
  r = g = b = gray;
}
#endif

#if FAST_COLOR_TRANSFORM
auto PixelS::to_grayscale() -> PixelS {
  u16 gray = (r * 19595U + g * 38470U + b * 7471U) / 65536U;
  return PixelS{gray, gray, gray, a};
}
void PixelS::RGB2Grayscale() {
  u16 gray = (r * 19595U + g * 38470U + b * 7471U) / 65536U;
  r = g = b = gray;
}
#else
auto PixelS::to_grayscale() -> PixelS {
  u16 gray = r * .299f + g * .587f + b * .114f;
  return PixelS{gray, gray, gray, a};
}
void PixelS::RGB2Grayscale() {
  u16 gray = r * .299f + g * .587f + b * .114f;
  r = g = b = gray;
}
#endif

#if FAST_COLOR_TRANSFORM
auto PixelI::to_grayscale() -> PixelI {
  u32 gray = (r * 19595ULL + g * 38470ULL + b * 7471ULL) / 65536ULL;
  return PixelI{gray, gray, gray, a};
}
void PixelI::RGB2Grayscale() {
  u32 gray = (r * 19595ULL + g * 38470ULL + b * 7471ULL) / 65536ULL;
  r = g = b = gray;
}
#else
auto PixelI::to_grayscale() -> PixelI {
  u32 gray = r * .299f + g * .587f + b * .114f;
  return PixelI{gray, gray, gray, a};
}
void PixelI::RGB2Grayscale() {
  u32 gray = r * .299f + g * .587f + b * .114f;
  r = g = b = gray;
}
#endif

auto PixelF::to_grayscale() -> PixelF {
  f32 gray = r * .299f + g * .587f + b * .114f;
  return PixelF{gray, gray, gray, a};
}
void PixelF::RGB2Grayscale() {
  f32 gray = r * .299f + g * .587f + b * .114f;
  r = g = b = gray;
}

auto PixelD::to_grayscale() -> PixelD {
  f64 gray = r * .299 + g * .587 + b * .114;
  return PixelD{gray, gray, gray, a};
}
void PixelD::RGB2Grayscale() {
  f64 gray = r * .299 + g * .587 + b * .114;
  r = g = b = gray;
}

// --------------------------------------------------
//.

void PixelB::RGB2LAB() {
  float r = gamma::rgb2xyz(this->r);
  float g = gamma::rgb2xyz(this->g);
  float b = gamma::rgb2xyz(this->b);

  float x = r * 0.4124564f + g * 0.3575761f + b * 0.1804375f;
  float y = r * 0.2126729f + g * 0.7151522f + b * 0.0721750f;
  float z = r * 0.0193339f + g * 0.1191920f + b * 0.9503041f;

  x /= 0.950456f;
  y /= 1.0f;
  z /= 1.088754f;

  x = gamma::xyz2lab(x);
  y = gamma::xyz2lab(y);
  z = gamma::xyz2lab(z);

  this->r = y * 255;       // l
  this->g = (x - y) * 127; // a
  this->b = (y - z) * 127; // b
}

void PixelB::LAB2RGB() {
  float y = this->r;     // l
  float x = y + this->g; // a
  float z = y - this->b; // b

  x = gamma::lab2xyz(x);
  y = gamma::lab2xyz(y);
  z = gamma::lab2xyz(z);

  x *= 0.950456f;
  y *= 1.0f;
  z *= 1.088754f;

  float r = x * 3.2404542f + y * -1.5371385f + z * -0.4985314f;
  float g = x * -0.9692660f + y * 1.8760108f + z * 0.0415560f;
  float b = x * 0.0556434f + y * -0.2040259f + z * 1.0572252f;

  this->r = gamma::xyz2rgb(r);
  this->g = gamma::xyz2rgb(g);
  this->b = gamma::xyz2rgb(b);
}

void PixelB::RGB2HSV() {
  float rNorm = r / 255.0f;
  float gNorm = g / 255.0f;
  float bNorm = b / 255.0f;

  float max   = std::max({rNorm, gNorm, bNorm});
  float min   = std::min({rNorm, gNorm, bNorm});
  float delta = max - min;

  float h = 0, s = 0, v = max;

  if (delta > 0.00001f) {
    s = delta / max;

    if (rNorm == max) {
      h = (gNorm - bNorm) / delta;
    } else if (gNorm == max) {
      h = 2.0f + (bNorm - rNorm) / delta;
    } else {
      h = 4.0f + (rNorm - gNorm) / delta;
    }

    h *= 60.0f;
    if (h < 0) { h += 360.0f; }
  }

  // 将 HSV 值存储在 r, g, b 字段中
  r = static_cast<byte>(h / 360.0f * 255.0f);
  g = static_cast<byte>(s * 255.0f);
  b = static_cast<byte>(v * 255.0f);
}

void PixelB::HSV2RGB() {
  float h = r / 255.0f * 360.0f;
  float s = g / 255.0f;
  float v = b / 255.0f;

  float c = v * s;
  float x = c * (1.0f - fabs(fmod(h / 60.0f, 2) - 1.0f));
  float m = v - c;

  float rNorm, gNorm, bNorm;

  if (h < 60.0f) {
    rNorm = c;
    gNorm = x;
    bNorm = 0;
  } else if (h < 120.0f) {
    rNorm = x;
    gNorm = c;
    bNorm = 0;
  } else if (h < 180.0f) {
    rNorm = 0;
    gNorm = c;
    bNorm = x;
  } else if (h < 240.0f) {
    rNorm = 0;
    gNorm = x;
    bNorm = c;
  } else if (h < 300.0f) {
    rNorm = x;
    gNorm = 0;
    bNorm = c;
  } else {
    rNorm = c;
    gNorm = 0;
    bNorm = x;
  }

  r = static_cast<byte>((rNorm + m) * 255.0f);
  g = static_cast<byte>((gNorm + m) * 255.0f);
  b = static_cast<byte>((bNorm + m) * 255.0f);
}

void PixelB::RGB2HSL() {
  float rNorm = r / 255.0f;
  float gNorm = g / 255.0f;
  float bNorm = b / 255.0f;

  float max   = std::max({rNorm, gNorm, bNorm});
  float min   = std::min({rNorm, gNorm, bNorm});
  float delta = max - min;

  float h = 0, s = 0, l = (max + min) / 2.0f;

  if (delta > 0.00001f) {
    if (l > 0.5f) {
      s = delta / (2.0f - max - min);
    } else {
      s = delta / (max + min);
    }

    if (rNorm == max) {
      h = (gNorm - bNorm) / delta;
    } else if (gNorm == max) {
      h = 2.0f + (bNorm - rNorm) / delta;
    } else {
      h = 4.0f + (rNorm - gNorm) / delta;
    }

    h *= 60.0f;
    if (h < 0) { h += 360.0f; }
  }

  // 将 HSL 值存储在 r, g, b 字段中
  r = static_cast<byte>(h / 360.0f * 255.0f);
  g = static_cast<byte>(s * 255.0f);
  b = static_cast<byte>(l * 255.0f);
}

void PixelB::HSL2RGB() {
  float h = r / 255.0f * 360.0f;
  float s = g / 255.0f;
  float l = b / 255.0f;

  float c = (1.0f - fabs(2.0f * l - 1.0f)) * s;
  float x = c * (1.0f - fabs(fmod(h / 60.0f, 2) - 1.0f));
  float m = l - c / 2.0f;

  float rNorm, gNorm, bNorm;

  if (h < 60.0f) {
    rNorm = c;
    gNorm = x;
    bNorm = 0;
  } else if (h < 120.0f) {
    rNorm = x;
    gNorm = c;
    bNorm = 0;
  } else if (h < 180.0f) {
    rNorm = 0;
    gNorm = c;
    bNorm = x;
  } else if (h < 240.0f) {
    rNorm = 0;
    gNorm = x;
    bNorm = c;
  } else if (h < 300.0f) {
    rNorm = x;
    gNorm = 0;
    bNorm = c;
  } else {
    rNorm = c;
    gNorm = 0;
    bNorm = x;
  }

  r = static_cast<byte>((rNorm + m) * 255.0f);
  g = static_cast<byte>((gNorm + m) * 255.0f);
  b = static_cast<byte>((bNorm + m) * 255.0f);
}

//* ----------------------------------------------------------------------------------------------------
//; float32
//* ----------------------------------------------------------------------------------------------------

void PixelF::RGB2HSV() {
  float max   = cpp::max(r, g, b);
  float min   = cpp::min(r, g, b);
  float delta = max - min;

  float h = 0, s = 0, v = max;
  if (delta > 1e-5f) {
    s = delta / max;
    h = ((r == max) ? (g - b) : (g == max) ? (2 + b - r) : (4 + r - g)) / (delta * 6);
    if (h < 0) h += 1;
  }

  this->r = h;
  this->g = s;
  this->b = v;
}

void PixelF::HSV2RGB() {
  float h = this->r * 6;
  float s = this->g;
  float v = this->b;

  float c = v * s;
  float x = c * (1 - cpp::abs(cpp::mod(h, 2) - 1));
  float m = v - c;

  float r, g, b;
  if (h < 1) {
    r = c;
    g = x;
    b = 0;
  } else if (h < 2) {
    r = x;
    g = c;
    b = 0;
  } else if (h < 3) {
    r = 0;
    g = c;
    b = x;
  } else if (h < 4) {
    r = 0;
    g = x;
    b = c;
  } else if (h < 5) {
    r = x;
    g = 0;
    b = c;
  } else {
    r = c;
    g = 0;
    b = x;
  }

  this->r = r + m;
  this->g = g + m;
  this->b = b + m;
}

void PixelF::RGB2HSL() {
  float max   = cpp::max(r, g, b);
  float min   = cpp::min(r, g, b);
  float delta = max - min;

  float h = 0, s = 0, l = max + min;
  if (delta > 1e-5f) {
    s = delta / (l > 1 ? 2 - l : l);
    h = ((r == max) ? (g - b) : (g == max) ? (2 + b - r) : (4 + r - g)) / (delta * 6);
    if (h < 0) h += 1;
  }
  l /= 2;

  this->r = h;
  this->g = s;
  this->b = l;
}

void PixelF::HSL2RGB() {
  float h = this->r * 6;
  float s = this->g;
  float l = this->b;

  float c = (1 - cpp::abs(2 * l - 1)) * s;
  float x = c * (1 - cpp::abs(cpp::mod(h, 2) - 1));
  float m = l - c / 2;

  float r, g, b;
  if (h < 1) {
    r = c;
    g = x;
    b = 0;
  } else if (h < 2) {
    r = x;
    g = c;
    b = 0;
  } else if (h < 3) {
    r = 0;
    g = c;
    b = x;
  } else if (h < 4) {
    r = 0;
    g = x;
    b = c;
  } else if (h < 5) {
    r = x;
    g = 0;
    b = c;
  } else {
    r = c;
    g = 0;
    b = x;
  }

  this->r = r + m;
  this->g = g + m;
  this->b = b + m;
}

void PixelF::RGB2LAB() {
  float r = gamma::rgb2xyz(this->r);
  float g = gamma::rgb2xyz(this->g);
  float b = gamma::rgb2xyz(this->b);

  float x = r * 0.4124564f + g * 0.3575761f + b * 0.1804375f;
  float y = r * 0.2126729f + g * 0.7151522f + b * 0.0721750f;
  float z = r * 0.0193339f + g * 0.1191920f + b * 0.9503041f;

  x /= 0.950456f;
  y /= 1.0f;
  z /= 1.088754f;

  x = gamma::xyz2lab(x);
  y = gamma::xyz2lab(y);
  z = gamma::xyz2lab(z);

  this->r = y;     // l
  this->g = x - y; // a
  this->b = y - z; // b
}

void PixelF::LAB2RGB() {
  float y = this->r;     // l
  float x = y + this->g; // a
  float z = y - this->b; // b

  x = gamma::lab2xyz(x);
  y = gamma::lab2xyz(y);
  z = gamma::lab2xyz(z);

  x *= 0.950456f;
  y *= 1.0f;
  z *= 1.088754f;

  float r = x * 3.2404542f + y * -1.5371385f + z * -0.4985314f;
  float g = x * -0.9692660f + y * 1.8760108f + z * 0.0415560f;
  float b = x * 0.0556434f + y * -0.2040259f + z * 1.0572252f;

  this->r = gamma::xyz2rgb(r);
  this->g = gamma::xyz2rgb(g);
  this->b = gamma::xyz2rgb(b);
}

//;  未实现
void PixelF::XYZ2LUV() {
  float x = this->r;
  float y = this->g;
  float z = this->b;

  float L = (y > 0.008856f) ? 116.f * cbrtf(y) - 16.f : (903.3f * y + 16.f) / 116.f;

  float u_prime = 4.f * x / (x + 15.f * y + 3.f * z);
  float v_prime = 9.f * y / (x + 15.f * y + 3.f * z);

  this->r = L;       // L component
  this->g = u_prime; // u' component
  this->b = v_prime; // v' component
}

//* ----------------------------------------------------------------------------------------------------
//; float64
//* ----------------------------------------------------------------------------------------------------

//+ 参照 float32

void PixelD::RGB2HSV() {
  f64 max   = cpp::max(r, g, b);
  f64 min   = cpp::min(r, g, b);
  f64 delta = max - min;

  f64 h = 0, s = 0, v = max;
  if (delta > 1e-5) {
    s = delta / max;
    h = ((r == max) ? (g - b) : (g == max) ? (2 + b - r) : (4 + r - g)) / (delta * 6);
    if (h < 0) h += 1;
  }

  this->r = h;
  this->g = s;
  this->b = v;
}

void PixelD::HSV2RGB() {
  f64 h = this->r * 6;
  f64 s = this->g;
  f64 v = this->b;

  f64 c = v * s;
  f64 x = c * (1 - cpp::abs(cpp::mod(h, 2) - 1));
  f64 m = v - c;

  f64 r, g, b;
  if (h < 1) {
    r = c;
    g = x;
    b = 0;
  } else if (h < 2) {
    r = x;
    g = c;
    b = 0;
  } else if (h < 3) {
    r = 0;
    g = c;
    b = x;
  } else if (h < 4) {
    r = 0;
    g = x;
    b = c;
  } else if (h < 5) {
    r = x;
    g = 0;
    b = c;
  } else {
    r = c;
    g = 0;
    b = x;
  }

  this->r = r + m;
  this->g = g + m;
  this->b = b + m;
}

void PixelD::RGB2HSL() {
  f64 max   = cpp::max(r, g, b);
  f64 min   = cpp::min(r, g, b);
  f64 delta = max - min;

  f64 h = 0, s = 0, l = max + min;
  if (delta > 1e-5) {
    s = delta / (l > 1 ? 2 - l : l);
    h = ((r == max) ? (g - b) : (g == max) ? (2 + b - r) : (4 + r - g)) / (delta * 6);
    if (h < 0) h += 1;
  }
  l /= 2;

  this->r = h;
  this->g = s;
  this->b = l;
}

void PixelD::HSL2RGB() {
  f64 h = this->r * 6;
  f64 s = this->g;
  f64 l = this->b;

  f64 c = (1 - cpp::abs(2 * l - 1)) * s;
  f64 x = c * (1 - cpp::abs(cpp::mod(h, 2) - 1));
  f64 m = l - c / 2;

  f64 r, g, b;
  if (h < 1) {
    r = c;
    g = x;
    b = 0;
  } else if (h < 2) {
    r = x;
    g = c;
    b = 0;
  } else if (h < 3) {
    r = 0;
    g = c;
    b = x;
  } else if (h < 4) {
    r = 0;
    g = x;
    b = c;
  } else if (h < 5) {
    r = x;
    g = 0;
    b = c;
  } else {
    r = c;
    g = 0;
    b = x;
  }

  this->r = r + m;
  this->g = g + m;
  this->b = b + m;
}

} // namespace pl2d
