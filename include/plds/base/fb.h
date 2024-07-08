#pragma once
#include <c.h>
#include <define.h>
#include <type.h>

typedef enum plds_PixFmt {
  plds_PixFmt_BlackWhite,
  plds_PixFmt_Grayscale8,
  plds_PixFmt_Palette16,
  plds_PixFmt_Palette256,
  plds_PixFmt_RGB565,
  plds_PixFmt_BGR565,
  plds_PixFmt_RGB888,
  plds_PixFmt_RGB = plds_PixFmt_RGB888,
  plds_PixFmt_BGR888,
  plds_PixFmt_BGR = plds_PixFmt_BGR888,
  plds_PixFmt_RGBA8888,
  plds_PixFmt_RGBA = plds_PixFmt_RGBA8888,
  plds_PixFmt_BGRA8888,
  plds_PixFmt_BGRA = plds_PixFmt_BGRA8888,
  plds_PixFmt_ARGB8888,
  plds_PixFmt_ARGB = plds_PixFmt_ARGB8888,
  plds_PixFmt_ABGR8888,
  plds_PixFmt_ABGR = plds_PixFmt_ABGR8888,
  plds_PixFmt_RGB_FLT,
  plds_PixFmt_BGR_FLT,
  plds_PixFmt_RGBA_FLT,
  plds_PixFmt_BGRA_FLT,
  plds_PixFmt_ARGB_FLT,
  plds_PixFmt_ABGR_FLT,
  plds_PixFmt_RGB_Plane,
  plds_PixFmt_RGBA_Plane,
  plds_PixFmt_RGB_FLT_Plane,
  plds_PixFmt_RGBA_FLT_Plane,
} plds_PixFmt;

typedef enum plds_PalFmt {
  plds_PalFmt_None,
  plds_PalFmt_RGB888,
  plds_PalFmt_RGB = plds_PalFmt_RGB888,
  plds_PalFmt_BGR888,
  plds_PalFmt_BGR = plds_PalFmt_BGR888,
  plds_PalFmt_RGBA8888,
  plds_PalFmt_RGBA = plds_PalFmt_RGBA8888,
  plds_PalFmt_BGRA8888,
  plds_PalFmt_BGRA = plds_PalFmt_BGRA8888,
  plds_PalFmt_ARGB8888,
  plds_PalFmt_ARGB = plds_PalFmt_ARGB8888,
  plds_PalFmt_ABGR8888,
  plds_PalFmt_ABGR = plds_PalFmt_ABGR8888,
} plds_PalFmt;

#if COLOR_USE_BGR
#  define texture_pixfmt plds_PixFmt_BGRA
#else
#  define texture_pixfmt plds_PixFmt_RGBA
#endif
