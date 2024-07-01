#pragma once
#include "../point.hpp"
#include "col.hpp"
#include "row.hpp"
#include <define.h>
#include <type.hpp>

namespace pl2d {

template <typename T>
struct BaseRect {
  T x1 = 0, y1 = 0; // 左上角坐标
  T x2 = 0, y2 = 0; // 右下角坐标

  BaseRect() = default;
  BaseRect(T x1, T y1, T x2, T y2) {
    cpp::exch_if(x1 > x2, x1, x2);
    cpp::exch_if(y1 > y2, y1, y2);
    this->x1 = x1, this->y1 = y1;
    this->x2 = x2, this->y2 = y2;
  }
  BaseRect(const BaseRect &)     = default;
  BaseRect(BaseRect &&) noexcept = default;

  auto size() -> size_t {
    return (x2 - x1 + 1) * (y2 - y1 + 1);
  }

  auto translate(T x, T y) -> BaseRect & {
    x1 += x;
    x2 += x;
    y1 += y;
    y2 += y;
    return *this;
  }

  auto topleft() -> BasePoint2<T> {
    return {x1, y1};
  }
  auto topright() -> BasePoint2<T> {
    return {x1, y2};
  }
  auto bottomleft() -> BasePoint2<T> {
    return {x2, y1};
  }
  auto bottomright() -> BasePoint2<T> {
    return {x2, y2};
  }

  void contain(T x, T y) {
    x1 = cpp::min(x1, x);
    y1 = cpp::min(y1, y);
    x2 = cpp::max(x2, x);
    y2 = cpp::max(y2, y);
  }
  void contain(const BasePoint2<T> &p) {
    contain(p.x, p.y);
  }

  auto contains(T x, T y) -> bool {
    if (x < x1 || x > x2) return false;
    if (y < y1 || y > y2) return false;
    return true;
  }
  auto contains(const BasePoint2<T> &p) -> bool {
    return contains(p.x, p.y);
  }
};

using RectI = BaseRect<i32>;
using RectF = BaseRect<f32>;
using RectD = BaseRect<f64>;
using Rect  = RectI;

class ItRectI : RectI {
public:
  ItRectI(const RectI &r) : RectI(r.x1, r.y1, r.x2, r.y2) {}

  class Iterator {
  private:
    i32 x1, x2, y1, y2;

  public:
    Iterator(i32 x1, i32 x2, i32 y1, i32 y2) : x1(x1), x2(x2), y1(y1), y2(y2) {}

    auto operator*() -> ItRowI {
      return {x1, x2, y1};
    }

    auto operator++() -> Iterator & {
      y1++;
      return *this;
    }

    auto operator==(const Iterator &it) const -> bool {
      return y1 == it.y1;
    }

    auto operator!=(const Iterator &it) const -> bool {
      return y1 != it.y1;
    }
  };

  auto begin() const -> Iterator {
    return {x1, x2, y1, y2};
  }

  auto end() const -> Iterator {
    return {x1, x2, y2 + 1, y2};
  }
};

} // namespace pl2d
