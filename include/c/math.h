#pragma once
#include <define.h>
#include <type.h>

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
