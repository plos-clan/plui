#pragma once
#include <define.h>
#include <type.h>

#define RGBA(r, g, b, a) ((u32)(u8)(r) << 24 | (u32)(u8)(g) << 16 | (u32)(u8)(b) << 8 | (u8)(a))
#define RGB(r, g, b)     ((u32)(u8)(r) << 24 | (u32)(u8)(g) << 16 | (u32)(u8)(b) << 8 | 255)
#define BGRA(b, g, r, a) ((u32)(u8)(r) << 24 | (u32)(u8)(g) << 16 | (u32)(u8)(b) << 8 | (u8)(a))
#define BGR(b, g, r)     ((u32)(u8)(r) << 24 | (u32)(u8)(g) << 16 | (u32)(u8)(b) << 8 | 255)

dlimport u32 color_from_name(cstr name);
