#pragma once
#include <define.h>
#include <plds/base.hpp>
#include <type.hpp>

namespace plds {

dlimport i32 mouse_x;
dlimport i32 mouse_y;

dlimport i32 screen_w;
dlimport i32 screen_h;

dlimport FrameBuffer screen_fb;
dlimport pl2d::TextureB screen_tex;

} // namespace plds
