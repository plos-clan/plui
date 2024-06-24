
#include <c/error.h>
#include <type.hpp>

namespace plui::server {

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
  RGB_Plane,
  // 32位真彩色
  RGBA8888,
  RGBA = RGBA8888,
  BGRA8888,
  BGRA = BGRA8888,
  RGBA_Plane,
};

struct FrameBuffer {
  byte  *buf[4];        // 缓冲区，由内核分配
  u32    width  = 0;    // 宽度（可自动计算） width = pitch / size_of_pixel
  u32    height = 0;    // 高度
  u32    pitch  = 0;    // pitch = width * size_of_pixel
  u32    size   = 0;    //
  u16    bpp;           // 像素深度（可自动计算） size_of_pixel * 8
  u16    padding = 0;   //
  PixFmt fmt;           // 像素格式
  bool   alpha = false; // 是否有alpha通道（可自动计算）
  bool   plane = false;
  bool   ready = false;

  // 返回 0: 正常，-1:异常
  auto init() -> int {
    if (ready) return 0;

    if (fmt == PixFmt::BlackWhite) ERROR(1, "暂不支持");

    auto old_bpp = bpp;
    switch (fmt) {
    case PixFmt::BlackWhite: bpp = 1; break;
    case PixFmt::Grayscale8: bpp = 8; break;
    case PixFmt::Palette16: bpp = 4; break;
    case PixFmt::Palette256: bpp = 8; break;
    case PixFmt::RGB565:
    case PixFmt::BGR565: bpp = 16; break;
    case PixFmt::RGB888:
    case PixFmt::BGR888: bpp = 24; break;
    case PixFmt::RGBA8888:
    case PixFmt::BGRA8888: bpp = 32; break;
    default: ERROR(1, "未知的像素格式");
    }
    if (old_bpp > 0 && bpp != old_bpp) ERROR(1, "bpp 与 fmt 不匹配");

    // 计算pitch
    if (pitch == 0) pitch = (width * bpp + 7) / 8;
    if (pitch == 0) ERROR(1, "pitch 与 width 不能同时为 0");

    // 计算width
    if (width == 0) width = pitch * 8 / bpp;
    if (width == 0) ERROR(1, "pitch 与 width 不能同时为 0");

    // 计算size
    u32 _size = pitch * height;
    if (size == 0) size = _size;
    if (size != _size) ERROR(1, "size 变量的大小与计算值不同");
  }
};

void FrameBuffer_init(FrameBuffer *fb, uint32_t width, uint32_t height, PixFmt fmt) {

  // 计算每个像素的字节数

  fb->pitch = fb->width * (fb->bpp / 8);
  fb->alpha = (fmt == PixFmt::RGBA8888 || fmt == PixFmt::BGRA8888);
  fb->plane = false;

  // 分配缓冲区内存
  for (int i = 0; i < 4; i++) {
    fb->buf[i] = nullptr;
  }
  fb->buf[0] = new byte[fb->pitch * fb->height];
}

} // namespace plui::server
