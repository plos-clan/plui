#include <pl2d.hpp>

#include <cstring>

namespace pl2d {

// --------------------------------------------------
//. 简单的绘图函数

template <typename T>
auto BaseTexture<T>::replace(const T &src, const T dst) -> BaseTexture & {
  for (const auto [x, y] : size_rect()) {
    if (at(x, y) == src) at(x, y) = dst;
  }
  return *this;
}

template <typename T>
auto BaseTexture<T>::transform(void (*cb)(T &pix)) -> BaseTexture & {
  for (const auto [x, y] : size_rect()) {
    cb(at(x, y));
  }
  return *this;
}

template <typename T>
auto BaseTexture<T>::transform(void (*cb)(T &pix, i32 x, i32 y)) -> BaseTexture & {
  for (const auto [x, y] : size_rect()) {
    cb(at(x, y), x, y);
  }
  return *this;
}

template <typename T>
auto BaseTexture<T>::line(i32 x1, i32 y1, i32 x2, i32 y2, const T &color) -> BaseTexture & {
  for (const auto [x, y] : ItPoint2I(x1, y1, x2, y2)) {
    at(x, y) = color;
  }
  return *this;
}

template <typename T>
auto BaseTexture<T>::line_mix(i32 x1, i32 y1, i32 x2, i32 y2, const T &color) -> BaseTexture & {
  for (const auto [x, y] : ItPoint2I(x1, y1, x2, y2)) {
    at(x, y).mix(color);
  }
  return *this;
}

template <typename T>
auto BaseTexture<T>::fill(const T &color) -> BaseTexture & {
  for (const auto [x, y] : size_rect()) {
    at(x, y) = color;
  }
  return *this;
}

template <typename T>
auto BaseTexture<T>::fill(RectI rect, const T &color) -> BaseTexture & {
  for (const auto [x, y] : rect) {
    at(x, y) = color;
  }
  return *this;
}

template <typename T>
auto BaseTexture<T>::fill_mix(RectI rect, const T &color) -> BaseTexture & {
  for (const auto [x, y] : rect) {
    at(x, y).mix(color);
  }
  return *this;
}

template class BaseTexture<PixelB>;
template class BaseTexture<PixelF>;

} // namespace pl2d
