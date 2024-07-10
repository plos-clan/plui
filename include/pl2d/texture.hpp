#pragma once
#include "pixel.hpp"
#include "points/rect.hpp"
#include "type.hpp"

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
  BaseTexture(const BaseTexture &) = delete; // 隐式地复制是不允许的
  BaseTexture(BaseTexture &&) noexcept;
  ~BaseTexture();
  auto operator=(const BaseTexture &) -> BaseTexture & = delete; // 隐式地复制是不允许的
  auto operator=(BaseTexture &&) noexcept -> BaseTexture &;

  auto reset() -> BaseTexture &;

  auto ready() const -> bool {
    return pixels != null;
  }

  // 使用运算符访问不进行安全检查
  auto operator[](i32 y) const -> const T * {
    return &pixels[y * pitch];
  }
  auto operator[](i32 y) -> T * {
    return &pixels[y * pitch];
  }
  auto operator()(i32 x, i32 y) const -> const T & {
    return pixels[y * pitch + x];
  }
  auto operator()(i32 x, i32 y) -> T & {
    return pixels[y * pitch + x];
  }
  // 不进行安全检查
  auto pix(ssize_t i) const -> const T & {
    return pixels[i];
  }
  auto pix(ssize_t i) -> T & {
    return pixels[i];
  }
  auto pix(i32 x, i32 y) const -> const T & {
    return pixels[y * pitch + x];
  }
  auto pix(i32 x, i32 y) -> T & {
    return pixels[y * pitch + x];
  }
  // 进行安全检查
  auto at(ssize_t i) const -> const T & {
    i = cpp::clamp(i, (ssize_t)0, (ssize_t)size - 1);
    return pixels[i];
  }
  auto at(ssize_t i) -> T & {
    i = cpp::clamp(i, (ssize_t)0, (ssize_t)size - 1);
    return pixels[i];
  }
  auto at(i32 x, i32 y) const -> const T & {
    cpp::clamp(x, 0, (i32)width - 1);
    cpp::clamp(y, 0, (i32)height - 1);
    return pixels[y * pitch + x];
  }
  auto at(i32 x, i32 y) -> T & {
    cpp::clamp(x, 0, (i32)width - 1);
    cpp::clamp(y, 0, (i32)height - 1);
    return pixels[y * pitch + x];
  }

  // 获取与 texture 一样大的 rect
  auto size_rect() const -> Rect {
    return {0, 0, (i32)width - 1, (i32)height - 1};
  }

  auto copy() -> BaseTexture *;
  template <typename T2>
  auto copy_to(BaseTexture<T2> &d) const -> bool {
    return d.copy_from(*this);
  }
  template <typename T2>
  auto copy_from(const BaseTexture<T2> &d) -> bool;

  auto clear() -> BaseTexture &;

  auto get(i32 x, i32 y) -> T &;
  auto get(i32 x, i32 y) const -> const T &;
  auto get(i32 x, i32 y, T &p) -> BaseTexture &;
  auto get(i32 x, i32 y, T &p) const -> const BaseTexture &;
  auto set(i32 x, i32 y, const T &p) -> BaseTexture &;
  auto set(i32 x, i32 y, u32 c) -> BaseTexture &;
  auto set(i32 x, i32 y, byte r, byte g, byte b) -> BaseTexture &;
  auto set(i32 x, i32 y, byte r, byte g, byte b, byte a) -> BaseTexture &;
  auto set(i32 x, i32 y, f32 r, f32 g, f32 b) -> BaseTexture &;
  auto set(i32 x, i32 y, f32 r, f32 g, f32 b, f32 a) -> BaseTexture &;

  auto fft() -> BaseTexture &;
  auto ift() -> BaseTexture &;

  //% 缩放 resize会创建新对象 resize_to不会创建新对象
  auto resize_to(float s) -> BaseTexture &;      // 缩放到 s 倍
  auto resize_to(u32 w, u32 h) -> BaseTexture &; // 缩放到指定大小
  auto resize(float s) -> BaseTexture *;         // 缩放到 s 倍
  auto resize(u32 w, u32 h) -> BaseTexture *;    // 缩放到指定大小

  //% 纹理内置的简单绘图函数

  // 绘制线条
  auto line(i32 x1, i32 y1, i32 x2, i32 y2, const T &color) -> BaseTexture &;
  auto line_mix(i32 x1, i32 y1, i32 x2, i32 y2, const T &color) -> BaseTexture &;
  // 填充区域
  auto fill(const T &color) -> BaseTexture &;
  auto fill(RectI rect, const T &color) -> BaseTexture &;
  auto fill_mix(RectI rect, const T &color) -> BaseTexture &;
  // 绘制图片
  auto paste_from(const BaseTexture &tex, i32 x, i32 y) -> BaseTexture &;
  auto paste_to(BaseTexture &tex, i32 x, i32 y) -> BaseTexture &;
  auto paste_to(BaseTexture &tex, i32 x, i32 y) const -> const BaseTexture &;
  auto paste_from_mix(const BaseTexture &tex, i32 x, i32 y) -> BaseTexture &;
  auto paste_to_mix(BaseTexture &tex, i32 x, i32 y) -> BaseTexture &;
  auto paste_to_mix(BaseTexture &tex, i32 x, i32 y) const -> const BaseTexture &;
  // 转换颜色
  auto replace(const T &src, const T dst) -> BaseTexture &;
  auto transform(void (*cb)(T &pix)) -> BaseTexture &;
  auto transform(void (*cb)(T &pix, i32 x, i32 y)) -> BaseTexture &;
  // 未实现
  void trangle();
  void polygon();
};

using TextureB = BaseTexture<PixelB>;
using TextureS = BaseTexture<PixelS>;
using TextureF = BaseTexture<PixelF>;
using TextureD = BaseTexture<PixelD>;
using Texture  = TextureB;

} // namespace pl2d
