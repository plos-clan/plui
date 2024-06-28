#pragma once
#include "point.hpp"
#include <define.h>
#include <type.hpp>

namespace pl2d {

template <typename T>
struct BaseRow {
  T x = 0, y1 = 0, y2 = 0;

  BaseRow(T x, T y1, T y2) : x(x) {
    cpp::exch_if(y1 > y2, y1, y2);
    this->y1 = y1, this->y2 = y2;
  }

  auto left() -> BasePoint2<T> {
    return {x, y1};
  }
  auto right() -> BasePoint2<T> {
    return {x, y2};
  }
};

template <typename T>
struct BaseCol {
  T x1 = 0, x2 = 0, y = 0;

  BaseCol(T x1, T x2, T y) : y(y) {
    cpp::exch_if(x1 > x2, x1, x2);
    this->x1 = x1, this->x2 = x2;
  }

  auto left() -> BasePoint2<T> {
    return {x1, y};
  }
  auto right() -> BasePoint2<T> {
    return {x2, y};
  }
};

template <typename T>
struct BaseRect {
  T x1 = 0, y1 = 0; // 左上角坐标
  T x2 = 0, y2 = 0; // 右下角坐标

  BaseRect(T x1, T y1, T x2, T y2) {
    cpp::exch_if(x1 > x2, x1, x2);
    cpp::exch_if(y1 > y2, y1, y2);
    this->x1 = x1, this->y1 = y1;
    this->x2 = x2, this->y2 = y2;
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
};

using RowI = BaseRow<i32>;
using RowF = BaseRow<f32>;
using RowD = BaseRow<f64>;
using Row  = RowI;

using ColI = BaseCol<i32>;
using ColF = BaseCol<f32>;
using ColD = BaseCol<f64>;
using Col  = ColI;

using RectI = BaseRect<i32>;
using RectF = BaseRect<f32>;
using RectD = BaseRect<f64>;
using Rect  = RectI;

class ItRowI : RowI {
public:
  class Iterator {
  private:
    bool ended = false;
    i32;

  public:
    Iterator() : ended(true) {}
    Iterator(Point2I p1, Point2I p2) {
      x1 = p1.x;
      y1 = p1.y;
      x2 = p2.x;
      y2 = p2.y;

      dx  = cpp::abs(x2 - x1);
      dy  = cpp::abs(y2 - y1);
      sx  = (x1 < x2) ? 1 : -1;
      sy  = (y1 < y2) ? 1 : -1;
      err = dx - dy;
    }

    auto operator*() -> Point2I {
      return {x1, y1};
    }

    auto operator++() -> Iterator & {
      if (ended) return *this;
      if (x1 == x2 && y1 == y2) {
        ended = true;
        return *this;
      }

      if (2 * err > -dy) {
        err -= dy;
        x1  += sx;
      }
      if (2 * err < dx) {
        err += dx;
        y1  += sy;
      }
      return *this;
    }

    auto operator==(const Iterator &other) const -> bool {
      return ended == other.ended;
    }

    auto operator!=(const Iterator &other) const -> bool {
      return ended != other.ended;
    }
  };

  auto begin() const -> Iterator {
    return {p1, p2};
  }

  auto end() const -> Iterator {
    return {};
  }
};

class ItRectI : RectI {
public:
  class Iterator {
  private:
    bool ended = false;
    i32  x1, y1, x2, y2;
    i32  dx, dy, sx, sy, err;

  public:
    Iterator() : ended(true) {}
    Iterator(Point2I p1, Point2I p2) {
      x1 = p1.x;
      y1 = p1.y;
      x2 = p2.x;
      y2 = p2.y;

      dx  = cpp::abs(x2 - x1);
      dy  = cpp::abs(y2 - y1);
      sx  = (x1 < x2) ? 1 : -1;
      sy  = (y1 < y2) ? 1 : -1;
      err = dx - dy;
    }

    auto operator*() -> Point2I {
      return {x1, y1};
    }

    auto operator++() -> Iterator & {
      if (ended) return *this;
      if (x1 == x2 && y1 == y2) {
        ended = true;
        return *this;
      }

      if (2 * err > -dy) {
        err -= dy;
        x1  += sx;
      }
      if (2 * err < dx) {
        err += dx;
        y1  += sy;
      }
      return *this;
    }

    auto operator==(const Iterator &other) const -> bool {
      return ended == other.ended;
    }

    auto operator!=(const Iterator &other) const -> bool {
      return ended != other.ended;
    }
  };

  auto begin() const -> Iterator {
    return {p1, p2};
  }

  auto end() const -> Iterator {
    return {};
  }
};

} // namespace pl2d
