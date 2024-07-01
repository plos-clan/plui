#include <c.h>
#include <cpp.hpp>
#include <define.h>
#include <pl2d.hpp>
#include <type.hpp>

namespace pl2d {

// #if BETTER_COLOR_INTERPOLATE && FAST_COLOR_INTERPOLATE
// #  warning "启用 BETTER_COLOR_INTERPOLATE 的情况下启用 FAST_COLOR_INTERPOLATE 也快不到哪去"
// #endif

template <typename T>
void color_lerp(T *buf, size_t n, T src, T dst) {
  if (buf == null || n == 0) return;
  for (size_t i = 0; i < n; i++) {
    f32 k    = (f32)i / (f32)(n - 1);
    buf[i].r = (1 - k) * src.r + k * dst.r;
    buf[i].g = (1 - k) * src.g + k * dst.g;
    buf[i].b = (1 - k) * src.b + k * dst.b;
    buf[i].a = (1 - k) * src.a + k * dst.a;
  }
}

// 我不知道这个是否真的有效
#if FAST_COLOR_INTERPOLATE && 0
template <>
void color_lerp<PixelB>(PixelB *buf, size_t n, PixelB src, PixelB dst) {
  if (buf == null || n == 0) return;
  for (size_t i = 0; i < n; i++) {
    i32 k    = i * 65536 / (i32)(n - 1);
    buf[i].r = ((65536 - k) * src.r + k * dst.r) / 65536;
    buf[i].g = ((65536 - k) * src.g + k * dst.g) / 65536;
    buf[i].b = ((65536 - k) * src.b + k * dst.b) / 65536;
    buf[i].a = ((65536 - k) * src.a + k * dst.a) / 65536;
  }
}
#endif

// 开启 BETTER_COLOR_INTERPOLATE 的情况下使用 LAB 空间进行插值
// 否则使用 RGB 空间
template <typename T>
void color_interpolate(T *buf, size_t n, T src, T dst) {
  if (buf == null || n == 0) return;
#if BETTER_COLOR_INTERPOLATE
  src.RGB2LAB();
  dst.RGB2LAB();
#endif

  color_lerp(buf, n, src, dst);

#if BETTER_COLOR_INTERPOLATE
  for (size_t i = 0; i < n; i++) {
    buf[i].LAB2RGB();
  }
#endif
}

template <typename T>
void color_hsv_interpolate(T *buf, size_t n, T src, T dst) {
  if (buf == null || n == 0) return;
  src.RGB2HSV();
  dst.RGB2HSV();

  color_lerp(buf, n, src, dst);

  for (size_t i = 0; i < n; i++) {
    buf[i].HSV2RGB();
  }
}

template <typename T>
void color_hsl_interpolate(T *buf, size_t n, T src, T dst) {
  if (buf == null || n == 0) return;
  src.RGB2HSL();
  dst.RGB2HSL();

  color_lerp(buf, n, src, dst);

  for (size_t i = 0; i < n; i++) {
    buf[i].HSL2RGB();
  }
}

template <typename T>
void color_lab_interpolate(T *buf, size_t n, T src, T dst) {
  if (buf == null || n == 0) return;
  src.RGB2LAB();
  dst.RGB2LAB();

  color_lerp(buf, n, src, dst);

  for (size_t i = 0; i < n; i++) {
    buf[i].LAB2RGB();
  }
}

template <typename T>
void color_luv_interpolate(T *buf, size_t n, T src, T dst) {
  if (buf == null || n == 0) return;
  src.RGB2LUV();
  dst.RGB2LUV();

  color_lerp(buf, n, src, dst);

  for (size_t i = 0; i < n; i++) {
    buf[i].LUV2RGB();
  }
}

#define INSTANTIATION(_name_)                                                                      \
  template void _name_(PixelB *buf, size_t n, PixelB src, PixelB dst);                             \
  template void _name_(PixelS *buf, size_t n, PixelS src, PixelS dst);                             \
  template void _name_(PixelI *buf, size_t n, PixelI src, PixelI dst);                             \
  template void _name_(PixelF *buf, size_t n, PixelF src, PixelF dst);                             \
  template void _name_(PixelD *buf, size_t n, PixelD src, PixelD dst);

INSTANTIATION(color_lerp)
INSTANTIATION(color_interpolate)
INSTANTIATION(color_hsv_interpolate)
INSTANTIATION(color_hsl_interpolate)
INSTANTIATION(color_lab_interpolate)
INSTANTIATION(color_luv_interpolate)

#undef INSTANTIATION

} // namespace pl2d
