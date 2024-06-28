#include "pl2d/point.hpp"
#include <pl2d.hpp>

#include <cstring>

namespace pl2d {

//* ----------------------------------------------------------------------------------------------------
//; BaseTexture
//* ----------------------------------------------------------------------------------------------------

template <typename T>
BaseTexture<T>::BaseTexture(u32 width, u32 height)
    : width(width), height(height), pitch(width), size(width * height) {
  own_pixels   = true;
  alloced_size = size;
  pixels       = (T *)malloc(size * sizeof(T));
}

template <typename T>
BaseTexture<T>::BaseTexture(u32 width, u32 height, u32 pitch)
    : width(width), height(height), pitch(pitch), size(pitch * height) {
  own_pixels   = true;
  alloced_size = size;
  pixels       = (T *)malloc(size * sizeof(T));
}

template <typename T>
BaseTexture<T>::BaseTexture(T *pixels, u32 width, u32 height)
    : width(width), height(height), pitch(width), size(width * height) {
  this->pixels = pixels;
}

template <typename T>
BaseTexture<T>::BaseTexture(T *pixels, u32 width, u32 height, u32 pitch)
    : width(width), height(height), pitch(pitch), size(pitch * height) {
  this->pixels = pixels;
}

template <typename T>
BaseTexture<T>::~BaseTexture() {
  if (own_pixels) free(pixels);
}

template <typename T>
auto BaseTexture<T>::copy() -> BaseTexture<T> * {
  auto *d = new BaseTexture<T>(width, height, pitch);
  if (d == null) return null;
  d->copy_from(*this);
  return d;
}

template <typename T>
auto BaseTexture<T>::copy_to(BaseTexture<T> &d) const -> bool {
  return d.copy_from(*this);
}

template <typename T>
auto BaseTexture<T>::copy_from(const BaseTexture<T> &d) -> bool {
  if (&d == this) return true;
  if (d.width != width || d.height != height) return false;
  if (d.pitch == pitch) {
    memcpy(pixels, d.pixels, size * sizeof(T));
    return true;
  }
  for (u32 i = 0; i < height; i++) {
    memcpy(&pixels[i * pitch], &d.pixels[i * d.pitch], width * sizeof(T));
  }
  return true;
}

template <typename T>
auto BaseTexture<T>::clear() -> BaseTexture<T> & {
  // 重置为透明
  memset(pixels, 0, size * sizeof(T));
  return *this;
}

template <typename T>
void BaseTexture<T>::line(i32 x1, i32 y1, i32 x2, i32 y2, const T &color) {
  for (const auto p : ItPoint2I(x1, y1, x2, y2)) {
    set(p.x, p.y, color);
  }
}

//* ----------------------------------------------------------------------------------------------------
//; TextureB
//* ----------------------------------------------------------------------------------------------------

auto TextureB::set(size_t x, size_t y, byte r, byte g, byte b) -> TextureB & {
  pixels[y * pitch + x] = {r, g, b, 255};
  return *this;
}

auto TextureB::set(size_t x, size_t y, byte r, byte g, byte b, byte a) -> TextureB & {
  pixels[y * pitch + x] = {r, g, b, a};
  return *this;
}

auto TextureB::set(size_t x, size_t y, f32 r, f32 g, f32 b) -> TextureB & {
  pixels[y * pitch + x] = PixelF{r, g, b, 1}.to_u8();
  return *this;
}

auto TextureB::set(size_t x, size_t y, f32 r, f32 g, f32 b, f32 a) -> TextureB & {
  pixels[y * pitch + x] = PixelF{r, g, b, a}.to_u8();
  return *this;
}

//* ----------------------------------------------------------------------------------------------------
//; TextureF
//* ----------------------------------------------------------------------------------------------------

auto TextureF::set(size_t x, size_t y, byte r, byte g, byte b) -> TextureF & {
  pixels[y * pitch + x] = PixelB{r, g, b, 255}.to_f32();
  return *this;
}

auto TextureF::set(size_t x, size_t y, byte r, byte g, byte b, byte a) -> TextureF & {
  pixels[y * pitch + x] = PixelB{r, g, b, a}.to_f32();
  return *this;
}

auto TextureF::set(size_t x, size_t y, f32 r, f32 g, f32 b) -> TextureF & {
  pixels[y * pitch + x] = {r, g, b, 1};
  return *this;
}

auto TextureF::set(size_t x, size_t y, f32 r, f32 g, f32 b, f32 a) -> TextureF & {
  pixels[y * pitch + x] = {r, g, b, a};
  return *this;
}

} // namespace pl2d
