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
//; 构造
//* ----------------------------------------------------------------------------------------------------

template <BasePixelTemplate>
BasePixelT::BasePixel(u32 c) {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
  byte r = c, g = c >> 8, b = c >> 16, a = c >> 24;
#else
  byte r = c >> 24, g = c >> 16, b = c >> 8, a;
#endif
  if constexpr (std::is_floating_point_v<T>) {
    this->r = r / (T)255;
    this->g = g / (T)255;
    this->b = b / (T)255;
    this->a = a / (T)255;
  } else {
    this->r = (u64)r * v_max / 255;
    this->g = (u64)g * v_max / 255;
    this->b = (u64)b * v_max / 255;
    this->a = (u64)a * v_max / 255;
  }
}

template <BasePixelTemplate>
template <_BasePixelTemplate>
BasePixelT::BasePixel(const _BasePixelT &p) {
  if constexpr (v_max == v_max_2 && _v_max == _v_max_2) {
    r = p.r, g = p.g, b = p.b, a = p.a;
  } else if constexpr (v_max == v_max_2 && _v_max != _v_max_2) {
    r = p.r / (T)_v_max, g = p.g / (T)_v_max, b = p.b / (T)_v_max, a = p.a / (T)_v_max;
  } else if constexpr (v_max != v_max_2 && _v_max == _v_max_2) {
    r = p.r * (FT)v_max, g = p.g * (FT)v_max, b = p.b * (FT)v_max, a = p.a * (FT)v_max;
  } else {
    r = (u64)p.r * v_max / _v_max, g = (u64)p.g * v_max / _v_max;
    b = (u64)p.b * v_max / _v_max, a = (u64)p.a * v_max / _v_max;
  }
}

template BasePixelBT::BasePixel(const BasePixelST &);
template BasePixelBT::BasePixel(const BasePixelIT &);
template BasePixelBT::BasePixel(const BasePixelFT &);
template BasePixelBT::BasePixel(const BasePixelDT &);
template BasePixelST::BasePixel(const BasePixelBT &);
template BasePixelST::BasePixel(const BasePixelIT &);
template BasePixelST::BasePixel(const BasePixelFT &);
template BasePixelST::BasePixel(const BasePixelDT &);
template BasePixelIT::BasePixel(const BasePixelBT &);
template BasePixelIT::BasePixel(const BasePixelST &);
template BasePixelIT::BasePixel(const BasePixelFT &);
template BasePixelIT::BasePixel(const BasePixelDT &);
template BasePixelFT::BasePixel(const BasePixelBT &);
template BasePixelFT::BasePixel(const BasePixelST &);
template BasePixelFT::BasePixel(const BasePixelIT &);
template BasePixelFT::BasePixel(const BasePixelDT &);
template BasePixelDT::BasePixel(const BasePixelBT &);
template BasePixelDT::BasePixel(const BasePixelST &);
template BasePixelDT::BasePixel(const BasePixelIT &);
template BasePixelDT::BasePixel(const BasePixelFT &);

template <BasePixelTemplate>
auto BasePixelT::to_u8() const -> PixelB {
  return *this;
}
template <BasePixelTemplate>
auto BasePixelT::to_u16() const -> PixelS {
  return *this;
}
template <BasePixelTemplate>
auto BasePixelT::to_u32() const -> PixelI {
  return *this;
}
template <BasePixelTemplate>
auto BasePixelT::to_f32() const -> PixelF {
  return *this;
}
template <BasePixelTemplate>
auto BasePixelT::to_f64() const -> PixelD {
  return *this;
}

template class BasePixelBT;
template class BasePixelST;
template class BasePixelIT;
template class BasePixelFT;
template class BasePixelDT;

} // namespace pl2d
