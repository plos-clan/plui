#pragma once
#include <define.h>
#include <type.hpp>

namespace cpp {

template <typename T>
void exch(T &x, T &y) {
  T t = x;
  x   = y;
  y   = t;
}

template <typename T>
void exch_if(bool b, T &x, T &y) {
  if (!b) return;
  T t = x;
  x   = y;
  y   = t;
}

} // namespace cpp
