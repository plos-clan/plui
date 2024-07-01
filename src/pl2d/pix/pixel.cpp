#include "pl2d/pixel.hpp"
#include <c.h>
#include <cpp.hpp>
#include <define.h>
#include <pl2d.hpp>
#include <type.hpp>

namespace pl2d {

auto gamma(f32 x, f32 g) -> f32 {
  return cpp::pow(x, g);
}

auto gamma(f64 x, f64 g) -> f64 {
  return cpp::pow(x, g);
}

auto igamma(f32 x, f32 g) -> f32 {
  return cpp::pow(x, 1.f / g);
}

auto igamma(f64 x, f64 g) -> f64 {
  return cpp::pow(x, 1.f / g);
}

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
//; 灰度
//* ----------------------------------------------------------------------------------------------------

#if FAST_COLOR_TRANSFORM
auto PixelB::to_grayscale() -> PixelB {
  byte gray = (r * 19595 + g * 38470 + b * 7471) / 65536;
  return PixelB{gray, gray, gray, a};
}
void PixelB::RGB2Grayscale() {
  byte gray = (r * 19595 + g * 38470 + b * 7471) / 65536;
  r = g = b = gray;
}

auto PixelS::to_grayscale() -> PixelS {
  u16 gray = (r * 19595U + g * 38470U + b * 7471U) / 65536U;
  return PixelS{gray, gray, gray, a};
}
void PixelS::RGB2Grayscale() {
  u16 gray = (r * 19595U + g * 38470U + b * 7471U) / 65536U;
  r = g = b = gray;
}

auto PixelI::to_grayscale() -> PixelI {
  u32 gray = (r * 19595ULL + g * 38470ULL + b * 7471ULL) / 65536ULL;
  return PixelI{gray, gray, gray, a};
}
void PixelI::RGB2Grayscale() {
  u32 gray = (r * 19595ULL + g * 38470ULL + b * 7471ULL) / 65536ULL;
  r = g = b = gray;
}
#endif

template <BasePixelTemplate>
auto BasePixelT::to_grayscale() -> BasePixelT {
  T gray = r * (FT).299 + g * (FT).587 + b * (FT).114;
  return {gray, gray, gray, a};
}
template <BasePixelTemplate>
void BasePixelT::RGB2Grayscale() {
  T gray = r * (FT).299 + g * (FT).587 + b * (FT).114;
  r = g = b = gray;
}

template class BasePixel<u8, 255, 128, u32, f32>;
template class BasePixel<u16, 65535, 32767, u32, f32>;
template class BasePixel<u32, 4294967295, 2147483647, u64, f32>;
template class BasePixel<f32, 1, 1, f32, f32>;
template class BasePixel<f64, 1, 1, f32, f64>;

} // namespace pl2d
