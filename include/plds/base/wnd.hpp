#pragma once
#include "plui/element.hpp"
#include <define.h>
#include <type.hpp>

struct pdui_window : plui::Element {
  char   *title;
  bool    moving; // 是否正在移动窗口
  int32_t oldx;
  int32_t oldy;
  int8_t  order; // 窗口排列的顺序，置顶、置底
};
