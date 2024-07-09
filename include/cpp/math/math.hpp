#pragma once
#include "base.hpp"
#include <define.h>
#include <type.hpp>

namespace cpp {

// 计算两个数的差值（非负）
template <typename T>
static auto diff(T x, T y) -> T {
  return x < y ? y - x : x - y;
}

template <typename T>
static auto equals(const T &a, const T &b) -> bool {
  return a == b;
}

template <>
static auto equals(const f32 &a, const f32 &b) -> bool {
  return a - b < F32_EPSILON && a - b > -F32_EPSILON;
}

template <>
static auto equals(const f64 &a, const f64 &b) -> bool {
  return a - b < F64_EPSILON && a - b > -F64_EPSILON;
}

// --------------------------------------------------
//; 最大最小

template <typename T>
static auto min(T x) -> T {
  return x;
}
template <typename T, typename... Args>
static auto min(T x, Args... args) -> T {
  T y = min(args...);
  return x < y ? x : y;
}

template <typename T>
static auto max(T x) -> T {
  return x;
}
template <typename T, typename... Args>
static auto max(T x, Args... args) -> T {
  T y = max(args...);
  return x > y ? x : y;
}

// 将 v 限制到 [min,max] 的范围内
template <typename T>
static auto clamp(const T &v, const T &min, const T &max) -> const T & {
  if (v < min) return min;
  if (v > max) return max;
  return v;
}

// --------------------------------------------------
//; 求和

template <typename T>
static auto sum(T x) -> T {
  return x;
}
template <typename T, typename... Args>
static auto sum(T x, Args... args) -> T {
  T y = sum(args...);
  return x + y;
}

template <typename T>
static auto sumi(T x) -> int {
  return x;
}
template <typename T, typename... Args>
static auto sumi(T x, Args... args) -> int {
  int y = sumi(args...);
  return x + y;
}

template <typename T>
static auto suml(T x) -> long {
  return x;
}
template <typename T, typename... Args>
static auto suml(T x, Args... args) -> long {
  long y = sumi(args...);
  return x + y;
}

template <typename T>
static auto sumf(T x) -> float {
  return x;
}
template <typename T, typename... Args>
static auto sumf(T x, Args... args) -> float {
  float y = sumf(args...);
  return x + y;
}

template <typename T>
static auto sumd(T x) -> double {
  return x;
}
template <typename T, typename... Args>
static auto sumd(T x, Args... args) -> double {
  double y = sumd(args...);
  return x + y;
}

// --------------------------------------------------
//; 平均数

template <typename T, typename... Args>
static auto avg(T x, Args... args) -> T {
  return sum(args...) / sizeof...(args);
}

template <typename T, typename... Args>
static auto avgf(T x, Args... args) -> float {
  return sumf(args...) / (float)sizeof...(args);
}

template <typename T, typename... Args>
static auto avgd(T x, Args... args) -> double {
  return sumd(args...) / (double)sizeof...(args);
}

// --------------------------------------------------
//;

template <typename T>
static auto abs(T x) -> T {
  return x >= 0 ? x : -x;
}

template <typename T>
static auto gcd(T a, T b) -> T {
  while (b != 0) {
    T t = b;
    b   = a % b;
    a   = t;
  }
  return a;
}

template <typename T>
static auto lcm(T a, T b) -> T {
  return a / gcd(a, b) * b;
}

#if __has(fmod)
static auto mod(f32 x, f32 y) -> f32 {
  return __builtin_fmodf(x, y);
}
static auto mod(f64 x, f64 y) -> f64 {
  return __builtin_fmod(x, y);
}
#else
static auto mod(f32 x, f32 y) -> f32 {
  return x - (i32)(x / y) * y;
}
static auto mod(f64 x, f64 y) -> f64 {
  return x - (i64)(x / y) * y;
}
#endif

// #if __has(abs)
// #else
// #endif

} // namespace cpp
