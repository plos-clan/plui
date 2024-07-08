#include <c.h>
#include <pl2d.hpp>

namespace pl2d {

template <typename T>
auto BaseTexture<T>::paste_from(const BaseTexture<T> &tex, i32 dx, i32 dy) -> BaseTexture & {
  Rect rect = {(i32)tex.width, (i32)tex.height};
  rect.trunc((i32)width - dx, (i32)height - dy);
  for (const auto [x, y] : rect) {
    at(x + dx, y + dy) = tex.at(x, y);
  }
  return *this;
}

template <typename T>
auto BaseTexture<T>::paste_to(BaseTexture &tex, i32 x, i32 y) -> BaseTexture & {
  tex.paste_from(*this, x, y);
  return *this;
}

template <typename T>
auto BaseTexture<T>::paste_to(BaseTexture &tex, i32 x, i32 y) const -> const BaseTexture & {
  tex.paste_from(*this, x, y);
  return *this;
}

template <typename T>
auto BaseTexture<T>::paste_from_mix(const BaseTexture<T> &tex, i32 dx, i32 dy) -> BaseTexture & {
  Rect rect = {(i32)tex.width, (i32)tex.height};
  rect.trunc((i32)width - dx, (i32)height - dy);
  for (const auto [x, y] : rect) {
    at(x + dx, y + dy).mix(tex.at(x, y));
  }
  return *this;
}

template <typename T>
auto BaseTexture<T>::paste_to_mix(BaseTexture &tex, i32 x, i32 y) -> BaseTexture & {
  tex.paste_from(*this, x, y);
  return *this;
}

template <typename T>
auto BaseTexture<T>::paste_to_mix(BaseTexture &tex, i32 x, i32 y) const -> const BaseTexture & {
  tex.paste_from(*this, x, y);
  return *this;
}

template class BaseTexture<PixelB>;
template class BaseTexture<PixelF>;

} // namespace pl2d
