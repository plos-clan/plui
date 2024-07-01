#include <cpp.hpp>
#include <define.h>
#include <pl2d.hpp>
#include <plds.hpp>
#include <type.hpp>

extern "C" {
void next_event();
void screen_flush();
auto test_main(void *buffer, u32 width, u32 height) -> int;
}

auto test_main(void *buffer, u32 width, u32 height) -> int {
  plds::FrameBuffer fb;
  fb.pix[0] = buffer;
  fb.pixfmt = plds::PixFmt::BGRA;
  fb.width  = width;
  fb.height = height;
  fb.init();

  if (!fb.ready) return 1; // 初始化失败

  pl2d::TextureB tex;
  fb.init_texture(tex);

  byte i = 0;

  while (1) {
    next_event();
    pl2d::PixelB p = {i++, 255, 255, 255};
    p.HSV2RGB();
    tex.fill(tex.size_rect(), p);
    fb.flush(tex);
    screen_flush();
  }

  return 0;
}
