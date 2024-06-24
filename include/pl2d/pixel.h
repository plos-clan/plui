#pragma once
#include <define.h>
#include <type.h>

typedef struct {
  union {
    struct {
      byte r, g, b, a;
    };
    byte d[4];
  };
} PixelB;

typedef struct {
  union {
    struct {
      float r, g, b, a;
    };
    float d[4];
  };
} PixelF;
