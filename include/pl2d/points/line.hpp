#pragma once
#include "../point.hpp"
#include "rect.hpp"
#include <define.h>
#include <type.hpp>

namespace pl2d {

template <typename T>
struct BaseLine {
  T x1 = 0, y1 = 0;
  T x2 = 0, y2 = 0;

  BaseLine()                                         = default;
  BaseLine(const BaseLine &)                         = default;
  BaseLine(BaseLine &&) noexcept                     = default;
  auto operator=(const BaseLine &) -> BaseLine     & = default;
  auto operator=(BaseLine &&) noexcept -> BaseLine & = default;

  auto translate(T x, T y) -> BaseLine & {
    x1 += x;
    x2 += x;
    y1 += y;
    y2 += y;
    return *this;
  }

  auto rect() -> BaseRect<T> {
    return {x1, y1, x2, y2};
  }

  // 如果线段完全在 rect 外部，返回 false
  auto clamp(const BaseRect<T> &rect) -> bool;
  auto clamp(const BaseRect<T> &rect, BaseLine &l) const -> bool;
};

using LineI = BaseLine<i32>;
using LineF = BaseLine<f32>;
using LineD = BaseLine<f64>;
using Line  = RectI;

} // namespace pl2d
