#include <plds/base.hpp>

#include "fb.hpp"
using namespace plds::framebuffer;

namespace plds {

auto FrameBuffer::init() -> int {
  if (ready) return 0;

  if (pixfmt == PixFmt::BlackWhite) ERROR(1, "暂不支持");

  auto old_bpp = bpp;
  switch (pixfmt) {
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

void FrameBuffer::clear() {
  for (auto &k : pix8) {
    if (k == null) continue;
    for (u32 i = 0; i < size; i++) {
      k[i] = 0;
    }
  }
}

void FrameBuffer::clear(byte b) {
  for (auto &k : pix8) {
    if (k == null) continue;
    for (u32 i = 0; i < size; i++) {
      k[i] = b;
    }
  }
}

} // namespace plds
