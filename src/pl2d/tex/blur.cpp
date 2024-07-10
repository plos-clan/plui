#include <c.h>
#include <cpp.hpp>
#include <define.h>
#include <pl2d.hpp>
#include <type.hpp>

namespace pl2d {

// float gaussian_kernel_5[5] = {0.06136, 0.24477, 0.38774, 0.24477, 0.06136};

// 一维高斯模糊卷积核
void gaussian_kernel_1(f32 *kernel, i32 size, f32 sigma) {
  i32 center = size / 2;
  f32 sum    = 0;
  f32 k      = -1 / (2 * sigma * sigma);
  for (i32 i = 0; i < size; i++) {
    const i32 x  = i - center;
    kernel[i]    = cpp::exp((x * x) * k);
    sum         += kernel[i];
  }
  for (i32 i = 0; i < size; i++) {
    kernel[i] /= sum;
  }
}

// 二维高斯模糊卷积核
void gaussian_kernel_2(f32 *kernel, i32 size, f32 sigma) {
  i32 center = size / 2;
  f32 sum    = 0;
  f32 k      = -1 / (2 * sigma * sigma);
  for (i32 i = 0; i < size; i++) {
    for (i32 j = 0; j < size; j++) {
      const i32 x = i - center, y = j - center;
      kernel[i * size + j]  = cpp::exp((x * x + y * y) * k);
      sum                  += kernel[i * size + j];
    }
  }
  for (i32 i = 0; i < size * size; i++) {
    kernel[i] /= sum;
  }
}

} // namespace pl2d
