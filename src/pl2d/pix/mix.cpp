#include <cpp.hpp>
#include <define.h>
#include <pl2d.hpp>
#include <type.hpp>

namespace pl2d {

//* ----------------------------------------------------------------------------------------------------
//; mix
//* ----------------------------------------------------------------------------------------------------

template <BasePixelTemplate>
void BasePixelT::mix(const BasePixelT &s) {
  T2 _a = (T2)v_max * (a + s.a) - a * s.a;
  T2 sw = (T2)v_max * s.a;
  T2 dw = a * ((T2)v_max - s.a);
  r     = (r * dw + s.r * sw) / _a;
  g     = (g * dw + s.g * sw) / _a;
  b     = (b * dw + s.b * sw) / _a;
  a     = _a / v_max;
}

template <BasePixelTemplate>
auto BasePixelT::mix(const BasePixelT &c1, const BasePixelT &c2) -> BasePixelT {
  T2 _a = (T2)v_max * (c1.a + c2.a) - c1.a * c2.a;
  T2 w1 = (T2)v_max * c1.a;
  T2 w2 = (T2)v_max * c2.a;
  return BasePixelT{
      (T)((c1.r * w1 + c2.r * w2) / _a),
      (T)((c1.g * w1 + c2.g * w2) / _a),
      (T)((c1.b * w1 + c2.b * w2) / _a),
      (T)(_a / v_max),
  };
}

template class BasePixel<u8, 255, 128, u32, f32>;
template class BasePixel<u16, 65535, 32767, u32, f32>;
template class BasePixel<u32, 4294967295, 2147483647, u64, f32>;
template class BasePixel<f32, 1, 1, f32, f32>;
template class BasePixel<f64, 1, 1, f32, f64>;

} // namespace pl2d
