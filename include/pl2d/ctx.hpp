#pragma once
#include "pixel.hpp"
#include "texture.hpp"

namespace pl2d {

__Pclass__(Context);

struct Context : private RefCount {
  PTexture tex;

  Context(size_t width, size_t height);
};

} // namespace pl2d
