#include <config.h>
#undef NO_STD
#define NO_STD 0
#include <cpp.hpp>
#include <define.h>
#include <pl2d.hpp>
#include <plds.hpp>
#include <plui.hpp>
#include <type.hpp>

#include <string>

extern "C" {
void abort();
}

#include "plds/base/fb.hpp"
#include "qoi.h"

extern "C" {
void next_event();
void screen_flush();
}

enum class Event : u32 {
  ScreenResize,
  MouseMove,
  ButtonDown, // 鼠标按键按下
  ButtonUp,   // 鼠标按键释放
  KeyDown,    // 键盘按键按下
  KeyUp,      // 键盘按键释放
  Scroll,     //
};

namespace plds {

// plui::Element root;

FrameBuffer    screen_fb;
pl2d::TextureB screen_tex;

// pl2d::TextureB img_tex;

pl2d::TextureB frame_tex[19];

static auto &fb  = screen_fb;
static auto &tex = screen_tex;

auto load_qoi_to_tex(const char *filename, pl2d::TextureB &tex) {
  int   img_width, img_height, img_channels;
  void *data = qoi_load(filename, &img_width, &img_height, &img_channels);
  if (data == null) abort();
  FrameBuffer img_fb;
  img_fb.width  = img_width;
  img_fb.height = img_height;
  img_fb.pixfmt = img_channels == 3 ? plds::PixFmt::RGB : plds::PixFmt::RGBA;
  img_fb.pix[0] = data;
  img_fb.init();
  img_fb.init_texture(tex);
  img_fb.copy_to(tex);
}

auto init(void *buffer, u32 width, u32 height, PixFmt fmt) -> int {
  for (int i = 0; i < 18; i++) {
    load_qoi_to_tex(("frame" + std::to_string(i) + ".qoi").c_str(), frame_tex[i]);
  }

  return on::screen_resize(buffer, width, height, fmt);
}

int nframe = 0;

void flush(bool force) {
  if (!force) nframe++;

  float        i = (f32)nframe * .01f;
  pl2d::PixelF p = {.8, cpp::cos(i) * .1f, cpp::sin(i) * .1f, 1};
  p.LAB2RGB();
  tex.fill(tex.size_rect(), p);
  // img_tex.paste_to(tex, 20, 20);
  frame_tex[nframe / 60 % 19].paste_to(tex, 20, 20);
  fb.flush(tex);
  screen_flush();
}

void deinit() {
  tex = {};
}

} // namespace plds

namespace plds::on {

// 屏幕大小重设
auto screen_resize(void *buffer, u32 width, u32 height, PixFmt fmt) -> int {
  if (fb.ready) fb.reset();
  fb.pix[0] = buffer;
  fb.pixfmt = fmt;
  fb.width  = width;
  fb.height = height;
  fb.init();
  if (!fb.ready) return 1; // 初始化失败

  fb.init_texture(tex);
  if (!tex.ready()) return 1; // 初始化失败

  return 0;
}
// 鼠标移动
void mouse_move(i32 x, i32 y) {}
// 鼠标按键按下
void button_down(i32 button, i32 x, i32 y) {}
// 鼠标按键释放
void button_up(i32 button, i32 x, i32 y) {}
// 键盘按键按下
void key_down(i32 key) {}
// 键盘按键释放
void key_up(i32 key) {
  if (key == event::Escape) program_exit();
}
// 鼠标滚轮，nrows 表示内容可见区域向下 N 行
void scroll(i32 nrows) {}

} // namespace plds::on
