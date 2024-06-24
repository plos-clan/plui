#include "pl2d/drawable.hpp"
#include "pl2d/pixel.hpp"
#include <pl2d.hpp>

#include <cstring>

namespace pl2d {

Drawable::Drawable(u32 width, u32 height)
    : width(width), height(height), pitch(width), size(width * height) {
  own_pixels   = true;
  alloced_size = size;
  pixels       = (Pixel *)malloc(size * sizeof(Pixel));
}

Drawable::Drawable(u32 width, u32 height, u32 pitch)
    : width(width), height(height), pitch(pitch), size(pitch * height) {
  own_pixels   = true;
  alloced_size = size;
  pixels       = (Pixel *)malloc(size * sizeof(Pixel));
}

Drawable::Drawable(Pixel *pixels, u32 width, u32 height)
    : width(width), height(height), pitch(width), size(width * height) {
  this->pixels = pixels;
}

Drawable::Drawable(Pixel *pixels, u32 width, u32 height, u32 pitch)
    : width(width), height(height), pitch(pitch), size(pitch * height) {
  this->pixels = pixels;
}

Drawable::~Drawable() {
  if (own_pixels) free(pixels);
}

auto Drawable::copy() -> Drawable * {
  auto *d = new Drawable(width, height, pitch);
  if (d == null) return null;
  d->copy_from(*this);
  return d;
}

auto Drawable::copy_to(Drawable &d) const -> bool {
  return d.copy_from(*this);
}

auto Drawable::copy_from(const Drawable &d) -> bool {
  if (&d == this) return true;
  if (d.width != width || d.height != height) return false;
  if (d.pitch == pitch) {
    memcpy(pixels, d.pixels, size * sizeof(Pixel));
    return true;
  }
  for (u32 i = 0; i < height; i++) {
    memcpy(&pixels[i * pitch], &d.pixels[i * d.pitch], width * sizeof(Pixel));
  }
  return true;
}

auto Drawable::clear() -> Drawable & {
  // 重置为透明
  memset(pixels, 0, size * sizeof(Pixel));
  return *this;
}

auto Drawable::get(size_t x, size_t y) const -> const Pixel {
  return pixels[y * pitch + x];
}

auto Drawable::set(size_t x, size_t y, const Pixel &p) -> Drawable & {
  pixels[y * pitch + x] = p;
  return *this;
}

auto Drawable::set(size_t x, size_t y, byte r, byte g, byte b) -> Drawable & {
  pixels[y * pitch + x] = {r, g, b, 255};
  return *this;
}

auto Drawable::set(size_t x, size_t y, byte r, byte g, byte b, byte a) -> Drawable & {
  pixels[y * pitch + x] = {r, g, b, a};
  return *this;
}

auto Drawable::set(size_t x, size_t y, float r, float g, float b) -> Drawable & {
  pixels[y * pitch + x] = PixelF{r, g, b, 1}.to_u8();
  return *this;
}

auto Drawable::set(size_t x, size_t y, float r, float g, float b, float a) -> Drawable & {
  pixels[y * pitch + x] = PixelF{r, g, b, a}.to_u8();
  return *this;
}

} // namespace pl2d
