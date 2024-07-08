#pragma once
#include <define.h>
#include <pl2d.hpp>
#include <plui.hpp>
#include <type.hpp>

namespace plui {

struct Style {
  u32         border_width; // 边框宽度
  pl2d::Pixel border_color; // 边框颜色

  u32 bg_color; // 背景色
  u32 fg_color; // 前景色

  pl2d::Texture *bg_img; // 背景图像

  bool moveable;   // 是否可以移动
  bool resizeable; // 是否可以调整大小

  char *text;

  // font;

  bool fit_content;
};

using ChildList = cpp::List<Element *>;

struct Element : Style {
  struct {
    i32 x;      // 元素左上角横坐标
    i32 y;      // 元素左上角纵坐标
    i32 width;  // 元素宽度
    i32 height; // 元素高度
  };
  pl2d::Rect     internal;            // 元素内部的区域
  Element       *parent;              // 父元素，表示当前元素的上一级元素
  bool           needdraw;            // 是否需要刷新，表示是否需要重新绘制元素
  pl2d::Texture *draw_tex = null;     // 可绘制对象，用于绘制元素的图形
  pl2d::Context *draw_ctx = null;     // 可绘制对象，用于绘制元素的图形
  bool           receive_child_event; // 是否接收子对象的事件
  Callbacks      cb;                  // 事件处理器
  int32_t        order;               //
  bool           mouse_hover;         //
  bool           visible;             // 是否可见
  bool           lock;                // 是否被锁定，锁定状态下无法修改属性
  bool           focus;               // 是否获得焦点
  bool           nochild;             // 是否不允许拥有子元素
  ChildList      child;               // 子元素列表
};

} // namespace plui
