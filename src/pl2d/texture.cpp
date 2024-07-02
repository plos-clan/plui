#include <c.h>
#include <pl2d.hpp>

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
BaseTexture<T>::BaseTexture(BaseTexture &&tex) noexcept {
  pixels           = tex.pixels;
  own_pixels       = tex.own_pixels;
  width            = tex.width;
  height           = tex.height;
  pitch            = tex.pitch;
  size             = tex.size;
  alloced_size     = tex.alloced_size;
  tex.pixels       = null;
  tex.own_pixels   = false;
  tex.width        = 0;
  tex.height       = 0;
  tex.pitch        = 0;
  tex.size         = 0;
  tex.alloced_size = 0;
}

template <typename T>
auto BaseTexture<T>::operator=(BaseTexture &&tex) noexcept -> BaseTexture & {
  if (this == &tex) return *this;
  this->~BaseTexture();
  pixels           = tex.pixels;
  own_pixels       = tex.own_pixels;
  width            = tex.width;
  height           = tex.height;
  pitch            = tex.pitch;
  size             = tex.size;
  alloced_size     = tex.alloced_size;
  tex.pixels       = null;
  tex.own_pixels   = false;
  tex.width        = 0;
  tex.height       = 0;
  tex.pitch        = 0;
  tex.size         = 0;
  tex.alloced_size = 0;
  return *this;
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
auto BaseTexture<T>::get(i32 x, i32 y) -> T & {
  cpp::clamp(x, 0, (i32)width - 1);
  cpp::clamp(y, 0, (i32)height - 1);
  return pixels[y * pitch + x];
}
template <typename T>
auto BaseTexture<T>::get(i32 x, i32 y) const -> const T & {
  cpp::clamp(x, 0, (i32)width - 1);
  cpp::clamp(y, 0, (i32)height - 1);
  return pixels[y * pitch + x];
}
template <typename T>
auto BaseTexture<T>::get(i32 x, i32 y, T &p) -> BaseTexture & {
  cpp::clamp(x, 0, (i32)width - 1);
  cpp::clamp(y, 0, (i32)height - 1);
  p = pixels[y * pitch + x];
  return *this;
}
template <typename T>
auto BaseTexture<T>::get(i32 x, i32 y, T &p) const -> const BaseTexture & {
  cpp::clamp(x, 0, (i32)width - 1);
  cpp::clamp(y, 0, (i32)height - 1);
  p = pixels[y * pitch + x];
  return *this;
}
template <typename T>
auto BaseTexture<T>::set(i32 x, i32 y, const T &p) -> BaseTexture & {
  cpp::clamp(x, 0, (i32)width - 1);
  cpp::clamp(y, 0, (i32)height - 1);
  pixels[y * pitch + x] = p;
  return *this;
}

template class BaseTexture<PixelB>;
template class BaseTexture<PixelF>;

//* ----------------------------------------------------------------------------------------------------
//; TextureB
//* ----------------------------------------------------------------------------------------------------

auto TextureB::set(i32 x, i32 y, byte r, byte g, byte b) -> TextureB & {
  pixels[y * pitch + x] = {r, g, b, 255};
  return *this;
}

auto TextureB::set(i32 x, i32 y, byte r, byte g, byte b, byte a) -> TextureB & {
  pixels[y * pitch + x] = {r, g, b, a};
  return *this;
}

auto TextureB::set(i32 x, i32 y, f32 r, f32 g, f32 b) -> TextureB & {
  pixels[y * pitch + x] = PixelF{r, g, b, 1}.to_u8();
  return *this;
}

auto TextureB::set(i32 x, i32 y, f32 r, f32 g, f32 b, f32 a) -> TextureB & {
  pixels[y * pitch + x] = PixelF{r, g, b, a}.to_u8();
  return *this;
}

//* ----------------------------------------------------------------------------------------------------
//; TextureF
//* ----------------------------------------------------------------------------------------------------

auto TextureF::set(i32 x, i32 y, byte r, byte g, byte b) -> TextureF & {
  pixels[y * pitch + x] = PixelB{r, g, b, 255}.to_f32();
  return *this;
}

auto TextureF::set(i32 x, i32 y, byte r, byte g, byte b, byte a) -> TextureF & {
  pixels[y * pitch + x] = PixelB{r, g, b, a}.to_f32();
  return *this;
}

auto TextureF::set(i32 x, i32 y, f32 r, f32 g, f32 b) -> TextureF & {
  pixels[y * pitch + x] = {r, g, b, 1};
  return *this;
}

auto TextureF::set(i32 x, i32 y, f32 r, f32 g, f32 b, f32 a) -> TextureF & {
  pixels[y * pitch + x] = {r, g, b, a};
  return *this;
}

} // namespace pl2d
