#include <pl2d.hpp>

#include <cstring>

namespace pl2d {

// --------------------------------------------------
//. 简单的绘图函数

template <typename T>
void BaseTexture<T>::line(i32 x1, i32 y1, i32 x2, i32 y2, const T &color) {
  for (const auto [x, y] : ItPoint2I(x1, y1, x2, y2)) {
    at(x, y) = color;
  }
}

template <typename T>
void BaseTexture<T>::line_mix(i32 x1, i32 y1, i32 x2, i32 y2, const T &color) {
  for (const auto [x, y] : ItPoint2I(x1, y1, x2, y2)) {
    at(x, y).mix(color);
  }
}

template <typename T>
void BaseTexture<T>::fill(const T &color) {
  for (const auto [x, y] : size_rect()) {
    at(x, y) = color;
  }
}

template <typename T>
void BaseTexture<T>::fill(RectI rect, const T &color) {
  for (const auto [x, y] : rect) {
    at(x, y) = color;
  }
}

template <typename T>
void BaseTexture<T>::fill_mix(RectI rect, const T &color) {
  for (const auto [x, y] : rect) {
    at(x, y).mix(color);
  }
}

template class BaseTexture<PixelB>;
template class BaseTexture<PixelF>;

} // namespace pl2d
