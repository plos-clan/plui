#pragma once
#include <define.h>
#include <type.h>

// --------------------------------------------------
//; clz

#ifndef __cplusplus
#  define F32_EPSILON 1e-5f
#  define F64_EPSILON 1e-10
#endif

#if __has(clz)
#  define clz(x)                                                                                   \
    _Generic((x),                                                                                  \
        unsigned char: __builtin_clzs((ushort)(x)) - 8,                                            \
        unsigned short: __builtin_clzs(x),                                                         \
        unsigned int: __builtin_clz(x),                                                            \
        unsigned long: __builtin_clzl(x),                                                          \
        unsigned long long: __builtin_clzll(x))
#else
#  define __(TYPE, NAME)                                                                           \
    static int _##NAME(TYPE x) {                                                                   \
      int  count = 0;                                                                              \
      TYPE mask  = (TYPE)1 << (sizeof(TYPE) - 1);                                                  \
      for (; mask && (x & mask) == 0; count++, mask = mask >> 1) {}                                \
      return count;                                                                                \
    }
__(ushort, clzs)
__(uint, clz)
__(ulong, clzl)
__(ullong, clzll)
#  undef __
#  define clz(x)                                                                                   \
    _Generic((x),                                                                                  \
        unsigned char: _clzs((ushort)(x)) - 8,                                                     \
        unsigned short: _clzs(x),                                                                  \
        unsigned int: _clz(x),                                                                     \
        unsigned long: _clzl(x),                                                                   \
        unsigned long long: _clzll(x))
#endif

// --------------------------------------------------
//; bit_reverse

finline u8 bit_reverse_8(u8 x) {
  x = ((x & 0x55) << 1) | ((x >> 1) & 0x55);
  x = ((x & 0x33) << 2) | ((x >> 2) & 0x33);
  x = ((x & 0x0f) << 4) | ((x >> 4) & 0x0f);
  return x;
}
finline u16 bit_reverse_16(u16 x) {
  x = ((x & 0x5555) << 1) | ((x >> 1) & 0x5555);
  x = ((x & 0x3333) << 2) | ((x >> 2) & 0x3333);
  x = ((x & 0x0f0f) << 4) | ((x >> 4) & 0x0f0f);
  x = ((x & 0x00ff) << 8) | ((x >> 8) & 0x00ff);
  return x;
}
finline u32 bit_reverse_32(u32 x) {
  x = ((x & 0x55555555) << 1) | ((x >> 1) & 0x55555555);
  x = ((x & 0x33333333) << 2) | ((x >> 2) & 0x33333333);
  x = ((x & 0x0f0f0f0f) << 4) | ((x >> 4) & 0x0f0f0f0f);
  x = ((x & 0x00ff00ff) << 8) | ((x >> 8) & 0x00ff00ff);
  x = (x << 16) | (x >> 16);
  return x;
}
finline u64 bit_reverse_64(u64 x) {
  x = ((x & 0x5555555555555555) << 1) | ((x >> 1) & 0x5555555555555555);
  x = ((x & 0x3333333333333333) << 2) | ((x >> 2) & 0x3333333333333333);
  x = ((x & 0x0f0f0f0f0f0f0f0f) << 4) | ((x >> 4) & 0x0f0f0f0f0f0f0f0f);
  x = ((x & 0x00ff00ff00ff00ff) << 8) | ((x >> 8) & 0x00ff00ff00ff00ff);
  x = ((x & 0x0000ffff0000ffff) << 16) | ((x >> 16) & 0x0000ffff0000ffff);
  x = (x << 32) | (x >> 32);
  return x;
}
#define bit_reverse(x)                                                                             \
  _Generic((x),                                                                                    \
      u8: bit_reverse_8(x),                                                                        \
      u16: bit_reverse_16(x),                                                                      \
      u32: bit_reverse_32(x),                                                                      \
      u64: bit_reverse_64(x))

//* ----------------------------------------------------------------------------------------------------
//; 标准库的
//* ----------------------------------------------------------------------------------------------------

#if NO_STD

// --------------------------------------------------
//; 求和

// --------------------------------------------------
//; 平均数

// --------------------------------------------------
//;

finline int abs(int x) {
  return x >= 0 ? x : -x;
}

finline double fmod(double x, double y) {
  return x - (long)(x / y) * y;
}

finline float fmodf(float x, float y) {
  return x - (int)(x / y) * y;
}

// --------------------------------------------------
//; 平方根 立方根

