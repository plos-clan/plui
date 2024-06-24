#include <pl2d.hpp>

#include <cstring>

namespace pl2d {

Texture::Texture(u32 width, u32 height)
    : width(width), height(height), pitch(width), size(width * height) {
  own_pixels   = true;
  alloced_size = size;
  pixels       = (Pixel *)malloc(size * sizeof(Pixel));
}

Texture::Texture(u32 width, u32 height, u32 pitch)
    : width(width), height(height), pitch(pitch), size(pitch * height) {
  own_pixels   = true;
  alloced_size = size;
  pixels       = (Pixel *)malloc(size * sizeof(Pixel));
}

Texture::Texture(Pixel *pixels, u32 width, u32 height)
    : width(width), height(height), pitch(width), size(width * height) {
  this->pixels = pixels;
}

Texture::Texture(Pixel *pixels, u32 width, u32 height, u32 pitch)
    : width(width), height(height), pitch(pitch), size(pitch * height) {
  this->pixels = pixels;
}

Texture::~Texture() {
  if (own_pixels) free(pixels);
}

auto Texture::copy() -> Texture * {
  auto *d = new Texture(width, height, pitch);
  if (d == null) return null;
  d->copy_from(*this);
  return d;
}

auto Texture::copy_to(Texture &d) const -> bool {
  return d.copy_from(*this);
}

auto Texture::copy_from(const Texture &d) -> bool {
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

auto Texture::clear() -> Texture & {
  // 重置为透明
  memset(pixels, 0, size * sizeof(Pixel));
  return *this;
}

auto Texture::get(size_t x, size_t y) const -> const Pixel {
  return pixels[y * pitch + x];
}

auto Texture::set(size_t x, size_t y, const Pixel &p) -> Texture & {
  pixels[y * pitch + x] = p;
  return *this;
}

auto Texture::set(size_t x, size_t y, byte r, byte g, byte b) -> Texture & {
  pixels[y * pitch + x] = {r, g, b, 255};
  return *this;
}

auto Texture::set(size_t x, size_t y, byte r, byte g, byte b, byte a) -> Texture & {
  pixels[y * pitch + x] = {r, g, b, a};
  return *this;
}

auto Texture::set(size_t x, size_t y, float r, float g, float b) -> Texture & {
  pixels[y * pitch + x] = PixelF{r, g, b, 1}.to_u8();
  return *this;
}

auto Texture::set(size_t x, size_t y, float r, float g, float b, float a) -> Texture & {
  pixels[y * pitch + x] = PixelF{r, g, b, a}.to_u8();
  return *this;
}

} // namespace pl2d
