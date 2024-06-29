#pragma once
#include <define.h>
#include <type.hpp>

namespace cpp {

constexpr f64 PI = 3.14159265358979323846264338327950288;
constexpr f64 E  = 2.718281828459045235360287;

// --------------------------------------------------
//; 最大最小

template <typename T>
auto min(T x) -> T {
  return x;
}
template <typename T, typename... Args>
auto min(T x, Args... args) -> T {
  T y = min(args...);
  return x < y ? x : y;
}

template <typename T>
auto max(T x) -> T {
  return x;
}
template <typename T, typename... Args>
auto max(T x, Args... args) -> T {
  T y = max(args...);
  return x > y ? x : y;
}

template <typename T>
auto clamp(const T &v, const T &min, const T &max) -> const T & {
  if (v < min) return min;
  if (v > max) return max;
  return v;
}

// --------------------------------------------------
//; 求和

template <typename T>
auto sum(T x) -> T {
  return x;
}
template <typename T, typename... Args>
auto sum(T x, Args... args) -> T {
  T y = sum(args...);
  return x + y;
}

template <typename T>
auto sumi(T x) -> int {
  return x;
}
template <typename T, typename... Args>
auto sumi(T x, Args... args) -> int {
  int y = sumi(args...);
  return x + y;
}

template <typename T>
auto suml(T x) -> long {
  return x;
}
template <typename T, typename... Args>
auto suml(T x, Args... args) -> long {
  long y = sumi(args...);
  return x + y;
}

template <typename T>
auto sumf(T x) -> float {
  return x;
}
template <typename T, typename... Args>
auto sumf(T x, Args... args) -> float {
  float y = sumf(args...);
  return x + y;
}

template <typename T>
auto sumd(T x) -> double {
  return x;
}
template <typename T, typename... Args>
auto sumd(T x, Args... args) -> double {
  double y = sumd(args...);
  return x + y;
}

// --------------------------------------------------
//; 平均数

template <typename T, typename... Args>
auto avg(T x, Args... args) -> T {
  return sum(args...) / sizeof...(args);
}

template <typename T, typename... Args>
auto avgf(T x, Args... args) -> float {
  return sumf(args...) / (float)sizeof...(args);
}

template <typename T, typename... Args>
auto avgd(T x, Args... args) -> double {
  return sumd(args...) / (double)sizeof...(args);
}

// --------------------------------------------------
//;

template <typename T>
auto abs(T x) -> T {
  return x >= 0 ? x : -x;
}

template <typename T>
auto gcd(T a, T b) -> T {
  while (b != 0) {
    T t = b;
    b   = a % b;
    a   = t;
  }
  return a;
}

template <typename T>
auto lcm(T a, T b) -> T {
  return a / gcd(a, b) * b;
}

#if __has_builtin(fmod)
auto mod(f32 x, f32 y) -> f32 {
  return __builtin_fmodf(x, y);
}
auto mod(f64 x, f64 y) -> f64 {
  return __builtin_fmod(x, y);
}
#else
auto fmod(f32 x, f32 y) -> f32 {
  return x - (i32)(x / y) * y;
}
auto fmod(f64 x, f64 y) -> f64 {
  return x - (i64)(x / y) * y;
}
#endif

// --------------------------------------------------
//; 平方 立方 平方根 立方根

template <typename T>
auto square(T x) -> T {
  return x * x;
}

template <typename T>
auto cube(T x) -> T {
  return x * x * x;
}

#if __has_builtin(sqrt)
finline auto sqrt(float x) -> float {
  return __builtin_sqrtf(x);
}
finline auto sqrt(double x) -> double {
  return __builtin_sqrt(x);
}
finline auto sqrt(i32 x) -> float {
  return sqrt((float)x);
}
finline auto sqrt(u32 x) -> float {
  return sqrt((float)x);
}
finline auto sqrt(i64 x) -> double {
  return sqrt((double)x);
}
finline auto sqrt(u64 x) -> double {
  return sqrt((double)x);
}
#else
auto sqrt(float x) -> float {
  x           = x < 0 ? -x : x;
  float guess = .6;
  guess       = (guess + x / guess) / 2;
  guess       = (guess + x / guess) / 2;
  guess       = (guess + x / guess) / 2;
  guess       = (guess + x / guess) / 2;
  guess       = (guess + x / guess) / 2;
  return guess;
}
auto sqrt(double x) -> double {
  x            = x < 0 ? -x : x;
  double guess = .6;
  guess        = (guess + x / guess) / 2;
  guess        = (guess + x / guess) / 2;
  guess        = (guess + x / guess) / 2;
  guess        = (guess + x / guess) / 2;
  guess        = (guess + x / guess) / 2;
  return guess;
}
finline auto sqrt(i32 x) -> float {
  return sqrt((float)x);
}
finline auto sqrt(u32 x) -> float {
  return sqrt((float)x);
}
finline auto sqrt(i64 x) -> double {
  return sqrt((double)x);
}
finline auto sqrt(u64 x) -> double {
  return sqrt((double)x);
}
#endif

#if __has_builtin(cbrt)
finline auto cbrt(float x) -> float {
  return __builtin_cbrtf(x);
}
finline auto cbrt(double x) -> double {
  return __builtin_cbrt(x);
}
#else
auto cbrt(float x) -> float {
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
auto cbrt(double x) -> double {
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
#endif

// --------------------------------------------------
//; 对数 指数

#if __has_builtin(exp2)
auto exp2(f32 x) -> f32 {
  return __builtin_exp2f(x);
}
auto exp2(f64 x) -> f64 {
  return __builtin_exp2(x);
}
#else
auto exp2(f32 x) -> f32 {
  f32 y;
  i32 e;
  e   = (i32)(x + 127);
  x  += 127 - e;
  e <<= 23;
  y   = *(f32 *)&e;
  x  *= x * .339766027f + .660233972f;
  return (x + 1) * y;
}
auto exp2(f64 x) -> f64 {
  f64 y;
  i64 e;
  e   = (i64)(x + 1023);
  x  += 1023 - e;
  e <<= 52;
  y   = *(f64 *)&e;
  x  *= x * .339766027 + .660233972;
  return (x + 1) * y;
}
#endif

#if __has_builtin(exp)
auto exp(f32 x) -> f32 {
  return __builtin_expf(x);
}
auto exp(f64 x) -> f64 {
  return __builtin_exp(x);
}
#else
auto exp(f32 x) -> f32 {}
auto exp(f64 x) -> f64 {}
#endif

#if __has_builtin(log2)
auto log2(f32 x) -> f32 {
  return __builtin_log2f(x);
}
auto log2(f64 x) -> f64 {
  return __builtin_log2(x);
}
#else
auto log2(f32 x) -> f32 {
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
auto log2(f64 x) -> f64 {
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
#endif

auto pow(f32 a, u32 b) -> f32 {
  f32 r = 1;
  while (b > 0) {
    if (b & 1) r *= a;
    a  *= a;
    b >>= 1;
  }
  return r;
}

auto pow(f32 a, i32 b) -> f32 {
  return b < 0 ? 1 / pow(a, (u32)-b) : pow(a, (u32)b);
}

auto pow(i32 a, u32 b) -> i32 {
  i32 r = 1;
  while (b > 0) {
    if (b & 1) r *= a;
    a  *= a;
    b >>= 1;
  }
  return r;
}

auto pow(f64 a, u64 b) -> f64 {
  f64 r = 1;
  while (b > 0) {
    if (b & 1) r *= a;
    a  *= a;
    b >>= 1;
  }
  return r;
}

auto pow(f64 a, i64 b) -> f64 {
  return b < 0 ? 1 / pow(a, (u64)-b) : pow(a, (u64)b);
}

auto pow(i64 a, u64 b) -> i64 {
  i64 r = 1;
  while (b > 0) {
    if (b & 1) r *= a;
    a  *= a;
    b >>= 1;
  }
  return r;
}

#if __has_builtin(pow)
auto pow(f32 a, f32 b) -> f32 {
  return __builtin_powf(a, b);
}
auto pow(f64 a, f64 b) -> f64 {
  return __builtin_pow(a, b);
}
#else
auto pow(f32 a, f32 b) -> f32 {
  return __builtin_powf(a, b);
  i32 c  = b;
  b     -= c;
  return exp2(b * log2(a)) * pow(a, c);
}
auto pow(f64 a, f64 b) -> f64 {
  return __builtin_pow(a, b);
  i64 c  = b;
  b     -= c;
  return exp2(b * log2(a)) * pow(a, c);
}
#endif

// --------------------------------------------------
//; 三角函数

#if __has_builtin(sin)
auto sin(f32 x) -> f32 {
  return __builtin_sinf(x);
}
auto sin(f64 x) -> f64 {
  return __builtin_sin(x);
}
#else
#  error "函数未实现，去催开发者"
#endif

#if __has_builtin(cos)
auto cos(f32 x) -> f32 {
  return __builtin_cosf(x);
}
auto cos(f64 x) -> f64 {
  return __builtin_cos(x);
}
#else
#  error "函数未实现，去催开发者"
#endif

#if __has_builtin(tan)
auto tan(f32 x) -> f32 {
  return __builtin_tanf(x);
}
auto tan(f64 x) -> f64 {
  return __builtin_tan(x);
}
#else
#  error "函数未实现，去催开发者"
#endif

#if __has_builtin(asin)
auto asin(f32 x) -> f32 {
  return __builtin_asinf(x);
}
auto asin(f64 x) -> f64 {
  return __builtin_asin(x);
}
#else
#  error "函数未实现，去催开发者"
#endif

#if __has_builtin(acos)
auto acos(f32 x) -> f32 {
  return __builtin_acosf(x);
}
auto acos(f64 x) -> f64 {
  return __builtin_acos(x);
}
#else
#  error "函数未实现，去催开发者"
#endif

#if __has_builtin(atan)
auto atan(f32 x) -> f32 {
  return __builtin_atanf(x);
}
auto atan(f64 x) -> f64 {
  return __builtin_atan(x);
}
#else
#  error "函数未实现，去催开发者"
#endif

#if __has_builtin(atan2)
auto atan(f32 x, f32 y) -> f32 {
  return __builtin_atan2f(x, y);
}
auto atan2(f64 x, f64 y) -> f64 {
  return __builtin_atan2(x, y);
}
#else
#  error "函数未实现，去催开发者"
#endif

// #if __has_builtin(abs)
// #else
// #endif

} // namespace cpp
