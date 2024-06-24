#pragma once
#include <define.h>
#include <type.h>

typedef struct {
  union {
    struct {
      float xx, yx;
      float xy, yy;
      float dx, dy;
    };
    float d[6];
  };
} Matrix2;

typedef struct Matrix3 {
  union {
    struct {
      float xx, yx, zx;
      float xy, yy, zy;
      float xz, yz, zz;
      float dx, dy, dz;
    };
    float d[12];
  };
} Matrix3;

typedef Matrix2 TransformMatrix;
