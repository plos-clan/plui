#pragma once
#include "pixel.hpp"

namespace pl2d {

template <typename T>
struct BaseTexture {
  T   *pixels       = null;  // 储存实际分配的大小 像素数而不是字节数
  bool own_pixels   = false; // pixels 是否为该结构体所有
  u32  width        = 0;     // 宽度
  u32  height       = 0;     // 高度
  u32  pitch        = 0;     // 每行实际的像素数
  u32  size         = 0;     // 储存 height * pitch 而不是占用的字节数
  u32  alloced_size = 0;     // 实际分配的内存 pixels数

  BaseTexture() = default;
  BaseTexture(u32 width, u32 height);
  BaseTexture(u32 width, u32 height, u32 pitch);
  BaseTexture(T *pixels, u32 width, u32 height);
  BaseTexture(T *pixels, u32 width, u32 height, u32 pitch);
  BaseTexture(const BaseTexture &)     = delete;
  BaseTexture(BaseTexture &&) noexcept = default;
  ~BaseTexture();

  auto ready() const -> bool {
    return pixels != null;
  }

  auto operator[](size_t y) const -> const T * {
    return &pixels[y * pitch];
  }
  auto operator[](size_t y) -> T * {
    return &pixels[y * pitch];
  }
  auto operator()(size_t x, size_t y) const -> const T & {
    return pixels[y * pitch + x];
  }
  auto operator()(size_t x, size_t y) -> T & {
    return pixels[y * pitch + x];
  }

  auto copy() -> BaseTexture *;
  auto copy_to(BaseTexture &d) const -> bool;
  auto copy_from(const BaseTexture &d) -> bool;

  auto clear() -> BaseTexture &;
  auto get(size_t x, size_t y) const -> const T {
    return pixels[y * pitch + x];
  }
  auto get(size_t x, size_t y, T &p) -> BaseTexture & {
    p = pixels[y * pitch + x];
    return *this;
  }
  auto get(size_t x, size_t y, T &p) const -> const BaseTexture & {
    p = pixels[y * pitch + x];
    return *this;
  }
  auto set(size_t x, size_t y, const T &p) -> BaseTexture & {
    pixels[y * pitch + x] = p;
    return *this;
  }

  // 纹理内置的简单绘图函数
  void line(i32 x1, i32 y1, i32 x2, i32 y2, const T &color);
};

struct TextureB : BaseTexture<PixelB> {
  using BaseTexture<PixelB>::BaseTexture;

  auto copy() -> TextureB * {
    return (TextureB *)BaseTexture<PixelB>::copy();
  }

  using BaseTexture<PixelB>::set;
  auto set(size_t x, size_t y, byte r, byte g, byte b) -> TextureB &;
  auto set(size_t x, size_t y, byte r, byte g, byte b, byte a) -> TextureB &;
  auto set(size_t x, size_t y, f32 r, f32 g, f32 b) -> TextureB &;
  auto set(size_t x, size_t y, f32 r, f32 g, f32 b, f32 a) -> TextureB &;

  auto resize(float s) -> TextureB &;            // 缩放到 s 倍
  auto resize(size_t w, size_t h) -> TextureB &; // 缩放到指定大小

  void trangle();
  void polygon();
};

struct TextureF : BaseTexture<PixelF> {
  using BaseTexture<PixelF>::BaseTexture;

  auto copy() -> TextureF * {
    return (TextureF *)BaseTexture<PixelF>::copy();
  }

  using BaseTexture<PixelF>::set;
  auto set(size_t x, size_t y, byte r, byte g, byte b) -> TextureF &;
  auto set(size_t x, size_t y, byte r, byte g, byte b, byte a) -> TextureF &;
  auto set(size_t x, size_t y, f32 r, f32 g, f32 b) -> TextureF &;
  auto set(size_t x, size_t y, f32 r, f32 g, f32 b, f32 a) -> TextureF &;
};

} // namespace pl2d
