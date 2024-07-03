#include <cpp.hpp>
#include <define.h>
#include <pl2d.hpp>
#include <type.hpp>

namespace pl2d {

template <BasePixelTemplate>
void BasePixelT::mix(const BasePixelT &s) {
  T2 _a = (T2)T_MAX * (a + s.a) - a * s.a;
  T2 sw = (T2)T_MAX * s.a;
  T2 dw = a * ((T2)T_MAX - s.a);
  r     = (r * dw + s.r * sw) / _a;
  g     = (g * dw + s.g * sw) / _a;
  b     = (b * dw + s.b * sw) / _a;
  a     = _a / T_MAX;
}

template <BasePixelTemplate>
auto BasePixelT::mix(const BasePixelT &c1, const BasePixelT &c2) -> BasePixelT {
  T2 _a = (T2)T_MAX * (c1.a + c2.a) - c1.a * c2.a;
  T2 w1 = (T2)T_MAX * c1.a;
  T2 w2 = (T2)T_MAX * c2.a;
  return BasePixelT{
      (T)((c1.r * w1 + c2.r * w2) / _a),
      (T)((c1.g * w1 + c2.g * w2) / _a),
      (T)((c1.b * w1 + c2.b * w2) / _a),
      (T)(_a / T_MAX),
  };
}

template class BasePixelBT;
template class BasePixelST;
template class BasePixelIT;
template class BasePixelFT;
template class BasePixelDT;

} // namespace pl2d
