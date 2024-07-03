#include <cpp.hpp>
#include <define.h>
#include <pl2d.hpp>
#include <plds.hpp>
#include <type.hpp>

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

static plds::FrameBuffer fb;
static pl2d::TextureB    tex;

namespace plds {

void flush() {
  static float i  = 0;
  pl2d::PixelF p  = {.8, cpp::cos(i) * .1f, cpp::sin(i) * .1f, 1};
  i              += .01;
  p.LAB2RGB();
  // printf("%f %f %f\n", p.r, p.g, p.b);
  tex.fill(tex.size_rect(), 0xff00ffff);
  fb.flush(tex);
  screen_flush();
}

void deinit() {}

} // namespace plds

namespace plds::on {

// 屏幕大小重设
auto screen_resize(void *buffer, u32 width, u32 height) -> int {
  if (fb.ready) fb.reset();
  fb.pix[0] = buffer;
  fb.pixfmt = plds::PixFmt::BGRA;
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
