
#include <plds/base.hpp>
#include <plds/server.hpp>
#include <type.hpp>

namespace plds::server {

static FrameBuffer *fb = null;

// 是否需要刷新
auto need_flush() -> bool {
  return false;
}

#if NO_STD && OSAPI_MP
// 独立进程模式
// 0: 成功，<0: 失败
auto main(FrameBuffer &fb) -> int {
  if (int err = fb.init(); err < 0) return -err;

  while (pause() >= 0) {}

  return 0;
}
#endif

} // namespace plds::server
