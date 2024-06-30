#pragma once
#include <c.h>
#include <cpp.hpp>
#include <define.h>
#include <pl2d.hpp>
#include <type.hpp>

namespace plds {

enum class PixFmt : u32 {
  BlackWhite, // 黑白双色
  Grayscale8, // 8位灰度
  Palette16,  // 16色调色板
  Palette256, // 256色调色板

  RGB565, //
  BGR565, //

  // 24位真彩色
  RGB888,
  RGB = RGB888,
  BGR888,
  BGR = BGR888,
  // 32位真彩色
  RGBA8888,
  RGBA = RGBA8888,
  BGRA8888,
  BGRA = BGRA8888,
  ARGB8888,
  ARGB = ARGB8888,
  ABGR8888,
  ABGR = ABGR8888,

  // 通道分离
  RGB_Plane,
  RGBA_Plane,
};

enum class PalFmt : u32 {
  None,

  // 24位真彩色
  RGB888,
  RGB = RGB888,
  BGR888,
  BGR = BGR888,
  // 32位真彩色
  RGBA8888,
  RGBA = RGBA8888,
  BGRA8888,
  BGRA = BGRA8888,
  ARGB8888,
  ARGB = ARGB8888,
  ABGR8888,
  ABGR = ABGR8888,

  // 通道分离
  RGB_Plane,
  RGBA_Plane,
};

struct FrameBuffer {
  union {
    void *pix[4] = {};
    u8   *pix8[4];
    u16  *pix16[4];
    u32  *pix32[4];
    struct {
      byte *plane1;
      byte *plane2;
      byte *plane3;
      byte *plane4;
    };
  };                             // 缓冲区，由内核分配
  u32   *pal     = null;         //
  u32    width   = 0;            // 宽度（可自动计算） width = pitch / size_of_pixel
  u32    height  = 0;            // 高度
  u32    pitch   = 0;            // pitch = width * size_of_pixel
  u32    size    = 0;            //
  u16    bpp     = 0;            // 像素深度（可自动计算） size_of_pixel * 8
  u8     padding = 0;            //
  u8     channel = 0;            //
  PixFmt pixfmt  = PixFmt::RGBA; // 像素格式
  PalFmt palfmt  = PalFmt::None; // 像素格式
  bool   alpha   = false;        // 是否有alpha通道（可自动计算）
  bool   plane   = false;        // 是否通道分离
  bool   ready   = false;        //
  void (*cb_flushed)();

  FrameBuffer()                        = default;
  FrameBuffer(const FrameBuffer &)     = default;
  FrameBuffer(FrameBuffer &&) noexcept = default;

  auto init() -> int; // 返回 0: 正常，<0:异常

  void clear();       // 全部数据清零
  void clear(byte b); // 全部数据清零

  // rect 是要更新的区域
  auto flush(const pl2d::TextureB &tex) -> int;
  auto flush(const pl2d::TextureF &tex) -> int;
  auto flush(const pl2d::TextureB &tex, const pl2d::Rect &rect) -> int;
  auto flush(const pl2d::TextureF &tex, const pl2d::Rect &rect) -> int;

  auto copy_to(pl2d::TextureB &tex) const -> int;
  auto copy_to(pl2d::TextureF &tex) const -> int;
  auto copy_to(pl2d::TextureB &tex, const pl2d::Rect &rect) const -> int;
  auto copy_to(pl2d::TextureF &tex, const pl2d::Rect &rect) const -> int;
};

} // namespace plds
