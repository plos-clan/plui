#pragma once
#include "pixel.hpp"

namespace pl2d {

struct Texture;

struct Texture {
  Pixel *pixels       = null;  // 储存实际分配的大小 像素数而不是字节数
  bool   own_pixels   = false; // pixels 是否为该结构体所有
  u32    width        = 0;     // 宽度
  u32    height       = 0;     // 高度
  u32    pitch        = 0;     // 每行实际的像素数
  u32    size         = 0;     // 储存 height * pitch 而不是占用的字节数
  u32    alloced_size = 0;     // 实际分配的内存 pixels数

  Texture() = default;
  Texture(u32 width, u32 height);
  Texture(u32 width, u32 height, u32 pitch);
  Texture(Pixel *pixels, u32 width, u32 height);
  Texture(Pixel *pixels, u32 width, u32 height, u32 pitch);
  Texture(const Texture &) = delete;
  Texture(Texture &&)      = default;
  ~Texture();

  auto ready() const -> bool {
    return pixels != null;
  }

  auto operator[](size_t y) const -> const Pixel * {
    return &pixels[y * pitch];
  }
  auto operator[](size_t y) -> Pixel * {
    return &pixels[y * pitch];
  }
  auto operator()(size_t x, size_t y) const -> const Pixel & {
    return pixels[y * pitch + x];
  }
  auto operator()(size_t x, size_t y) -> Pixel & {
    return pixels[y * pitch + x];
  }

  auto copy() -> Texture *;
  auto copy_to(Texture &d) const -> bool;
  auto copy_from(const Texture &d) -> bool;

  auto clear() -> Texture &;
  auto get(size_t x, size_t y) const -> const Pixel;
  auto set(size_t x, size_t y, const Pixel &p) -> Texture &;
  auto set(size_t x, size_t y, byte r, byte g, byte b) -> Texture &;
  auto set(size_t x, size_t y, byte r, byte g, byte b, byte a) -> Texture &;
  auto set(size_t x, size_t y, float r, float g, float b) -> Texture &;
  auto set(size_t x, size_t y, float r, float g, float b, float a) -> Texture &;

  void line();
  void trangle();
  void polygon();
};

} // namespace pl2d