finline float cbrtf(float x) {
  bool neg = x < 0;
  if (neg) x = -x;
  float guess = .6;
  guess       = (2 * guess + x / (guess * guess)) / 3;
  guess       = (2 * guess + x / (guess * guess)) / 3;
  guess       = (2 * guess + x / (guess * guess)) / 3;
  guess       = (2 * guess + x / (guess * guess)) / 3;
  guess       = (2 * guess + x / (guess * guess)) / 3;
  return neg ? -guess : guess;
}
finline double cbrt(double x) {
  bool neg = x < 0;
  if (neg) x = -x;
  double guess = .6;
  guess        = (2 * guess + x / (guess * guess)) / 3;
  guess        = (2 * guess + x / (guess * guess)) / 3;
  guess        = (2 * guess + x / (guess * guess)) / 3;
  guess        = (2 * guess + x / (guess * guess)) / 3;
  guess        = (2 * guess + x / (guess * guess)) / 3;
  return neg ? -guess : guess;
}

finline float sqrtf(float x) {
  x           = x < 0 ? -x : x;
  float guess = .6;
  guess       = (guess + x / guess) / 2;
  guess       = (guess + x / guess) / 2;
  guess       = (guess + x / guess) / 2;
  guess       = (guess + x / guess) / 2;
  guess       = (guess + x / guess) / 2;
  return guess;
}

finline double sqrt(double x) {
  x            = x < 0 ? -x : x;
  double guess = .6;
  guess        = (guess + x / guess) / 2;
  guess        = (guess + x / guess) / 2;
  guess        = (guess + x / guess) / 2;
  guess        = (guess + x / guess) / 2;
  guess        = (guess + x / guess) / 2;
  return guess;
}

// --------------------------------------------------
//; 对数 指数

finline f32 exp2f(f32 x) {
  f32 y;
  i32 e;
  e   = (i32)(x + 127);
  x  += 127 - e;
  e <<= 23;
  y   = *(f32 *)&e;
  x  *= x * .339766027f + .660233972f;
  return (x + 1) * y;
}

finline f32 log2f(f32 x) {
  i32 y;
  f32 r;
  y   = *(i32 *)&x;
  y >>= 23;
  r   = (f32)y;
  y   = *(i32 *)&x;
  y   = (y & 0x007fffff) | 0x3f800000;
  x   = *(f32 *)&y;
  r  += -128 + x * (x * -0.333333333f + 2) - 0.666666666f;
  return r;
}

finline f64 exp2(f64 x) {
  f64 y;
  i64 e;
  e   = (i64)(x + 1023);
  x  += 1023 - e;
  e <<= 52;
  y   = *(f64 *)&e;
  x  *= x * .339766027 + .660233972;
  return (x + 1) * y;
}

finline f64 log2(f64 x) {
  i64 y;
  f64 r;
  y   = *(i64 *)&x;
  y >>= 52;
  r   = (f64)y;
  y   = *(i64 *)&x;
  y   = (y & 0x000fffffffffffff) | 0x3ff0000000000000;
  x   = *(f64 *)&y;
  r  += -1024 + x * (x * -0.3333333333333333 + 2) - 0.6666666666666666;
  return r;
}

finline float powf(float a, float b) {
  return exp2f(b * log2f(a));
}

finline float pow(float a, float b) {
  return exp2(b * log2(a));
}

#endif

//* ----------------------------------------------------------------------------------------------------
//; 自定义的
//* ----------------------------------------------------------------------------------------------------

// --------------------------------------------------
//; 最大最小

finline int min(int a, int b) {
  return a < b ? a : b;
}

finline int max(int a, int b) {
  return a > b ? a : b;
}

// --------------------------------------------------
//; 平方 立方

finline int square(int x) {
  return x * x;
}

finline float squaref(float x) {
  return x * x;
}

finline int cube(int x) {
  return x * x * x;
}

finline float cubef(float x) {
  return x * x * x;
}

// --------------------------------------------------
//;

finline int gcd(int a, int b) {
  while (b != 0) {
    int t = b;
    b     = a % b;
    a     = t;
  }
  return a;
}

finline long gcdl(long a, long b) {
  while (b != 0) {
    long t = b;
    b      = a % b;
    a      = t;
  }
  return a;
}

finline u64 factorial(uint n) {
  u64 result = 1;
  for (uint i = 2; i <= n; i++) {
    result *= i;
  }
  return result;
}
