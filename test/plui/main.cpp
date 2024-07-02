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

// 屏幕大小重设
extern void on_screen_resize(i32 width, i32 height);
// 鼠标移动
extern void on_mouse_move(i32 x, i32 y);
// 鼠标按下
extern void on_button_down(i32 button, i32 x, i32 y);
// 鼠标释放
extern void on_button_up(i32 button, i32 x, i32 y);
//
extern void on_key_down(i32 key);
//
extern void on_key_up(i32 key);
//
extern void on_scroll(i32 nrows);

enum class Event : u32 {
  ScreenResize,
  MouseMove,
  ButtonDown, // 鼠标按键按下
  ButtonUp,   // 鼠标按键释放
  KeyDown,    // 键盘按键按下
  KeyUp,      // 键盘按键释放
  Scroll,     //
};

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
